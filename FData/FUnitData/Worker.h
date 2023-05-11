#include <string>

class Worker: public AUnit
{
    public:
        Worker() : AUnit('W', 20, 2, 100, 1, 2){}

        ~Worker() override {}
        char getUnitType() override
        {
            return Worker::unitType;
        }
        int getHp() override
        {
            return Worker::basehp;
        }
        int getSpeed() override
        {
            return Worker::speed;
        }
        int getCost() override {
            return Worker::cost;
        }
        int getAttackRange() override{
            return Worker::attackRange;
        }
        int getCreateTime() override
        {
            return Worker::createTime;
        }
};
