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
                        case 'K':{return 35;}
                        case 'S':{return 35;}
                        case 'A':{return 35;}
                        case 'P':{return 35;}
                        case 'C':{return 35;}
                        case 'R':{return 50;}
                        case 'W':{return 35;}
                        case 'B':{return 35;}
                        default: {return 0;}
                    }
                }
                case 'S':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 30;}
                        case 'S':{return 30;}
                        case 'A':{return 30;}
                        case 'P':{return 20;}
                        case 'C':{return 20;}
                        case 'R':{return 30;}
                        case 'W':{return 30;}
                        case 'B':{return 30;}
                        default: {return 0;}
                    }
                }
                case 'A':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 35;}
                        case 'S':{return 35;}
                        case 'A':{return 35;}
                        case 'P':{return 35;}
                        case 'C':{return 35;}
                        case 'R':{return 50;}
                        case 'W':{return 35;}
                        case 'B':{return 35;}
                        default: {return 0;}
                    }
                }
                case 'P':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 35;}
                        case 'S':{return 15;}
                        case 'A':{return 15;}
                        case 'P':{return 15;}
                        case 'C':{return 15;}
                        case 'R':{return 10;}
                        case 'W':{return 15;}
                        case 'B':{return 10;}
                        default: {return 0;}
                    }
                }
                case 'C':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 40;}
                        case 'S':{return 40;}
                        case 'A':{return 40;}
                        case 'P':{return 40;}
                        case 'C':{return 40;}
                        case 'R':{return 40;}
                        case 'W':{return 40;}
                        case 'B':{return 50;}
                        default: {return 0;}
                    }
                }
                case 'R':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 10;}
                        case 'S':{return 10;}
                        case 'A':{return 10;}
                        case 'P':{return 10;}
                        case 'C':{return 10;}
                        case 'R':{return 10;}
                        case 'W':{return 10;}
                        case 'B':{return 50;}
                        default: {return 0;}
                    }
                }
                case 'W':
                {
                    switch(eUnit)
                    {
                        case 'K':{return 5;}
                        case 'S':{return 5;}
                        case 'A':{return 5;}
                        case 'P':{return 5;}
                        case 'C':{return 5;}
                        case 'R':{return 5;}
                        case 'W':{return 5;}
                        case 'B':{return 1;}
                        default: {return 0;}
                    }
                }
                default:
                {
                    switch(eUnit)
                    {
                        case 'K':{return 0;}
                        case 'S':{return 0;}
                        case 'A':{return 0;}
                        case 'P':{return 0;}
                        case 'C':{return 0;}
                        case 'R':{return 0;}
                        case 'W':{return 0;}
                        case 'B':{return 0;}
                        default: {return 0;}
                    }
                }
            }
        }
};