#include <iostream>
#include <cassert>
#include "FUnitOnBoard/UnitOnBoard.h"
#include <string.h>

void testUnitOnBoard() {
    UnitOnBoard unitOnBoard('P', 'K', 1, 0, 0, 100);
    std::string res;
    res = unitOnBoard.printUnit();
    assert(res.compare("P K 1 0 0 100") == 0);

    delete res;
}