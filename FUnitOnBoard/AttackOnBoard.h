//Class with method, which coresponds to table of takingDamage
class AttackOnBoard
{
    public:
        static int AttackOnEnemy(char yUnit, char eUnit)
        {
            switch(yUnit)
            {
                case 'K':
                {
                    switch(eUnit)
                    {
                        case 'R':{return 50;}
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'W':
                        case 'B':{return 35;}
                        default: {return 0;}
                    }
                }
                case 'S':
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'R':
                        case 'W':
                        case 'B':{return 30;}
                        case 'P':
                        case 'C':{return 20;}
                        default: {return 0;}
                    }
                }
                case 'A':
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'W':
                        case 'B':{return 35;}
                        case 'R':{return 50;}
                        default: {return 0;}
                    }
                }
                case 'P':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 35;}
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'W':{return 15;}
                        case 'R':
                        case 'B':{return 10;}
                        default: {return 0;}
                    }
                }
                case 'C':
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'R':
                        case 'W':{return 40;}
                        case 'B':{return 50;}
                        default: {return 0;}
                    }
                }
                case 'R':
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'R':
                        case 'W':{return 10;}
                        case 'B':{return 50;}
                        default: {return 0;}
                    }
                }
                case 'W':
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'R':
                        case 'W':{return 5;}
                        case 'B':{return 1;}
                        default: {return 0;}
                    }
                }
                default:
                {
                    switch(eUnit)
                    {
                        case 'K':
                        case 'S':
                        case 'A':
                        case 'P':
                        case 'C':
                        case 'R':
                        case 'W':
                        case 'B':
                        default: {return 0;}
                    }
                }
            }
        }
};