#include "grigorakis.h"
#include <vector>
#include <utility>

using namespace std;

Grigorakis::Grigorakis(const Map& m) :
    Hero(m),
    last_position(0,0)    // αρχικοποίηση για αποφυγή oscillation
{}


void Grigorakis::move(Map& map) {
    if (has_won) return;  // αν κέρδισε, δεν κινείται
    if (is_trapped && has_key)
    {
        is_trapped = false;
        map.ModifyCell(hero_position.getX(),hero_position.getY(),' ');
        return;
    }

    Position current_position = hero_position;   // τρέχουσα θέση
    Position next_position    = current_position; // θέση προτεινόμενης κίνησης

    const vector<pair<const int, const int>> possible_directions{{0,1},{1,0},{-1,0},{0,-1}};
    // Vector με τις κατευθύνσεις: πάνω, δεξιά, αριστερά, κάτω

    // Αποφυγή ταλάντωσης: αν η μόνη «νέα» θέση είναι η προηγούμενη, ψάχνουμε άλλη
    if (next_position == last_position) {
        for (auto const& d : possible_directions) {
            Position alt{current_position.getX() + d.first,
                         current_position.getY() + d.second};
            if (map.getNewCell(alt.getX(), alt.getY()) != '*' &&
                !(alt == last_position)) {
                next_position = alt;
                break;
            }
        }
    }

    // Πρώτο πέρασμα: προτιμούμε μη επισκεφθέντα κελιά
    for (auto const& dir : possible_directions) {
        int nx = current_position.getX() + dir.first;
        int ny = current_position.getY() + dir.second;
        if (nx >= 0 && nx < map.getNumOfRows() &&
            ny >= 0 && ny < map.getNumOfCols() &&
            map.getNewCell(nx, ny) != '*' &&
            !hasVisited(nx, ny))
        {
            next_position = Position(nx, ny);
            break;
        }
    }

    // Δεύτερο πέρασμα: αν δεν βρήκαμε, παίρνουμε οποιοδήποτε έγκυρο κελί
    if (next_position == current_position) {
        for (auto const& dir : possible_directions) {
            int nx = current_position.getX() + dir.first;
            int ny = current_position.getY() + dir.second;
            if (nx >= 0 && nx < map.getNumOfRows() &&
                ny >= 0 && ny < map.getNumOfCols() &&
                map.getNewCell(nx, ny) != '*')
            {
                next_position = Position(nx, ny);
                break;
            }
        }
    }

    // Ενημέρωση θέσης, μνήμης και last_position
    hero_position = next_position;
    map_memory[next_position.getX()][next_position.getY()] = '+';
    last_position = current_position;

    // Τώρα χειριζόμαστε το περιεχόμενο του κελιού όπως πριν
    unsigned int x = next_position.getX();
    unsigned int y = next_position.getY();
    char cell = map.getNewCell(x, y);

    if (cell == 'T') {
        is_trapped = true;
        map.ModifyCell(x, y, 'C');
        return;
    }
    if (cell == 'K') {
        has_key = true;
        map.ModifyCell(x, y, ' ');
        return;
    }
    if (cell == 'C' && has_key) {
        is_trapped = false;
        map.ModifyCell(x, y, ' ');
        return;
    }
    if (cell == 'C' && !has_key) return;
    if (cell == 'L' && has_key) {
        has_won = true;
        return;
    }
}
