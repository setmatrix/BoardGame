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
            AUnit::unitType = _unitType;
            AUnit::basehp = _basehp;
            AUnit::speed = _speed;
            AUnit::cost = _cost;
            AUnit::attackRange = _attackRange;
            AUnit::buildTime = _buildTime;
        }
        virtual ~AUnit(){}
        virtual char getUnitType()
        {
            return AUnit::unitType;
        }
        virtual int getHp(){return AUnit::basehp;}
        virtual int getSpeed(){return AUnit::speed;}
        virtual int getCost(){return AUnit::cost;}
        virtual int getAttackRange(){return AUnit::attackRange;}
        virtual int getBuildTime(){return AUnit::buildTime;}
};