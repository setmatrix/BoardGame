#include "ABase/ABase.h"
#include <string>
#include "../FUnitData/AUnit/AUnit.h"

class Base: private ABase
{
    private:
        int index;
        char baseLetter;
        int xCord;
        int yCord;
        bool isOnBuild;
        char unitType;
        int timeToBuild;
    public:
        Base(int _index, char _baseLetter, int _xCord, 
        int _yCord, bool _isOnBuild = false, char _unitType = '0', int timeToBuild = -1) : ABase(200, 0){
            Base::index = _index;
            Base::baseLetter = _baseLetter;
            Base::xCord = _xCord;
            Base::yCord = _yCord;
            Base::unitType = '0';

            if (_isOnBuild)
            {
                Base::isOnBuild = true;               
            }
            else {
                Base::isOnBuild = false;
            }
            Base::unitType = unitType;
            Base::timeToBuild = timeToBuild; 
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

        bool getIsOnBuild() {return Base::isOnBuild;}

        void setIsOnBuild(bool _onBuild) {Base::isOnBuild = _onBuild;}

        char getUnitType() {return Base::unitType;}

        int getTimeToBuild() {return Base::timeToBuild;}

        void setTimeToBuild(int _timeToBuild){Base::timeToBuild = _timeToBuild;}

        //Method to add Unit to build and changes state for base
        void addUnitToBuild(AUnit _unit)
        {
            if (!getIsOnBuild())
            {
                Base::isOnBuild = true;
                Base::unitType = _unit.getUnitType();
                Base::timeToBuild = _unit.getBuildTime();
            }
        }

        //Resets base state
        void isNotBuilding()
        {
            if (Base::getTimeToBuild() > 0)
            {
                return;
            }
            Base::isOnBuild = false;
            Base::unitType = '0';
            Base::timeToBuild = -1; 
        }
};
