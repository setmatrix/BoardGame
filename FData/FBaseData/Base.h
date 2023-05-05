#include "ABase/ABase.h"
#include <string>

class Base: private ABase
{
    private:
        int index;
        char baseLetter;
        int xCord;
        int yCord;
    public:
        Base(int _index, char _baseLetter, int _xCord, int _yCord) : ABase(200, 0){
            this->index = _index;
            this->baseLetter = _baseLetter;
            this->xCord = _xCord;
            this->yCord = _yCord;
        }
};
