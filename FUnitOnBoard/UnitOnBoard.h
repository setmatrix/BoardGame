#include <string>
class UnitOnBoard
{
    // Format linii określającej jednostkę na planszy:
    private:
        char unitType;
        char owner;
        int unitId;
        int xCord;
        int yCord;
        int hp;
        bool attacked = false;
        int speed;
        int actionPoints;
        int attackRange;

    public:
        UnitOnBoard(char _unitType, int _unitId, int _xCord, int _yCord, int _hp, int _speed, int _attackRange, char _owner)
        {
            UnitOnBoard::unitType = _unitType;
            UnitOnBoard::unitId = _unitId;
            UnitOnBoard::xCord = _xCord;
            UnitOnBoard::yCord = _yCord;
            UnitOnBoard::hp = _hp;
            UnitOnBoard::speed = _speed;
            UnitOnBoard::actionPoints = _speed;
            UnitOnBoard::attackRange = _attackRange;
            UnitOnBoard::owner = _owner;
        }

        char getUnitType()
        {
            return UnitOnBoard::unitType;
        }
        int getUnitId()
        {
            return UnitOnBoard::unitId;
        }
        int getXCord()
        {
            return UnitOnBoard::xCord;
        }
        void setXCord(int _xCord)
        {
            UnitOnBoard::xCord = _xCord;
        }
        int getYCord()
        {
            return UnitOnBoard::yCord;
        }
        void setYCord(int _yCord)
        {
            UnitOnBoard::yCord = _yCord;
        }
        int getHp()
        {
            return UnitOnBoard::hp;
        }
        void setHp(int _hp)
        {
            UnitOnBoard::hp = _hp;
        }
        void setAttacking(bool _attacked)
        {
            UnitOnBoard::attacked = _attacked;
        }
        bool getAttack()
        {
            return UnitOnBoard::attacked;
        }
        int getSpeed()
        {
            return UnitOnBoard::speed;
        }

        int getActionPoints()
        {
            return UnitOnBoard::actionPoints;
        }

        void setActionPoints(int _actionPoints)
        {
            UnitOnBoard::actionPoints = _actionPoints;
        }

        int getAttackRange()
        {
            return UnitOnBoard::attackRange;
        }

        char getOwner()
        {
            return UnitOnBoard::owner;
        }

        void resetAction()
        {
            UnitOnBoard::actionPoints = speed;
            UnitOnBoard::attacked = false;
        }
};