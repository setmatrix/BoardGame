int AttackOnEnemy(char playerUnit, char enemyUnit)
{
    switch (playerUnit)
    {
        case 'K':
        {
            switch (enemyUnit)
            {
            case 'R':
            {
                return 50;
            }
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'W':
            case 'B':
            {
                return 35;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'S':
    {
        switch (enemyUnit)
            {
            case 'K':
            case 'S':
            case 'A':
            case 'R':
            case 'W':
            case 'B':
            {
                return 30;
            }
            case 'P':
            case 'C':
            {
                return 20;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'A':
    {
        switch (enemyUnit)
            {
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'W':
            case 'B':
            {
                return 35;
            }
            case 'R':
            {
                return 50;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'P':
    {
        switch (enemyUnit)
            {
            case 'K':
            {
                return 35;
            }
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'W':
            {
                return 15;
            }
            case 'R':
            case 'B':
            {
                return 10;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'C':
    {
        switch (enemyUnit)
            {
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'R':
            case 'W':
            {
                return 40;
            }
            case 'B':
            {
                return 50;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'R':
    {
        switch (enemyUnit)
        {
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'R':
            case 'W':
            {
                return 10;
            }
            case 'B':
            {
                return 50;
            }
            default:
            {
                return 0;
            }
        }
    }
    case 'W':
    {
        switch (enemyUnit)
        {
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'R':
            case 'W':
            {
                return 5;
            }
            case 'B':
            {
                return 1;
            }
            default:
            {
                return 0;
            }
        }
    }
    default:
    {
        switch (enemyUnit)
        {
            case 'K':
            case 'S':
            case 'A':
            case 'P':
            case 'C':
            case 'R':
            case 'W':
            case 'B':
            default:
            {
                return 0;
            }
        }
    }
    }
}