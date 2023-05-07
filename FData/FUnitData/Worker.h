#include <string>

class Worker: public AUnit
{
    public:
        Worker() : AUnit('W', 20, 2, 100, 1, 2){}

        ~Worker() override {}
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

        int takeDamage (char _unitType) override
        {
            switch(_unitType)
            {
                case 'K':{return 5;}
                case 'S':{return 5;}
                case 'A':{return 5;}
                case 'P':{return 5;}
                case 'C':{return 5;}
                case 'R':{return 5;}
                case 'W':{return 5;}
                case 'B':{return 1;}
            }
        }
};
