#include "hero.h"  //Συμπερίληψη αρχείου header ώστε να συνδεθούν οι δηλώσεις στο .h & .cpp file.

#include <iostream>

using namespace std;

Hero::Position::Position()  //Υλοποίηση Default Constructor της κλάσης Position, χρησιμοποι΄ώντας initializer list. Δηλαδή η αρχική θέση είναι (0,0).

    :
    x_axis(0),
    y_axis(0)
{}

Hero::Position::Position(const unsigned int x,const unsigned int y)  //Υλοποίηση General Constructor της κλάσης Position, η οποία είναι εμφωλευμένη εντός της κλάσης Hero.
//Χρησιμοποιείται επίσης initializer list.
    : x_axis(x),
    y_axis(y)
{}

Hero::Position::Position(const Hero::Position& other)  //Copy Constructor της κλάσης Position για την αντιγραφή ( deep copying ) αντικειμένων τύπου Position.

    : x_axis(other.x_axis), y_axis(other.y_axis)
{}


const unsigned int Hero::Position::getX() const {
    return x_axis;
}
//Getters X,Y.
const unsigned int Hero::Position::getY() const {
    return y_axis;
 }

const bool Hero::Position::operator==(const Hero::Position& other) const { //Υπερφόρτωση '==' για την σύγκριση αντικειμένων τύπου Position.Αν τα δύο αντικείμενα έχουν ΄΄ισες συντεταγμένες, επιστρέφεται αληθής λογική τιμή.


    return (x_axis == other.x_axis && y_axis == other.y_axis);

}

Hero::Position Hero::Position::ComputeNextMove(const Map& m,const vector<vector<char>> &map_memory) const {

    const vector<pair<const int , const int>> possible_directions{{0,1},{1,0},{0,-1},{-1,0}};  //Δημιουργία ζεύγους τιμών που αναπαριστούν τις πιθανές κινήσεις.

    int new_x_axis,new_y_axis;  //Δημιουργία μεταβλητών που αναπαριστούν το νέο ζεύγος συντεταγμένων.
    for (auto const & dir : possible_directions)
    {
        new_x_axis = (int)x_axis + dir.first;
        new_y_axis = (int)y_axis + dir.second;  //Προσπέλαση vector <pair> και ανάθεση τιμών στις νέες συντεταγμένες.
        if (new_x_axis>=0 && new_x_axis < m.getNumOfRows() && new_y_axis>=0 && new_y_axis <m.getNumOfCols() && m.getNewCell(new_x_axis,new_y_axis)!='*'){
        //Έλεγχος αν οι νέες συντεταγμένες βρίσκονται εντός ορίων και δεν αναπαριστούν τοίχο.
        if (map_memory[new_x_axis][new_y_axis]!='+')    //Έλεγχος αν ο ήρωας δεν τις έχει επισκεφθεί.
            return Position(new_x_axis,new_y_axis);
        }

    }
        //Έλεγχος για οποιαδήποτε valid κίνηση.
        for (auto const &d: possible_directions)
        {
              new_x_axis = x_axis + d.first;
              new_y_axis = y_axis + d.second;
               if (new_x_axis>=0 && new_x_axis < m.getNumOfRows() && new_y_axis>=0 && new_y_axis <m.getNumOfCols() && m.getNewCell(new_x_axis,new_y_axis)!='*') return Position(new_x_axis,new_y_axis);
        //Έλεγχος αν οι νέες συντεταγμένες βρίσκονται εντός ορίων και δεν αναπαριστούν τοίχο.
        }

    //Αλλιώς επιστρέφεται η ίδια θέση, εφόσον καμία κίνηση δεν είναι πιθανή.
    return *this;
}

//General Constuctor κλάσης Hero, που δέχεται αντικείμενο χάρτη παραμετρικά.
Hero::Hero(const Map &mp)
    :
    map_memory(mp.getNumOfRows(),vector<char>(mp.getNumOfCols(),' ')),
    has_key(false),
    is_trapped(false),
    has_won(false),
    hero_position(0,0)
    //Αρχικοποίηση μνήμης ήρωα με κενούς χαρακτήρες και διαστάσεων χάρτη μνήμης,
    //Οι λογικές μεταβλητές αρχικοποιούνται με λογικό ΌΧΙ.
    //Η αρχική θέση του ήρωα αρχικοποείται ως (0,0).
{}


