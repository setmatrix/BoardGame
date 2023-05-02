#include "AUnit/AUnit.h"
#include <string>

class Knight: private AUnit
{
    private:
        std::string name="Knight";
    public:
        Knight() : AUnit(70, 5, 400, 1, 5){}
};
