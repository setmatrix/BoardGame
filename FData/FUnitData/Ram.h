#include "AUnit/AUnit.h"
#include <string>

class Ram: private AUnit
{
    private:
        std::string name="Ram";
    public:
        Ram() : AUnit(90, 2, 500, 1, 4){}
};
