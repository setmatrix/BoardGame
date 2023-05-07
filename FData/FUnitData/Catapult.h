#include <string>

class Catapult: public AUnit
{
    public:
        Catapult() : AUnit('C', 50, 2, 800, 7, 6){}
        ~Catapult() override {}
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
