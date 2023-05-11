#include <string>

class Archer: public AUnit
{
    public:
        Archer() : AUnit('A', 40, 2, 250, 5, 3){}

        ~Archer() override {}
        char getUnitType() override
        {
            return Archer::unitType;
        }

        int getHp() override
        {
            return Archer::basehp;
        }

        int getSpeed() override
        {
            return Archer::speed;
        }

        int getCost() override {
            return Archer::cost;
        }

        int getAttackRange() override{
            return Archer::attackRange;
        }

        int getCreateTime() override
        {
            return Archer::createTime;
        }
};
