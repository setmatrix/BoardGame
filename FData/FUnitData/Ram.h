class Ram: public AUnit
{
    public:
        Ram() : AUnit('R', 90, 2, 500, 1, 4){}
        
        ~Ram() override {}
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
                case 'K':{return 10;}
                case 'S':{return 10;}
                case 'A':{return 10;}
                case 'P':{return 10;}
                case 'C':{return 10;}
                case 'R':{return 10;}
                case 'W':{return 10;}
                case 'B':{return 50;}
            }
        }
};
