#pragma once
#include "hero.h"
#include <vector>

using namespace std;
class Asimenia : public Hero {


public:
    Asimenia(const Map &); //Θα κληρονομήσουμε τον γενικό κατασκευαστή της κλάσης Hero.
    void move(Map &) override;//Εδώ Υλοποιείται ο Αλγόριθμος Κίνησης της Ασημένιας.
    //Δηλαδή εδώ γίνεται το pathfinding και γίνεται ένα βήμα κάθε φορά της Ασημένιας .
    //Επίσης υπερφορτώνεται η συνάρτηση move της base hero class , όπως και στην κλάση του Γρηγοράκη, ώστε να διαμορφωθεί διαφορετική υλοποίηση στην κίνηση.
    Position last_position; //Τελευταία θέση Ασημένιας.
};
