#include "ABase/ABase.h"
#include <string>

class Base: private ABase
{
    private:
        std::string name="Base";
    public:
        Base() : ABase(200, 0){}
};
