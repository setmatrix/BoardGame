#include <string>

class Catapult: public AUnit
{
    public:
        Catapult() : AUnit('C', 50, 2, 800, 7, 6){}
        ~Catapult() override {}
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
                case 'K':{return 40;}
                case 'S':{return 40;}
                case 'A':{return 40;}
                case 'P':{return 40;}
                case 'C':{return 40;}
                case 'R':{return 40;}
                case 'W':{return 40;}
                case 'B':{return 50;}
            }
        }
};
