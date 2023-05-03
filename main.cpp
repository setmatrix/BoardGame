#include <iostream>
#include <cstdlib>
#include "FUnitOnBoard/UnitOnBoard.h"
#include "game.cpp"

using namespace std;

int main(int argc, char **argv )
{
    system("clear");
    switch(argc)
    {
        case 4:
            char *mapName = argv[1];
            char *statusName = argv[2];
            char *orderName = argv[3];
            gameStart(mapName, statusName, orderName);
        break;
        case 5:
            char *mapName = argv[1];
            char *statusName = argv[2];
            char *orderName = argv[3];
            int timeOut = atoi(argv[4]);
            gameStart(mapName, statusName, orderName, timeOut);
        break;
        cout << "Jest:" << argc << "argumentow" << endl;
        cout << argv[1];
        break;
        default:
        if (argc < 4)
        {
            cout << "Za mało parametrow: " << argc << endl;
        } else 
        {
            cout << "Za dużo parametrow: " << argc << endl;
        }
    }
}