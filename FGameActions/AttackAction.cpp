#include <string>

//Returns true, if enemy is on range
bool rangeCalculate(int range, int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2) <= range ? true: false);
}

//Decreases action points
int changeActionPoints(UnitOnBoard unit, int x, int y) {
    int availablePoints = unit.getActionPoints();
    int usingActionPoints = abs(x - unit.getXCord()) + abs(y - unit.getYCord());

    return availablePoints - usingActionPoints;
}

void AttackBase(Player actualPlayer, Player enemyPlayer, std::list<UnitOnBoard>::iterator playerUnit)
{
    //Check, if the base player wants to attack is enemy
    if(actualPlayer.getBase().getBaseLetter() != playerUnit->getPlayerBase())
    {
        //Check, if the base is on range
        if(rangeCalculate(playerUnit->getRange(), playerUnit->getXCord(), playerUnit->getYCord(),
            enemyPlayer.getBase().getXCord(), 
            enemyPlayer.getBase().getYCord()))
        {
            int actualBaseHp = enemyPlayer.getBase().getHp();
            enemyPlayer.getBase().setHp(
            actualBaseHp - AttackOnBoard::AttackOnEnemy(playerUnit->getUnitType(), 'B'));
        }
        else {
            std::cout << "Enemy base is out of range\n";
        }
    }
    else
    {
    std::cout << "Cannot attack your own base\n";
    }
}

void AttackUnit(Player actualPlayer, Player enemyPlayer, std::list<UnitOnBoard>::iterator playerUnit, std::string *words)
{
    if (enemyPlayer.getUnitList().size() <= 0)
    {
        std::cout << "Your enemy doesn't have units to attack!\n";
        return;
    }
    //Attack on enemy
    for (std::list<UnitOnBoard>::iterator enemyUnit= enemyPlayer.getUnitList().begin(); 
        enemyUnit != enemyPlayer.getUnitList().end(); ++enemyUnit)
    {
        //Like on previous comentary, get enemy unit id and check, is equal to data from file
        if (enemyUnit->getUnitId() == stoi(words[2]))
        {
            //Check, if is on range
            if(!rangeCalculate(playerUnit->getRange(), playerUnit->getXCord(), playerUnit->getYCord(),
                enemyUnit->getXCord(), enemyUnit->getYCord()))
            {
                std::cout << "Your enemy is out of range\n";
                return;
            }
            //Get hp from unit and attackDamage from static method 
            int enemyHp = enemyUnit->getHp();
            int attackDamage = AttackOnBoard::AttackOnEnemy(playerUnit->getUnitType(), enemyUnit->getUnitType());

            //Then set hp, substracting from damage.
            enemyUnit->setHp(enemyHp - attackDamage);
            playerUnit->setActionPoints(playerUnit->getActionPoints() - 1);

            //Set flag to true
            playerUnit->SetwasAttacking(true);

            //If unit has 0 or less hp
            if(enemyUnit->getHp() <= 0)
            {   
                //Delete from list of units
                actualPlayer.deleteUnit(*enemyUnit);
            }
            return;
        }
    }
}

void AttackAction(Player actualPlayer, Player enemyPlayer, std::string *words)
{
    for (std::list<UnitOnBoard>::iterator playerUnit = actualPlayer.getUnitList().begin(); 
        playerUnit != actualPlayer.getUnitList().end(); ++playerUnit)
    {
        //First, get unit id and check, is equal to data from file
        if (playerUnit->getUnitId() == stoi(words[0]))
        {
            //Then check, if unit was Attacking
            if (!playerUnit->getwasAttacking())
            {
                std::cout << "Your unit already attacked\n";
                return;
            }
            //Attack on base
            if((stoi(words[2]) == 0 && stoi(words[3]) == 0) || (stoi(words[2]) == 4 && stoi(words[3]) == 31))
            {
                AttackBase(actualPlayer, enemyPlayer, playerUnit);
            } 
            else
            {
                AttackUnit(actualPlayer, enemyPlayer, playerUnit, words);
            }
            break;
        }
    }
    return;
}