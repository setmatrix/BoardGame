#include <string>

class Pikeman: public AUnit
{
    public:
        Pikeman() : AUnit('P', 50, 2, 200, 2, 3){}
        
        ~Pikeman() override {}
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