#pragma once  //Οδηγία προς compiler να συμπεριλάβει το header file μόνο μία φορά.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Map{
    protected:
        vector<vector<char>> xartis;
    public:
        Map(); //Default Constructor
        Map(const unsigned int , const unsigned int);  //General Constructor του χάρτη για αρχικοποίηση των διαστάσεών του.
        const char getNewCell(const unsigned int, const unsigned int) const; //Αν βγω εκτός ορίων ο χάρτης επιστρέφει *, δηλαδή τοίχο. Η GetNewCell επιστρέφει ένα κελί του χάρτη ανά φορά για την κάθε κίνηση.
        const unsigned int getNumOfRows()const; //Επιστροφή Αριθμού Γραμμών Χάρτη
        const unsigned int getNumOfCols()const; //Επιστροφή Αριθμού Στηλών Χάρτη
        vector<vector<char>> getMap() const;
        void ModifyCell(const unsigned int , const unsigned int , const char);
        //Η συνάρτηση ModifyCell θα δίνει την δυνατότητα ο χάρτης να τροποποιείται . Για παράδειγμα, μπορεί να επιτρέψει την μετατροπή παγίδας σε κλουβί αν κάποιος ήρωας πατήσει παγίδα.
};


