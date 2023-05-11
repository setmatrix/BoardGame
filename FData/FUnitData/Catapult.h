#include <string>

class Catapult: public AUnit
{
    public:
        Catapult() : AUnit('C', 50, 2, 800, 7, 6){}
        ~Catapult() override {}
        char getUnitType() override
        {
            return Catapult::unitType;
        }
        int getHp() override
        {
            return Catapult::basehp;
        }
        int getSpeed() override
        {
            return Catapult::speed;
        }
        int getCost() override {
            return Catapult::cost;
        }
        int getAttackRange() override{
            return Catapult::attackRange;
        }
        int getCreateTime() override
        {
            return Catapult::createTime;
        }
};
