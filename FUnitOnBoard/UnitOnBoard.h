#include <string>
class UnitOnBoard
{
    // Format linii określającej jednostkę na planszy:
    private:
        char unitType;
        int unitId;
        int xCord;
        int yCord;
        int hp;
        bool wasAttacked = false;
    public:

        UnitOnBoard(char _unitType, int _unitId, int _xCord, int _yCord, int _hp)
        {
            this->unitType = _unitType;
            this->unitId = _unitId;
            this->xCord = _xCord;
            this->yCord = _yCord;
            this->hp = _hp;
        }
        std::string printUnit()
        {
            std::string res = std::string() + unitType + " " + std::to_string(unitId) + " " + std::to_string(xCord)
            + " " + std::to_string(yCord) + " " + std::to_string(hp);
            return res;
        }
        char getUnitType()
        {
            return getUnitType();
        }
        int getUnitId()
        {
            return unitId;
        }
        int getXCord()
        {
            return xCord;
        }
        void setXCord(int _xCord)
        {
            this->xCord = _xCord;
        }
        int getYCord()
        {
            return yCord;
        }
        void setYCord(int _yCord)
        {
            this->yCord = _yCord;
        }
        int getHp()
        {
            return hp;
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
};