const bool Hero::hasWon() const {

    return has_won;  //Επιστροφή της boolean που δείχνει αν ο ήρωας κέρδισε.(Λειτουργεί σαν getter).
    //Δηλαδή ανά πάσα στιγμή υπάρχει η δυνατότητα να ελεγχθεί αν το παιχνίδι τελείωσε ή συνεχίζει (σημαντικό για τα 1000 τέρμινα).
}

const bool Hero::isTrapped() const
{
    return is_trapped;  //Επιστροφή της boolean που δείχνει αν ο ήρωας είναι παγιδευμένος .(Λειτουργεί σαν getter).
}

const bool Hero::HasKey() const
{
    return has_key;        //Επιστροφή της boolean που δείχνει αν ο ήρωας έχει το κλειδί.(Λειτουργεί σαν getter).
}

void Hero::move( Map& map) {

    if (has_won|| is_trapped) return; //Αν ο ήρωας είναι παγιδευμένος, ή το παιχνίδι έληξε λόγω νίκης, δεν μπορεί να κινηθεί.

    Hero::Position next = hero_position.ComputeNextMove(map,map_memory); // Δημιουργία αντικειμένου Position (το Hero::Position τοποθετείται επειδή η Position βρίσκεται εντός της Hero),
    //  το οποίο θα αποθηκεύει την επόμενη κίνηση καλώντας την getnextmove, η οποία εξετάζει όλες τις πιθανές κινήσεις(πάνω, κάτω,δεξιά και αριστερά)
     //Πλέον η θέση του ήρωα προορίζεται ως η next.
    char next_cell = map.getNewCell(next.getX(),next.getY());
    if (next_cell =='*') return ; //Καμία κίνηση αν έχουμε τοίχο.

if (!(next.getX() < map.getNumOfRows() && next.getY() < map.getNumOfCols())) return;


    if (next_cell == 'T')
    {
        hero_position = next;
        is_trapped = true;
        map.ModifyCell(next.getX(),next.getY(),'C');
        map_memory[next.getX()][next.getY()] = '+';
        return;
    }//Αν ο ήρωας βρεθεί σε Παγίδα , εκείνη μετατρέπεται σε κλουβί και εκείνος παγιδεύεται.
    //Η μνήμη του ήρωα ενημερώνεται και η boolean μεταβλητή που δείχνει αν είναι παγιδευμένος πλέον αληθεύει.

    if (next_cell =='C')
    {
        if (has_key)
        {
            hero_position = next;
            is_trapped = false ;
            map.ModifyCell(next.getX(),next.getY(),' ');
            map_memory[next.getX()][next.getY()] = '+';
        }
        return;
    }//Αν ο ήρωας βρεθεί σε Παγίδα και έχει το κλειδί , εκείνη μετατρέπεται σε κενό χαρακτήρα και ο ήρωας απελευθερώνεται.
    //Η μνήμη του ήρωα ενημερώνεται και η boolean μεταβλητή που δείχνει αν είναι παγιδευμένος πλέον ψευδίζει.

    if(next_cell == 'K')

    {
        hero_position = next;
        has_key = true;
        map.ModifyCell(next.getX(),next.getY(),' ');
        map_memory[next.getX()][next.getY()] = '+';
        return;
    }

    if (next_cell == 'L')
    {
        hero_position = next;
        map_memory[next.getX()][next.getY()] = '+';
        if (has_key) has_won = true;

        return;
    }

    hero_position = next;
    map_memory[next.getX()][next.getY()] = '+';  //Κίνηση σε κενό κελί.
}

void Hero::Position::setX(const unsigned int x)
{
    x_axis = x;
}

void Hero::Position::setY(const unsigned int y)
{
    y_axis = y;
}
void Hero::setPosition(const unsigned int x, const unsigned int y)
{
    hero_position.setX(x);
    hero_position.setY(y);
    if (x<map_memory.size() && y<map_memory[0].size())
        map_memory[x][y] = '+';
}

Hero::Position Hero::getPosition() const
{
    return hero_position;
}

const vector<vector<char>>& Hero::getMap() const
{
    return map_memory;
}

unsigned int Hero::getPosX() const
{
    return hero_position.getX();
}

unsigned int Hero::getPosY() const
{
    return hero_position.getY();
}

const bool Hero::hasVisited(const unsigned int x,const unsigned int y) const {
    if (x < map_memory.size() && y < map_memory[0].size()) {
        return map_memory[x][y] == '+';  //Επιστρέφεται Boolean μεταβλητή που ελέγχει αν ο ήρωας επισκέφθηκε αυτό το μέρος.

    }
    return false;  //Διαφορετικά επιστρέφεται ψευδής τιμή, εφόσον o compiler δεν "μπήκε" στο if_statement.

}
