class Ram: public AUnit
{
    public:
        Ram() : AUnit('R', 90, 2, 500, 1, 4){}
        
        ~Ram() override {}
        char getUnitType() override
        {
            return this->unitType;
        }
        int getHp() override
        {
            return this->basehp;
        }
        int getSpeed() override
        {
            return this->speed;
        }
        int getCost() override {
            return this->cost;
        }
        int getAttackRange() override{
            return this->attackRange;
        }
        int getBuildTime() override
        {
            return this->buildTime;
        }
};
