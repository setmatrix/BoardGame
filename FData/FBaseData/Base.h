#include "ABase/ABase.h"
#include <string>
#include "../FUnitData/AUnit/AUnit.h"

class Base: private ABase
{
    private:
        int index;
        char baseLetter = 'B';
        char owner;
        int xCord;
        int yCord;
        bool isbuilding;
        char unitType;
        int timeToCreateUnit;
    public:
        Base(int _index, char _owner, int _xCord, 
        int _yCord, bool _isbuilding = false, char _unitType = '0', int _timeToCreateUnit = -1) : ABase(200, 0){
            Base::index = _index;
            Base::owner = _owner;
            Base::xCord = _xCord;
            Base::yCord = _yCord;
            Base::unitType = '0';

            if (_isbuilding)
            {
                Base::isbuilding = true;               
            }
            else {
                Base::isbuilding = false;
            }
            Base::unitType = unitType;
            Base::timeToCreateUnit = _timeToCreateUnit; 
        }

        ~Base() override {}

        int getHp() override
        {
            return Base::hp;
        }
        
        void setHp(int _hp) override
        {
            Base::hp = _hp;
        }
        int getSpeed() override{
            return Base::speed;
        }

        int getIndex()
        {
            return Base::index;
        }

        char getBaseLetter()
        {
            return Base::baseLetter;
        }

        int getXCord() {return Base::xCord;}

        int getYCord() {return Base::yCord;}

        bool isBuilding() {return Base::isbuilding;}

        void Building(bool _isbuilding) {Base::isbuilding = _isbuilding;}

        char getUnitType() {return Base::unitType;}

        int getTimeToCreate() {return Base::timeToCreateUnit;}

        void setTimeToCreateUnit(int _timeToCreateUnit){Base::timeToCreateUnit = _timeToCreateUnit;}

        //Method to add Unit to build and changes state for base
        void addUnitToCreate(AUnit _unit)
        {
            if (!isBuilding())
            {
                Base::isbuilding = true;
                Base::unitType = _unit.getUnitType();
                Base::timeToCreateUnit = _unit.getCreateTime();
            }
        }

        char getOwner()
        {
            return Base::owner;
        }

        //Resets base state
        void isNotBuilding()
        {
            if (Base::getTimeToCreate() > 0)
            {
                return;
            }
            Base::isbuilding = false;
            Base::unitType = '0';
            Base::timeToCreateUnit = -1; 
        }
};
