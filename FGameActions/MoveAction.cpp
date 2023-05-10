#include <string>

//If enemy is on place x and y, returns true
bool IsEnemyUnitOnBoard(Player enemyPlayer, int x, int y)
{
    std::list<UnitOnBoard> units = enemyPlayer.getUnitList();

    for (std::list<UnitOnBoard>::iterator it= units.begin(); 
            it != units.end(); ++it)
        {
            if (it->getXCord() == x && it->getYCord() == y)
            {
                units.clear();
                return true;
            }
        }
    units.clear();
    return false;
}

void MoveAction(Player actualPlayer, Player enemyPlayer, std::string *words, char** board)
{
    if (actualPlayer.getUnitList().size() <= 0)
    {
        std::cout << "You haven't an unit to play\n";
        return;
    }
    for (std::list<UnitOnBoard>::iterator it= actualPlayer.getUnitList().begin(); 
        it != actualPlayer.getUnitList().end(); ++it)
    {
        //Check if unit Id is equal to Id from file.
        if (it->getUnitId() == stoi(words[0]))
        {
            //Then check, if Cordinates are on board
            if (stoi(words[2]) > 0 && stoi(words[2]) < 32 && stoi(words[3]) > 0 && stoi(words[3]) < 5)
            {
                std::cout << "Your coordication are outside from board\n";
                return;
            }
            
            std::string s(board[(stoi(words[2]), stoi(words[3]))]);
            //Lastly, check if Coordinates from file are pointing to road, base, or cave and are on range to unit.
            if (!s.compare("0") && !s.compare("6"))
            {
                std::cout << "This place is an obstacle\n";
                return;
            }

            if (IsEnemyUnitOnBoard(enemyPlayer, stoi(words[2]), stoi(words[3])))
            {
                std::cout << "Enemy on this coordination exists\n";
                return;
            }

            if(!rangeCalculate(it->getActionPoints(), it->getXCord(), it->getYCord(), stoi(words[2]), stoi(words[3])))
            {
                std::cout << "Not enough Action Points\n";
                return;
            }

            //Decreases action points from move and set new Coorinates to unit.
            it->setActionPoints(changeActionPoints(*it, stoi(words[2]), stoi(words[3])));
            it->setXCord(stoi(words[2]));
            it->setYCord(stoi(words[3]));
            return;
        }
    }
}