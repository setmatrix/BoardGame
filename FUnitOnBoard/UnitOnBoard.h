#include <string>
class UnitOnBoard
{
    // Format linii określającej jednostkę na planszy:
    private:
        char unitType;
        char playerBase;
        int unitId;
        int xCord;
        int yCord;
        int hp;
        bool wasAttacked = false;
        int speed;
        int actionPoints;
        int range;
    public:
        UnitOnBoard(char _unitType, int _unitId, int _xCord, int _yCord, int _hp, int _speed, int _range, char _playerBase)
        {
            this->unitType = _unitType;
            this->unitId = _unitId;
            this->xCord = _xCord;
            this->yCord = _yCord;
            this->hp = _hp;
            this->speed = _speed;
            this->actionPoints = speed;
            this->range = _range;
            this->playerBase = _playerBase;
        }
        //Uses only on test
        std::string printUnit()
        {
            std::string res = std::string() + unitType + " " + std::to_string(unitId) + " " + std::to_string(xCord)
            + " " + std::to_string(yCord) + " " + std::to_string(hp);
            return res;
        }

        char getUnitType()
        {
            return this->unitType;
        }
        int getUnitId()
        {
            return this->unitId;
        }
        int getXCord()
        {
            return this->xCord;
        }
        void setXCord(int _xCord)
        {
            this->xCord = _xCord;
        }
        int getYCord()
        {
            return this->yCord;
        }
        void setYCord(int _yCord)
        {
            this->yCord = _yCord;
        }
        int getHp()
        {
            return this->hp;
        }
        void setHp(int _hp)
        {
            this->hp = _hp;
        }
        void SetwasAttacking(bool _attack)
        {
            this->wasAttacked = _attack;
        }
        bool getwasAttacking()
        {
            return this->wasAttacked;
        }
        int getSpeed()
        {
            return this->speed;
        }
        
        int getActionPoints()
        {
            return this->actionPoints;
        }

        void setActionPoints(int _actionPoints)
        {
            this->actionPoints = _actionPoints;
        }

        int getRange()
        {
            return this->range;
        }

        char getPlayerBase()
        {
            return this->playerBase;
        }

        void resetAction()
        {
            this->actionPoints = speed;
            this->wasAttacked = false;
        }
};