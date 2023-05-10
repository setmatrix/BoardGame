class Ram: public AUnit
{
    public:
        Ram() : AUnit('R', 90, 2, 500, 1, 4){}
        
        ~Ram() override {}
        char getUnitType() override
        {
            return Ram::unitType;
        }
        int getHp() override
        {
            return Ram::basehp;
        }
        int getSpeed() override
        {
            return Ram::speed;
        }
        int getCost() override {
            return Ram::cost;
        }
        int getAttackRange() override{
            return Ram::attackRange;
        }
        int getBuildTime() override
        {
            return Ram::buildTime;
        }
};
