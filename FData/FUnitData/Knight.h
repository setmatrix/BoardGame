#include <string>

class Knight: public AUnit
{
    public:
        Knight() : AUnit('K', 70, 5, 400, 1, 5){}

        ~Knight() override {}
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
