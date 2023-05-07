#include <string>

class Swordsman: public AUnit
{
    public:
        Swordsman() : AUnit('S', 60, 2, 250, 1, 3){}
        
        ~Swordsman() override {}
        
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