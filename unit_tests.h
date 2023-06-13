#include <iostream>
#include <cassert>
#include <string.h>
#include <iterator>
#include <memory>

#include "unitgame.cpp"


/* CHECK BASE STATE (CREATED/INBUILD/WAITING*/
void createDeleteDefaultBaseObject()
{
    std::unique_ptr<Base> base(new Base(0, 'T', 0, 0), std::default_delete<Base>());

    std::string getDataFromBase = std::string() + std::to_string(base->getIndex()) + " " +
        base->getOwner() + " " + std::to_string(base->getXCord()) + " " + std::to_string(base->getYCord())
        + " " + std::to_string(base->isBuilding()) + " " + base->getUnitType() + " " + std::to_string(base->getTimeToCreate());
    assert(getDataFromBase.compare("0 T 0 0 false 0 -1"));
}

void checkBuildStateBase()
{
    std::unique_ptr<Base> base(new Base(0, 'T', 0, 0), std::default_delete<Base>());

    std::unique_ptr<Archer> a(new Archer());

    base->addUnitToCreate(*a);

    std::string getDataFromBase = std::string() + base->getUnitType() + " " + std::to_string(base->getTimeToCreate());

    std::cout << getDataFromBase << std::endl;

    std::string getDataFromArcher = std::string() + a->getUnitType() + " " + std::to_string(a->getCreateTime());

    assert(getDataFromBase == getDataFromArcher);
}

void createUnit()
{
    std::unique_ptr<Base> base(new Base(0, 'T', 0, 0), std::default_delete<Base>());
    std::unique_ptr<Archer> a(new Archer());

    base->addUnitToCreate(*a);

    for(int i=0; i < a->getCreateTime(); i++)
    {
        base->setTimeToCreateUnit(base->getTimeToCreate() - 1);
    }
    base->isNotBuilding();
    
    std::cout << base->getTimeToCreate() << std::endl;
    
    assert(base->isBuilding() == 0);
}

void createDeletePlayer()
{
    std::unique_ptr<Player> player(new Player(0, 'T', 0, 0));
}

/* CHECK PLAYER */
void addUnitToList()
{
    std::unique_ptr<Player> player(new Player(0, 'T', 0, 0));
    std::unique_ptr<Knight> k(new Knight());
    std::unique_ptr<UnitOnBoard> u(new UnitOnBoard(
        player->getBaseData()->getUnitType(), 
        1, 
        player->getBaseData()->getXCord(), 
        player->getBaseData()->getYCord(),
        k->getHp(),
        k->getSpeed(),
        k->getAttackRange(),
        player->getBaseData()->getOwner()));
    player->addUnit(*u);

    std::list<UnitOnBoard> list = player->getUnitList();

    std::list<UnitOnBoard>::iterator it = list.begin();

    std::string unitFromListData = std::string() + it->getUnitType() + " "
        + std::to_string(it->getHp()) + " " + std::to_string(it->getSpeed()) + " " + std::to_string(it->getAttackRange());

    std::string unitCreatedData = std::string() + k->getUnitType() + " "
        + std::to_string(k->getHp()) + " " + std::to_string(k->getSpeed()) + " " + std::to_string(k->getAttackRange());
    
    assert(unitFromListData.compare(unitCreatedData));

    list.clear();
}

void deleteUnitFromListPlayer()
{
    std::unique_ptr<Player> player(new Player(0, 'T', 0, 0));
    std::unique_ptr<Knight> k(new Knight());
    std::unique_ptr<UnitOnBoard> u(new UnitOnBoard(
        player->getBaseData()->getUnitType(), 
        1, 
        player->getBaseData()->getXCord(), 
        player->getBaseData()->getYCord(),
        k->getHp(),
        k->getSpeed(),
        k->getAttackRange(),
        player->getBaseData()->getOwner()));
    player->addUnit(*u);

    player->deleteUnit(*u);

    assert(player->getUnitList().size() == 0);
}