#include <string>

class Archer: public AUnit
{
    public:
        Archer() : AUnit('A', 40, 2, 250, 5, 3){}

        ~Archer() override {}
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
