#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <ctime>
#include "map.h"
#include <string>
#include "grigorakis.h"
#include <stdexcept>
#include "asimenia.h"
#include "hero.h"
#include <cstdlib>
#include <cmath>

using namespace std;
int main (int argc , char ** argv)
    {
        if (argc<2)
            {
                throw runtime_error("Θα Έπρεπε Να Δοθεί Ως Όρισμα ο Χάρτης. Το Παιχνίδι Τερματίζεται.\n");
            }
        ifstream file(argv[1],ios::in);
        if(!file.is_open())
            throw runtime_error("Αδυναμία Ανοίγματος Αρχείου Χάρτη.\n");
        string map_line; // Αντικείμενο κλάσης string το οποίο θα φορτώνει τον χάρτη γραμμή προς γραμμή σε vector που θα αναπαριστά τον χάρτη μας.
        vector<string> map_lines;
        while (getline(file,map_line))
            map_lines.push_back(map_line);  //Προσπέλαση του αρχείου και αντιγραφή των περιεχομένων του στον vector. Άρα στο τέλος αυτού του βρόχου θα έχουμε μια  συλλογή που θα αναπαριστά ακριβώς τον χάρτη μας, όπως δόθηκε ως όρισμα στην γραμμή εντολών του προγράμματος.
        if (map_lines.empty()) return 1;

         int ladder_x_axis = -1;
         int ladder_y_axis = -1;
        //ΣΕ αυτό το σημείο γίνεται έλεγχος χαρακτήρων του χάρτη όπως γράφεται ότι απαιτείται στο Q&A.
        char c;
        for (int i =0;  i<map_lines.size(); i++)
        {
            for (int j=0;   j<map_lines[0].size();  j++)
            {
                c=map_lines[i][j];
                if (map_lines[i][j] == 'L')
                {
                    ladder_x_axis = i;
                    ladder_y_axis = j;      //Αυτό το κάνουμε για να κρατήσουμε τις συντεταγμένες της σκάλας ώστε αν οι ήρωες συναντηθούν στο τέλος να εξαφανιστούν οι τοίχοι και να ακολουθήσουν το συντομότερο μονοπάτι προς εκεί.
                }
                if (c!=' ' && c!='T' &&c!='K' &&c!='L' &&c!='*' &&c!='\n')
                    throw runtime_error("Μη έγκυροι Χαρακτήρες στον Χάρτη. \n");
            }
        }

        if(ladder_x_axis <0) throw runtime_error("Δεν βρέθηκε σκάλα. Το παιχνίδι Τερματίζεται.\n");
        unsigned int map_number_of_rows = map_lines.size();
        unsigned int map_number_of_columns = map_lines[0].size();
        //Αρχικοποίηση διαστάσεων χάρτη μέσω του Vector map_lines.
        Map file_map(map_number_of_rows,map_number_of_columns); //Δημιουργία αντικειμένου χάρτη map και αρχικοποίηση των διαστάσεών του με General Concstructor (βρίσκεται στο πηγαίο header source file map.h).
        for (unsigned int i=0;  i<map_number_of_rows; i++)
            for (unsigned int j=0;  j<map_number_of_columns;    j++)
                file_map.ModifyCell(i,j,map_lines[i][j]);
        //Πλέον έχουμε έτοιμο αντικείμενο map που αναπαριστά τον χάρτη σε ακριβή κλίμακα.


        //Τωρα θα τοποθετηθούν τυχαία οι ήρωες.
        srand(time(nullptr));
        Grigorakis grigorakis(file_map); //Δημιουργία αντικειμένου που αναπαριστά τον Γρηγοράκη και αρχικοποίηση αυτόυ μέσω General Constructor της κλάσης Hero, την οποία κληρονομεί η κλάση Grigorakis ως παράγωγη αυτής.
        Asimenia ashmenia(file_map); //Εντελώς αντίστοιχα με παραπάνω, το ίδιο γίνεται και για την Ασημένια.
        int grigorakis_x,grigorakis_y;
        int ashmenia_x,ashmenia_y;
        do
        {
            grigorakis_x = rand() % file_map.getNumOfRows();
            grigorakis_y = rand() % file_map.getNumOfCols();
        }while (file_map.getNewCell(grigorakis_x,grigorakis_y)!= ' ');
        grigorakis.setPosition(grigorakis_x,grigorakis_y);
        do
        {
            ashmenia_x = rand() % file_map.getNumOfRows();
            ashmenia_y = rand() % file_map.getNumOfCols();
        }while (file_map.getNewCell(ashmenia_x,ashmenia_y)!= ' ' || abs(grigorakis_x-ashmenia_x)<7 && abs(grigorakis_y-ashmenia_y)<7);
        ashmenia.setPosition(ashmenia_x,ashmenia_y);


        //Αρχικοποίηση Ncurses !
        initscr();
        noecho(); //Δεν θα εμφανίζονται οι χαρακτήρες του πληκτρολογίου στην οθόνη.
        curs_set(0); //Ο κέρσορας της ncurses τίθεται σε θέση 0.
        timeout(100); // Δεν θα υπάρχει καθυστέρηση μεταξύ getch και εισόδου πριν την επιστροφή αυτής.
        bool synanthsh_hrwwn(false); //Οι ήρωες δεν συναντήθηκαν ακόμα.
        for (int seira = 0; seira<1000; seira++)
        {
            int ch = getch();
            clear(); // Καθαρίζονται τα περιεχόμενα της οθόνης.

            for (int i=0;   i<file_map.getNumOfRows();   i++)
            for (int j=0;   j<file_map.getNumOfCols();   j++)
                mvaddch(i,j,file_map.getNewCell(i,j)); //Εκτυπώνεται στην οθόνη ncurses ο χάρτης αυτός καθ'αυτός.

            //Αν ο ήρωας (ασημένια ή γρηγοράκης) έχει περάσει από ένα σημείο του χάρτη , εκτυπώνεται στην οθόνη μέσω της mvaddch.
            auto grigorakis_map = grigorakis.getMap();
            auto ashmenia_map = ashmenia.getMap();
            for (int k =0;  k<file_map.getNumOfRows();   k++)
            {
                for (int l=0;   l<file_map.getNumOfCols();   l++)
                {
                    if(grigorakis_map[k][l] == '+') mvaddch(k,l,'+');
                    if(ashmenia_map[k][l] == '+') mvaddch(k,l,'+');
                }
            }
            //Εμφανίζονται στην οθόνη οι συντεταγμένες γρηγοράκη και ασημένιας.
            unsigned int g_x = grigorakis.getPosX();
            unsigned int g_y = grigorakis.getPosY();
            unsigned int a_x = ashmenia.getPosX();
            unsigned int a_y = ashmenia.getPosY();
            mvaddch(g_x,g_y,'G');
            mvaddch(a_x,a_y,'A');

            refresh(); //Ανανέωση παραθύρου οθόνης ncurses.

            //Κινούμε τους παίκτες :
            grigorakis.move(file_map);
            ashmenia.move(file_map);
            if (grigorakis.isTrapped() && ashmenia.isTrapped() && !grigorakis.HasKey() && !ashmenia.HasKey())
            {
                clear();
                printw("Game Over! Both Heroes Trapped . ");
                refresh();
                getch();
                endwin();
                return 0;
            }
            if (grigorakis.getPosition()  == ashmenia.getPosition()){
                //printw("Οι Ήρωες Συναντήθηκαν!");
                g_x=grigorakis.getPosX();
                g_y=grigorakis.getPosY();
                a_x=ashmenia.getPosX();
                a_y=ashmenia.getPosY();
                if (!( g_x == ladder_x_axis && g_y == ladder_y_axis
                     && a_x == ladder_x_axis && a_y == ladder_y_axis
                     && (ashmenia.HasKey() || grigorakis.HasKey()) ))
                    continue;  // αγνοούμε την συνάντηση πριν την σκάλα

                for(int i =0;   i<file_map.getNumOfRows();  i++)
                    for (int j =0;  j<file_map.getNumOfCols();  j++)
                        if(file_map.getNewCell(i,j) == '*')
                        {
                            mvaddch(i,j,' '); //Εξαφάνιση τοίχων μέσω mvaddch.
                            file_map.ModifyCell(i,j,' ');//Εξαφάνιση τοίχων μέσω vector.
                        }
                timeout(1000);//Καθυστέρηση 1s αφού σβηστούν οι τοίχοι
                while (g_x!=ladder_x_axis || g_y != ladder_y_axis ||a_x!=ladder_x_axis || a_y!= ladder_y_axis )
                {
                    //Για τον Γρηγοράκη.
                    if (g_x<ladder_x_axis) g_x++;  //Μετακίνηση προς δεξιά κατά μία θέση του Γρηγοράκη.
                    else if (g_x>ladder_x_axis) g_x--; //Μετακίνηση προς αριστερά κατά μία θέση του Γρηγοράκη.
                     if (g_y<ladder_y_axis) g_y++; //Μετακίνηση προς πάνω κατά μία θέση του Γρηγοράκη.
                    else if (g_y > ladder_y_axis) g_y--; //Μετακίνηση προς κάτω κατά μία θέση του Γρηγοράκη.


                    //Για την Ασημένια.
                    if (a_x<ladder_x_axis) a_x++;  //Μετακίνηση προς δεξιά κατά μία θέση της Ασημένιας.
                    else if (a_x>ladder_x_axis) a_x--; //Μετακίνηση προς αριστερά κατά μία θέση της Ασημένιας.
                     if (a_y<ladder_y_axis) a_y++; //Μετακίνηση προς πάνω κατά μία θέση της Ασημένιας.
                    else if (a_y > ladder_y_axis) a_y--; //Μετακίνηση προς κάτω κατά μία θέση της Ασημένιας.

                    clear(); //Άδειασμα Οθόνης
                    //Σε αυτό το σημείο θα εμφανιστούν οι χαρακτήρες του χάρτη,και  οι ήρωες, στην οθόνη ncurses.
                    for (unsigned int i =0; i<file_map.getNumOfRows();  i++)
                        for (unsigned int j=0;  j<file_map.getNumOfCols();  j++)
                            mvaddch(i,j,file_map.getNewCell(i,j)); //Εμφάνιση χάρτη
                    mvaddch(g_x,g_y,'G');
                    mvaddch(a_x,a_y,'A');
                    mvaddch(ladder_x_axis,ladder_y_axis,'L');
                    refresh();

                }if ( g_x == ladder_x_axis && g_y == ladder_y_axis
                    && a_x == ladder_x_axis && a_y == ladder_y_axis
                    && (ashmenia.HasKey() || grigorakis.HasKey()) )
                {
                   printw("Heroes Met and Reached The Ladder - You Win!");
                getch();
                endwin();
                return 0;

                }
            }
        }
        if (grigorakis.getPosX() != ashmenia.getPosX() || grigorakis.getPosY() != ashmenia.getPosY())
            printw("Heroes Did not Meet...Game Over!");
        endwin();
        return 0;
    }
