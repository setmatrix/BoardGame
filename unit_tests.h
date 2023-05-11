#include <iostream>
#include <cassert>
#include <string.h>
#include <iterator>

#include "unitgame.cpp"


/* CHECK BASE STATE (CREATED/INBUILD/WAITING*/
void createDeleteDefaultBaseObject()
{
    Base *base = new Base(0, 'T', 0, 0);

    std::string getDataFromBase = std::string() + std::to_string(base->getIndex()) + " " +
        base->getBaseLetter() + " " + std::to_string(base->getXCord()) + " " + std::to_string(base->getYCord())
        + " " + std::to_string(base->getIsOnBuild()) + " " + base->getUnitType() + " " + std::to_string(base->getTimeToBuild());
    assert(getDataFromBase.compare("0 T 0 0 false 0 -1"));
    
    delete base;
}

void checkBuildStateBase()
{
    Base *base = new Base(0, 'T', 0, 0);

    Archer* a = new Archer();

    base->addUnitToBuild(*a);

    std::string getDataFromBase = std::string() + base->getUnitType() + " " + std::to_string(base->getTimeToBuild());

    std::cout << getDataFromBase << std::endl;

    std::string getDataFromArcher = std::string() + a->getUnitType() + " " + std::to_string(a->getBuildTime());

    assert(getDataFromBase == getDataFromArcher);
    
    delete base;
    delete a;
}

void createUnit()
{
    Base *base = new Base(0, 'T', 0, 0);
    Archer* a = new Archer();
    base->addUnitToBuild(*a);

    for(int i=0; i < a->getBuildTime(); i++)
    {
        base->setTimeToBuild(base->getTimeToBuild() - 1);
    }
    base->isNotBuilding();
    
    std::cout << base->getTimeToBuild() << std::endl;
    
    assert(base->getIsOnBuild() == 0);

    delete base;
    delete a;
}

void createDeletePlayer()
{
    Player* player = new Player(0, 'T', 0, 0);

    delete player;
}

/* CHECK PLAYER */
void addUnitToList()
{
    Player* player = new Player(0, 'T', 0, 0);
    Knight* k = new Knight();
    UnitOnBoard* u = new UnitOnBoard(
        player->getBaseData()->getUnitType(), 
        1, 
        player->getBaseData()->getXCord(), 
        player->getBaseData()->getYCord(),
        k->getHp(),
        k->getSpeed(),
        k->getAttackRange(),
    player->getBaseData()->getBaseLetter());
    player->addUnit(*u);

    std::list<UnitOnBoard> list = player->getUnitList();

    std::list<UnitOnBoard>::iterator it = list.begin();

    std::string unitFromListData = std::string() + it->getUnitType() + " "
        + std::to_string(it->getHp()) + " " + std::to_string(it->getSpeed()) + " " + std::to_string(it->getAttackRange());

    std::string unitCreatedData = std::string() + k->getUnitType() + " "
        + std::to_string(k->getHp()) + " " + std::to_string(k->getSpeed()) + " " + std::to_string(k->getAttackRange());
    
    assert(unitFromListData.compare(unitCreatedData));

    delete k;
    list.clear();
    delete u;
    delete player;
}

void deleteUnitFromListPlayer()
{
    Player* player = new Player(0, 'T', 0, 0);
    Knight* k = new Knight();
    UnitOnBoard* u = new UnitOnBoard(
        player->getBaseData()->getUnitType(), 
        1, 
        player->getBaseData()->getXCord(), 
        player->getBaseData()->getYCord(),
        k->getHp(),
        k->getSpeed(),
        k->getAttackRange(),
    player->getBaseData()->getBaseLetter());
    player->addUnit(*u);

    player->deleteUnit(*u);

    assert(player->getUnitList().size() == 0);

    delete k;
    delete u;
    delete player;
}