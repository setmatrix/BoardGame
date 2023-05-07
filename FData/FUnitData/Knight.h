#include <string>

class Knight: public AUnit
{
    public:
        Knight() : AUnit('K', 70, 5, 400, 1, 5){}

        ~Knight() override {}
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
                case 'S':{return 35;}
                case 'A':{return 35;}
                case 'P':{return 35;}
                case 'C':{return 35;}
                case 'R':{return 50;}
                case 'W':{return 35;}
                case 'B':{return 35;}
            }
        }
};
