#include <string>

class Archer: public AUnit
{
    public:
        Archer() : AUnit('A', 40, 2, 250, 5, 3){}

        ~Archer() override {}
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
