#include <string>

class Worker: public AUnit
{
    public:
        Worker() : AUnit('W', 20, 2, 100, 1, 2){}

        ~Worker() override {}
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
