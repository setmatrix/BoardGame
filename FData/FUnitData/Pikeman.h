#include "AUnit/AUnit.h"
#include <string>

class Pikeman: private AUnit
{
    private:
        std::string name="Pikeman";
    public:
        Pikeman() : AUnit(50, 2, 200, 2, 3){}
};