#include <string>

class Swordsman: public AUnit
{
    public:
        Swordsman() : AUnit('S', 60, 2, 250, 1, 3){}
        
        ~Swordsman() override {}
        
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