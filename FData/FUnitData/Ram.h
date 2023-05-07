class Ram: public AUnit
{
    public:
        Ram() : AUnit('R', 90, 2, 500, 1, 4){}
        
        ~Ram() override {}
        char getUnitType() override
        {
            return unitType;
        }
        int getHp() override
        {
            return basehp;
        }
        int getSpeed() override
        {
            return speed;
        }
        int getCost() override {
            return cost;
        }
        int getAttackRange() override{
            return attackRange;
        }
        int getBuildTime() override
        {
            return buildTime;
        }
};
