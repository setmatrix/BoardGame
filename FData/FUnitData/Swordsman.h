#include <string>

class Swordsman: public AUnit
{
    public:
        Swordsman() : AUnit('S', 60, 2, 250, 1, 3){}
        
        ~Swordsman() override {}
        
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
                case 'K':{return 30;}
                case 'S':{return 30;}
                case 'A':{return 30;}
                case 'P':{return 20;}
                case 'C':{return 20;}
                case 'R':{return 30;}
                case 'W':{return 30;}
                case 'B':{return 30;}
            }
        }
};