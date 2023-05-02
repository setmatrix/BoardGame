#include "AUnit/AUnit.h"
#include <string>

class Catapult: private AUnit
{
    private:
        std::string name="Catapult";
    public:
        Catapult() : AUnit(50, 2, 800, 7, 6){}
};
