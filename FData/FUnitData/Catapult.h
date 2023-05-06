#include <string>

class Catapult: public AUnit
{
    public:
        Catapult() : AUnit('C', 50, 2, 800, 7, 6){}
        ~Catapult() override {}
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
