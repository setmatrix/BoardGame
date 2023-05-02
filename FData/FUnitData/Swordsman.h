#include "AUnit/AUnit.h"
#include <string>

class Swordsman: private AUnit
{
    private:
        std::string name="Swordsman";
    public:
        Swordsman() : AUnit(60, 2, 250, 1, 3){}
};