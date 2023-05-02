#include "AUnit/AUnit.h"
#include <string>

class Worker: private AUnit
{
    private:
        std::string name="Worker";
    public:
        Worker() : AUnit(20, 2, 100, 1, 2){}
};
