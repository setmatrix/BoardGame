#include <string>

class Archer: public AUnit
{
    public:
        Archer() : AUnit('A', 40, 2, 250, 5, 3){}

        ~Archer() override {}
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
                case 'K':{return 15;}
                case 'S':{return 15;}
                case 'A':{return 15;}
                case 'P':{return 15;}
                case 'C':{return 10;}
                case 'R':{return 10;}
                case 'W':{return 15;}
                case 'B':{return 15;}
            }
        }
};
