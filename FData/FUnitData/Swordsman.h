#include <string>

class Swordsman: public AUnit
{
    public:
        Swordsman() : AUnit('S', 60, 2, 250, 1, 3){}
        
        ~Swordsman() override {}
        
        char getUnitType() override
        {
            return Swordsman::unitType;
        }
        int getHp() override
        {
            return Swordsman::basehp;
        }
        int getSpeed() override
        {
            return Swordsman::speed;
        }
        int getCost() override {
            return Swordsman::cost;
        }
        int getAttackRange() override{
            return Swordsman::attackRange;
        }
        int getBuildTime() override
        {
            return Swordsman::buildTime;
        }
};