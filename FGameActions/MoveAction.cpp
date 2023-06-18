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

bool MoveAction(Player* actualPlayer, Player* enemyPlayer, std::vector<std::string> words, char** board, int boardX, int boardY)
{
    if (actualPlayer->getUnitList().size() <= 0)
    {
        throw std::string("You don't have an unit to play");
    }

    int actualIndex = 0;
    int max = actualPlayer->getUnitList().size();

    std::list<UnitOnBoard>::iterator it = actualPlayer->getUnitList().begin();

    while (it != actualPlayer->getUnitList().end())
    {
        if(actualIndex >= max)
        {
            return false;
        }
        //Check if unit Id is equal to Id from file.
        if (it->getUnitId() == stoi(words[0]))
        {
            //Then check, if Cordinates are on board
            if (stoi(words[2]) < 0 || stoi(words[2]) > boardX || stoi(words[3]) < 0 || stoi(words[3]) > boardY)
            {
                throw std::string("Your coordication are outside from board");
            }
            
            std::string field(board[(stoi(words[2]), stoi(words[3]))]);
            std::string getPlayerBase;

            getPlayerBase = enemyPlayer->getBaseData()->getOwner();
            //Lastly, check if Coordinates from file are pointing to road, base, or cave and are on range to unit.
            if (!field.compare("0") && !field.compare("6") && !field.compare(getPlayerBase))
            {
                throw std::string("This place is an obstacle or enemy player's base");
            }

            if(!rangeCalculate(it->getActionPoints(), it->getXCord(), it->getYCord(), stoi(words[2]), stoi(words[3])))
            {
                throw std::string("Not enough Action Points");
            }

            if (IsEnemyUnitOnBoard(enemyPlayer, stoi(words[2]), stoi(words[3])))
            {
                throw std::string("Enemy on this coordination exists");
            }
            break;
        }
        actualIndex += 1;
    }

    //For the problem with overriding memory of enemyPlayer Pointer,
    //I need to create another while function to update an unit
    
    actualIndex = 0;
    it = actualPlayer->getUnitList().begin();
    while (it != actualPlayer->getUnitList().end())
    {
        if(actualIndex >= max)
        {
            return false;
        }
        if (it->getUnitId() == stoi(words[0]))
        {
            //Decreases action points from move and set new Coorinates to unit.
            UnitOnBoard updatedUnit(it->getUnitType(), it->getUnitId(), stoi(words[2]), stoi(words[3]), it->getHp(), it->getSpeed(), it->getAttackRange(), it->getOwner());
            updatedUnit.setActionPoints(changeActionPoints(*it, stoi(words[2]), stoi(words[3])));
            actualPlayer->deleteUnit(*it);
            actualPlayer->addUnit(updatedUnit);
            return true;
        }
        actualIndex += 1;
    }

    throw std::string("List of units are empty");
    return false;
}