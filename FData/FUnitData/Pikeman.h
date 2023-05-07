#include <string>

class Pikeman: public AUnit
{
    public:
        Pikeman() : AUnit('P', 50, 2, 200, 2, 3){}
        
        ~Pikeman() override {}
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
                case 'K':{return 35;}
                case 'S':{return 15;}
                case 'A':{return 15;}
                case 'P':{return 15;}
                case 'C':{return 15;}
                case 'R':{return 10;}
                case 'W':{return 15;}
                case 'B':{return 10;}
            }
        }
};