#include "UnitOnBoard.h"

class BaseUnitOnBoard: public UnitOnBoard
{
    private:
        char unitProduced;
    public:
        BaseUnitOnBoard(char _unitAffiliation, char _unitType, int _unitId, int _xCord, int _yCord, int _strength, char _unitProduced) 
        : UnitOnBoard(_unitAffiliation, _unitType, _unitId, _xCord, _yCord, _strength)
        {
            this->unitProduced = _unitProduced;
        }
};