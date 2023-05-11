#include <string>

//If enemy is on place x and y, returns true
bool IsEnemyUnitOnBoard(Player* enemyPlayer, int x, int y)
{
    std::list<UnitOnBoard> units = enemyPlayer->getUnitList();

    for(UnitOnBoard unit : units)
    {
        if (unit.getXCord() == x && unit.getYCord() == y)
        {
            units.clear();
            return true;
        }
    }
    units.clear();
    return false;
}

void MoveAction(Player* actualPlayer, Player* enemyPlayer, std::string *words, char** board, int boardX, int boardY)
{
    if (actualPlayer->getUnitList().size() <= 0)
    {
        std::cout << "You haven't an unit to play\n";
        return;
    }

    std::list<UnitOnBoard>::iterator it = actualPlayer->getUnitList().begin();

    while (it != actualPlayer->getUnitList().end())
    {
        //Check if unit Id is equal to Id from file.
        if (it->getUnitId() == stoi(words[0]))
        {
            UnitOnBoard& s(*it);
            //Then check, if Cordinates are on board
            if (stoi(words[2]) < 0 || stoi(words[2]) > boardX || stoi(words[3]) < 0 || stoi(words[3]) > boardY)
            {
                std::cout << "Your coordication are outside from board\n";
                return;
            }
            
            std::string field(board[(stoi(words[2]), stoi(words[3]))]);
            std::string getPlayerBase;
            getPlayerBase = enemyPlayer->getBaseData()->getOwner();
            //Lastly, check if Coordinates from file are pointing to road, base, or cave and are on range to unit.
            if (!field.compare("0") && !field.compare("6") && !field.compare(getPlayerBase))
            {
                std::cout << "This place is an obstacle or enemy player's base\n";
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
            s.setActionPoints(changeActionPoints(*it, stoi(words[2]), stoi(words[3])));
            s.setXCord(stoi(words[2]));
            s.setYCord(stoi(words[3]));
            return;
        }
    }
    return;
}