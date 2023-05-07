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
            this->index = _index;
            this->baseLetter = _baseLetter;
            this->xCord = _xCord;
            this->yCord = _yCord;
            this->unitType = '0';

            if (_isOnBuild)
            {
                this-> isOnBuild = true;
                this->unitType = unitType;
                this->timeToBuild = timeToBuild;                
            }
        }
        int getHp() override
        {
            return hp;
        }
        void setHp(int _hp) override
        {
            this->hp = _hp;
        }
        int getSpeed() override{
            return speed;
        }

        int getIndex()
        {
            return index;
        }

        char getBaseLetter()
        {
            return baseLetter;
        }
        int getXCord() {return xCord;}
        int getYCord() {return yCord;}
        bool getIsOnBuild() {return isOnBuild;}
        void setIsOnBuild(bool _onBuild) {this->isOnBuild = _onBuild;}
        char getUnitType() {return unitType;}
        int getTimeToBuild() {return timeToBuild;}
        void setTimeToBuild(int _timeToBuild){this->timeToBuild = _timeToBuild;}

        void addUnitToBuild(AUnit _unit)
        {
            if (!getIsOnBuild())
            {
                this->isOnBuild = true;
                this->unitType = _unit.getUnitType();
                this->timeToBuild = _unit.getBuildTime();
            }
        }
        void isNotBuilding()
        {
            this-> isOnBuild = false;
            this->unitType = '0';
            this->timeToBuild = -1;  
        }
};
