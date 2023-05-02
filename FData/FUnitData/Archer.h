#include "AUnit/AUnit.h"
#include <string>

class Archer: private AUnit
{
    private:
        std::string name="Archer";
    public:
        Archer() : AUnit(40, 2, 250, 5, 3){}
};
