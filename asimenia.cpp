#include "asimenia.h" // Η κλάση Asimenia πρέπει να έχει οριστεί πριν την Hero, καθώς η Asimenia κληρονομεί από αυτήν.
#include <utility>   //Για να χρησιμοποιήσουμε Pairs.
#include <vector>    //Για να χρησιμοποιήσουμε Vectors.

using namespace std;

Asimenia::Asimenia(const Map& mp) : Hero(mp), last_position(0,0) {}  //Εκτελείται ο κατασκευαστής της base Κλάσης Hero με όρισμα το αντικείμενο χάρτη mp . Επίσης αρχικοποιούνται οι boolean μεταβλητές (has_key,has_won,is_trapped) με ψευδή τιμή και στήνεται μια placeholder θέση Position στις συντεταγμένες (0,0) πάνω στην οποία η main αργότερα θα καλέσει συνάρτηση για τυχαία τοποθέτηση των ηρώων με απόσταση >= 7 είτε οριζόντια, είτε κατακόρυφα.

void Asimenia::move(Map& map) {
    if (has_won || is_trapped ) return ; //Καμία κίνηση διαθέσιμη.Αν η Ασημένια έχει παγιδευτεί δεν εκτελείται τίποτα. Αν έχει νικήσει, δεν εκτελείται επίσης τίποτα.
    Position current_position = hero_position; //Αποθηκεύω την τρέχουσα θέση για την μνήμη .
    Position next_position = current_position; //Κρατάω αντικείμενο next_position για την επόμενη κίνηση της Ασημένιας.

    const vector<pair<const int, const int>> possible_directions {{0,1},{1,0},{-1,0},{0,-1}};
    //Vector με τις βασικές κατευθύνσεις πάνω,δεξιά,αριστερά,κάτω.

    //Πρώτο πέρασμα: δοκιμάζουμε θέσεις που δεν έχουμε επισκεφθεί ακόμη
    for (auto const & d : possible_directions)
    {
        int new_x_axis = current_position.getX() + d.first;
        int new_y_axis = current_position.getY() + d.second;
        if (new_x_axis>=0 && new_x_axis < map.getNumOfRows() &&
            new_y_axis>=0 && new_y_axis < map.getNumOfCols() &&
            map.getNewCell(new_x_axis,new_y_axis) != '*' &&
            !hasVisited(new_x_axis,new_y_axis))
        {
            next_position = Position(new_x_axis,new_y_axis);  //Εδώ καθορίζεται η θέση προς κίνηση.
            break; //Έξοδος εφόσον βρέθηκε νέα θέση.
        }
    }

    //Δεύτερο πέρασμα: αν δεν βρέθηκε, επιλέγουμε οποιαδήποτε έγκυρη θέση
    if (next_position == current_position)
    {
        for (auto const & d : possible_directions)
        {
            int new_x_axis = current_position.getX() + d.first;
            int new_y_axis = current_position.getY() + d.second;
            if (new_x_axis>=0 && new_x_axis < map.getNumOfRows() &&
                new_y_axis>=0 && new_y_axis < map.getNumOfCols() &&
                map.getNewCell(new_x_axis,new_y_axis) != '*')
            {
                next_position = Position(new_x_axis,new_y_axis);
                break; //Έξοδος εφόσον βρέθηκε θέση.
            }
        }
    }

    //Αποφυγή επιστροφής στην προηγούμενη θέση
    if (next_position == last_position && !(next_position == current_position))
    {
        for (auto const & d : possible_directions)
        {
            int new_x_axis = current_position.getX() + d.first;
            int new_y_axis = current_position.getY() + d.second;
            Position alt{new_x_axis,new_y_axis};
            if (new_x_axis>=0 && new_x_axis < map.getNumOfRows() &&
                new_y_axis>=0 && new_y_axis < map.getNumOfCols() &&
                map.getNewCell(new_x_axis,new_y_axis) != '*' &&
                !(alt == last_position))
            {
                next_position = alt;  //Εναλλακτική θέση για να αποφύγουμε εναλλαγή μεταξύ δύο κελιών.
                break;
            }
        }
    }

    //Τελικά ενημερώνουμε θέση, μνήμη και last_position
    hero_position = next_position;
    map_memory[next_position.getX()][next_position.getY()] = '+';
    last_position = current_position;

    unsigned int x = next_position.getX();
    unsigned int y = next_position.getY();
    char new_cell = map.getNewCell(x,y);
    if (new_cell=='*') return;  //Καμία ενέργεια αν το κελί είναι τοίχος.

    if (new_cell == 'T')  //Αν η Ασημένια συναντήσει παγίδα:
    {
        is_trapped = true;  //Παγιδεύεται
        map.ModifyCell(x,y,'C');    //Μετατρέπεται σε κλουβί
        return;
    }

    if (new_cell == 'K')  //Αν συναντήσει κλειδί:
    {
        has_key = true;    //Το μαζεύει
        map.ModifyCell(x,y,' ');    //Αφαιρείται από το χάρτη
        return;
    }

    if (new_cell == 'C' && has_key)  //Αν συναντήσει κλουβί και έχει κλειδί:
    {
        is_trapped = false; //Απελευθερώνεται
        map.ModifyCell(x,y,' ');    //Κενό κελί
        return;
    }

    if (new_cell == 'C' && !has_key) return;  //Αν συναντήσει κλουβί χωρίς κλειδί, μένει εκεί.

    if (new_cell == 'L' && has_key)  //Αν φτάσει στη σκάλα με κλειδί:
    {
        has_won = true;  //Κερδίζει
        return;
    }
}
