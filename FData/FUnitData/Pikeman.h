#include <string>

class Pikeman: public AUnit
{
    public:
        Pikeman() : AUnit('P', 50, 2, 200, 2, 3){}
        
        ~Pikeman() override {}
        char getUnitType() override
        {
            return Pikeman::unitType;
        }
        int getHp() override
        {
            return Pikeman::basehp;
        }
        int getSpeed() override
        {
            return Pikeman::speed;
        }
        int getCost() override {
            return Pikeman::cost;
        }
        int getAttackRange() override{
            return Pikeman::attackRange;
        }
        int getBuildTime() override
        {
            return Pikeman::buildTime;
        }
};