#include "map.h"
#include <fstream>
#include <iostream>

using namespace std;

Map::Map(): xartis()    {}


Map::Map(const unsigned int rows , const unsigned int columns)
    :xartis(rows,vector<char>(columns , ' '))  {}  //Γέμισμα της συλλογής με κενά, και ταυτόχρονη αρχικοποίηση των διαστάσεων χάρτη.


const char Map::getNewCell(const unsigned int rows , const unsigned int columns) const
{
    if (rows>= getNumOfRows() || columns>=getNumOfCols())
            return '*'; //Αν βρισκόμαστε εκτός ορίων του χάρτη επιστρέφεται '*' δηλαδή τοίχος.
        return xartis[rows][columns];  //Αλλιώς επιστρέφεται κανονικά το κελί.
}

const unsigned int Map::getNumOfRows () const
{
    if (xartis.empty()) return 0;
    return xartis.size();
}
const unsigned int Map::getNumOfCols() const //Getter αριθμού στηλών χάρτη.
{
    if(xartis.empty()) return 0;
    return xartis[0].size();  //Αν ο χάρτης είναι άδειος επιστρέφονται 0 στήλες.
}

vector<vector<char>> Map::getMap() const
{
    return xartis;
}

void Map::ModifyCell(const unsigned int x , const unsigned int y , const char ch)
{
    if (x<getNumOfRows()  && y<getNumOfCols()) xartis[x][y] = ch;
    return ;
}
