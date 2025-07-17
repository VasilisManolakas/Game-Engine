#pragma once  //Οδηγία προς Compiler να συμπεριλάβει κάθε .h μόνο μία φορά.
#include <iostream>
#include <string> //Για την διαχείριση της συλλογής συμβολοσειρών.
#include <vector>   //Συμπεριλήφθηκε για να περνά ως παράμετρος στον General Constructor της κλάση Hero , ώστε να αρχικοποιηθεί η συλλογή με κενά, αναπαριστώντας την αρχική "κενή μνήμη" του ήρωα.
#include "map.h"    // Συμπεριλήφθηκε για να χρησιμοποιηθούν αντικείμενα τύπου Map ως ορίσματα μεθόδων κλάσεων Hero & Position.

using namespace std;

class Hero {
protected:
    vector<vector<char>> map_memory;    //Συλλογή που παριστά την μνήμη του ήρωα, δηλαδή τα μέρη από τα οποία έχει περάσει.
    bool has_key;  //Λογική Μεταβλητή που Δείχνει Αν ο Ήρωας έχει το κλειδί για να νικήσει.
    bool is_trapped;  //Λογική Μεταβλητή που δείχνει αν ο ήρωας είναι παγιδευμένος εντός παγίδας.
    bool has_won;   //Λογική Μεταβλητή που Δείχνει αν ο Ήρωας Νίκησε.

    //Εμφωλευμένη κλάση Position που αναπαριστά ζεύγος συντεταγμένων ήρωα.
    class Position {

    private:
        unsigned int x_axis;  //Ζεύγος Συντεταγμένων που αναπαριστά την θέση του ήρωα.
        unsigned int y_axis;

    public:
        Position(); //Default Constructor που αρχικοποιεί τις Χ,Υ συντεταγμένες του ήρωα σε (0,0).
        Position(const unsigned int, const unsigned int); //General Constructor που αρxικοποιεί τις Χ,Υ συντεταγμένες του ήρωα με βάση τα ορίσματα.
        Position(const Position&);  //Copy Constructor για Αντιγραφή ζεύγους συντεταγμένων.


        const unsigned int getX() const;  //Αντίστοιχος Getter Για την Τετμημένη.
        const unsigned int getY() const;  //Αντίστοιχος Getter για την Τεταγμένη.
        void setX(const unsigned int ) ;
        void setY(const unsigned int);
        const bool operator==(const Position& ) const;  //Υπερφόρτωση '=' για την σύγκριση αντικειμένων τύπου Position για την σύγκριση συντεταγμένων.

        Position ComputeNextMove(const Map&,const vector<vector<char>> &) const;  //Μέθοδος για την αποκομιδή της επόμενης κίνησης του Ήρωα.

    };
    Position hero_position; // ΑΝτικείμενο που αναπαριστά την θέση του ήρωα.



public:
    virtual ~Hero() = default;  //Ορισμός εικονικού καταστροφέα , άρα η κλάση είναι abstract.
    Hero(const Map &);  //General Constructor Κλάσης Hero, αρχικοποιώντας την μνήμη του ήρωα (την συλλογή map_memory) με κενούς χαρακτήρες,ορίζει την διάσταση χάρτη με βάση το όρισμα, αρχικοποιεί το αντικείμενο hero_position με (0,0),δηλώνει πως ο ήρωας ΔΕΝ έχει κλειδί(has_key(false)),ΔΕΝ είναι παγιδευμένος (is_trapped(false)), και επίσης αρχικοποιεί πως ο ήρωας ΔΕΝ έχει κερδίσει (has_won(false)).

    Hero(const vector<vector<char>>& ); //General Constructor της κλάσης Hero, που αρχικοποιεί με κενά την συλλογή map_memory.

    const bool hasWon() const;  //Μέθοδος που επιστρέφει εάν ο ήρωας νίκησε μέσω απλόυ return - statement.
    const bool isTrapped() const; //Μέθοδος που επιστρέφει εάν ο ήρωας είναι παγιδευμένος μέσω απλόυ return - statement.
    const bool HasKey() const ; //Μέθοδος που επιστρέφει εάν ο ήρωας έχει το κλειδί μέσω απλόυ return - statement.
    virtual void move( Map&);
    void setPosition(const unsigned int ,const unsigned int);
    Position getPosition() const;
    const vector<vector<char>>& getMap() const;
    unsigned int getPosX() const;
    unsigned int getPosY() const;

    //Εικονική Μέθοδος που λαμβάνει τον χάρτη by reference, τον περνά στην ComputeNextMove, η οποία επιστρέφει την νέα θέση, και εάν αυτή η θέση είναι εντός ορίων,δηλαδή δεν ξεπερνά τους τοίχους('*') η μνήμη του ήρωα σε αυτές τις συντεταγμένες ανανεώνεται, και αυτός θυμάται πλεόν ότι πέρασε από εκεί.Η move είναι εικονική στην κλάση Hero ώστε να μπορούμε στις παραγόμενες κλάσεις Γρηγοράκη και Ασημένιας να την υπερφορτώσουμε με διαφορετική λογική κίνησης.

    const bool hasVisited(const unsigned int , const unsigned int ) const;  // Mέθοδοςπου ελέγχει αν ο ήρωας πέρασε από μια συγκεκριμένη θέση (δίνονται οι συντεταγμένες ως ορίσματα).
};
