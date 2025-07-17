#pragma once  //Οδηγία προς τον compiler να ενσωματώσει τα πηγαία header files μία φορά έκαστος.

#include "hero.h"   //Απαραίτητη συμπερίληψη βιβλιοθήκης καθώς ο Γρηγοράκης είναι Ήρωας, και άρα κληρονομεί από την κλάση Hero.

using namespace std;

class Grigorakis : public Hero {    //Δήλωση Κληρονομικότητας(Ο Γρηγοράκης ΕΙΝΑΙ ήρωας άρα κληρονομεί τα προστατευμένα χαρακτηριστικά της κλάσης αυτής.)
protected:
    Position last_position;
public:
    Grigorakis(const Map &);  //General Constructor της κλάσης Γρηγοράκη.
    void move (Map &) override; //Υπερφορτωμένη μέθοδος κίνησης Γρηγοράκη για την εφαρμογή ξεχωριστού αλγορίθμου κίνσης.
};
