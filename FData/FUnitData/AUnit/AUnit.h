class AUnit
{
    protected:
        char unitType;
        int basehp;
        int speed;
        int cost;
        int attackRange;
        int buildTime;

    public:
        AUnit(char _unitType, int _basehp, int _speed, int _cost, int _attackRange, int _buildTime)
        {
            this->unitType = _unitType;
            this->basehp = _basehp;
            this->speed = _speed;
            this->cost = _cost;
            this->attackRange = _attackRange;
            this->buildTime = _buildTime;
        }
        virtual ~AUnit(){}
        virtual char getUnitType()
        {
            return unitType;
        }
        virtual int getHp(){return basehp;}
        virtual int getSpeed(){return speed;}
        virtual int getCost(){return cost;}
        virtual int getAttackRange(){return attackRange;}
        virtual int getBuildTime(){return buildTime;}
        virtual int takeDamage(char unitType) = 0;
};