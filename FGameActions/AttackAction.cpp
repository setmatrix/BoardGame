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

bool AttackBase(Player *enemyPlayer, UnitOnBoard& playerUnit)
{
    // Check, if the base is on range
    if (rangeCalculate(playerUnit.getAttackRange(), playerUnit.getXCord(), playerUnit.getYCord(),
                        enemyPlayer->getBaseData()->getXCord(),
                       enemyPlayer->getBaseData()->getYCord()))
    {
        int actualBaseHp = enemyPlayer->getBaseData()->getHp();
        int unitOnDamage = AttackOnEnemy(playerUnit.getUnitType(), 'B');
        
        enemyPlayer->getBaseData()->setHp(actualBaseHp - unitOnDamage);
        playerUnit.setAttacking(true);
        return true;
    }
    else
    {
        throw std::string("Enemy base is out of range");
    }
    return false;
}

bool AttackUnit(Player *enemyPlayer, UnitOnBoard playerUnit, std::vector<std::string> words)
{
    if (enemyPlayer->getUnitList().size() <= 0)
    {
        throw std::string("Your enemy doesn't have units to attack!");
    }

    // Attack on enemy
    std::list<UnitOnBoard>::iterator enemyUnit = enemyPlayer->getUnitList().begin();

    int actualIndex = 0;
    int maxIndex = enemyPlayer->getUnitList().size();

    while (enemyUnit != enemyPlayer->getUnitList().end())
    {
        if(actualIndex >= maxIndex)
        {
            break;
        }
        // Get enemy unit id and check, is equal to data from file
        if (enemyUnit->getUnitId() == stoi(words[2]))
        {
            // Check, if is on range
            if (!rangeCalculate(playerUnit.getAttackRange(), playerUnit.getXCord(), playerUnit.getYCord(),
                                enemyUnit->getXCord(), enemyUnit->getYCord()))
            {
                throw std::string("Your enemy is out of range!");
            }
            // Get hp from unit and attackDamage from static method
            int enemyHp = enemyUnit->getHp();
            int attackDamage = AttackOnEnemy(playerUnit.getUnitType(), enemyUnit->getUnitType());

            // Then set hp, substracting from damage.
            enemyUnit->setHp(enemyHp - attackDamage);
            playerUnit.setActionPoints(playerUnit.getActionPoints() - 1);

            // Set flag to true
            playerUnit.setAttacking(true);

            // If unit has 0 or less hp
            if (enemyUnit->getHp() <= 0)
            {
                // Delete from list of units
                enemyPlayer->deleteUnit(*enemyUnit);
            }
            return true;
        }
        actualIndex += 1;
    }
    return false;
}

bool AttackAction(Player *actualPlayer, Player *enemyPlayer, std::vector<std::string> words)
{
    if (actualPlayer->getUnitList().size() <= 0)
    {
        throw std::string("You can't attack if you don't have an unit.");
    }

    std::list<UnitOnBoard>::iterator playerUnit = actualPlayer->getUnitList().begin();

    while (playerUnit != actualPlayer->getUnitList().end())
    {
        // First, get unit id and check, is equal to data from file
        if (playerUnit->getUnitId() == stoi(words[0]))
        {
            // Then check, if unit was Attacking
            if (playerUnit->getAttack())
            {
                throw std::string("Your unit already attacked.");
            }
            if (stoi(words[2]) == enemyPlayer->getBaseData()->getIndex())
            {
                // Attack on base
                return AttackBase(enemyPlayer, *playerUnit);
            }
            else
            {
                // Attack on unit
                return AttackUnit(enemyPlayer, *playerUnit, words);
            }
            break;
        }
    }
    return false;
}