#include <string>

class Knight: public AUnit
{
    public:
        Knight() : AUnit('K', 70, 5, 400, 1, 5){}

        ~Knight() override {}
        char getUnitType() override
        {
            return Knight::unitType;
        }
        int getHp() override
        {
            return Knight::basehp;
        }
        int getSpeed() override
        {
            return Knight::speed;
        }
        int getCost() override {
            return Knight::cost;
        }
        int getAttackRange() override{
            return Knight::attackRange;
        }
        int getBuildTime() override
        {
            return Knight::buildTime;
        }
};
