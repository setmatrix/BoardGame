#include <iostream>
#include <cassert>
#include "FUnitOnBoard/UnitOnBoard.h"
#include "FData/FBaseData/Base.h"
#include <string.h>

#include "FData/FUnitData/Archer.h"

/* CHECK BASE STATE (CREATED/INBUILD/*/
void createDefaultBaseObject()
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

    base->addUnitToBuild((AUnit) *a);

    std::string getDataFromBase = std::string() + base->getUnitType() + " " + std::to_string(base->getTimeToBuild());

    std::cout << getDataFromBase << std::endl;

    std::string getDataFromArcher =  std::string() + a->getUnitType() + " " + std::to_string(a->getBuildTime());

    delete base, a;
    assert(getDataFromBase == getDataFromArcher);
}