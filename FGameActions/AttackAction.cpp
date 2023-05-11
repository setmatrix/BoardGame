#include <string>

// Returns true, if enemy is on range
bool rangeCalculate(int range, int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2) <= range ? true : false);
}

// Decreases action points
int changeActionPoints(UnitOnBoard unit, int x, int y)
{
    int availablePoints = unit.getActionPoints();
    int usingActionPoints = abs(x - unit.getXCord()) + abs(y - unit.getYCord());

    return availablePoints - usingActionPoints;
}

bool AttackBase(Player *actualPlayer, Player *enemyPlayer, std::list<UnitOnBoard>::iterator playerUnit)
{
    // Check, if the base player wants to attack is enemy
    if (actualPlayer->getBaseData()->getOwner() != playerUnit->getOwner())
    {
        // Check, if the base is on range
        if (rangeCalculate(playerUnit->getAttackRange(), playerUnit->getXCord(), playerUnit->getYCord(),
                           enemyPlayer->getBaseData()->getXCord(),
                           enemyPlayer->getBaseData()->getYCord()))
        {
            int actualBaseHp = enemyPlayer->getBaseData()->getHp();
            enemyPlayer->getBaseData()->setHp(
                actualBaseHp - AttackOnEnemy(playerUnit->getUnitType(), 'B'));
        }
        else
        {
            std::cout << "Enemy base is out of range\n";
            return false;
        }
        return true;
    }
    else
    {
        std::cout << "Cannot attack your own base\n";
        return false;
    }
    return false;
}

bool AttackUnit(Player *actualPlayer, Player *enemyPlayer, std::list<UnitOnBoard>::iterator playerUnit, std::string *words)
{
    if (enemyPlayer->getUnitList().size() <= 0)
    {
        std::cout << "Your enemy doesn't have units to attack!\n";
        return false;
    }
    // Attack on enemy

    std::list<UnitOnBoard>::iterator enemyUnit = enemyPlayer->getUnitList().begin();

    while (enemyUnit != enemyPlayer->getUnitList().end())
    {
        // Like on previous comentary, get enemy unit id and check, is equal to data from file
        if (enemyUnit->getUnitId() == stoi(words[2]))
        {
            // Check, if is on range
            if (!rangeCalculate(playerUnit->getAttackRange(), playerUnit->getXCord(), playerUnit->getYCord(),
                                enemyUnit->getXCord(), enemyUnit->getYCord()))
            {
                std::cout << "Your enemy is out of range\n";
                return false;
            }
            // Get hp from unit and attackDamage from static method
            int enemyHp = enemyUnit->getHp();
            int attackDamage = AttackOnEnemy(playerUnit->getUnitType(), enemyUnit->getUnitType());

            // Then set hp, substracting from damage.
            enemyUnit->setHp(enemyHp - attackDamage);
            playerUnit->setActionPoints(playerUnit->getActionPoints() - 1);

            // Set flag to true
            playerUnit->setAttacking(true);

            // If unit has 0 or less hp
            if (enemyUnit->getHp() <= 0)
            {
                // Delete from list of units
                actualPlayer->deleteUnit(*enemyUnit);
            }
            return true;
        }
    }
    return false;
}

bool AttackAction(Player *actualPlayer, Player *enemyPlayer, std::string *words)
{
    if (actualPlayer->getUnitList().size() <= 0)
    {
        std::cout << "You can't attack if you don't have an unit.\n";
        return false;
    }

    std::list<UnitOnBoard>::iterator playerUnit = actualPlayer->getUnitList().begin();

    while (playerUnit != actualPlayer->getUnitList().end())
    {
        // First, get unit id and check, is equal to data from file
        if (playerUnit->getUnitId() == stoi(words[0]))
        {
            // Then check, if unit was Attacking
            if (!playerUnit->getAttack())
            {
                std::cout << "Your unit already attacked\n";
                return false;
            }
            if ((stoi(words[2]) == actualPlayer->getBaseData()->getXCord() && stoi(words[3]) == actualPlayer->getBaseData()->getYCord()) || (stoi(words[2]) == enemyPlayer->getBaseData()->getXCord() && stoi(words[3]) == enemyPlayer->getBaseData()->getYCord()))
            {
                // Attack on base
                return AttackBase(actualPlayer, enemyPlayer, playerUnit);
            }
            else
            {
                // Attack on unit
                return AttackUnit(actualPlayer, enemyPlayer, playerUnit, words);
            }
            break;
        }
    }
    return false;
}