#include <string>

//Includes all headers from units
#include "../FData/FUnitData/Catapult.h"
#include "../FData/FUnitData/Archer.h"
#include "../FData/FUnitData/Knight.h"
#include "../FData/FUnitData/Pikeman.h"
#include "../FData/FUnitData/Ram.h"
#include "../FData/FUnitData/Swordsman.h"
#include "../FData/FUnitData/Worker.h"


void createUnit(Player actualPlayer, AUnit *unit)
{
    if (actualPlayer.getGold() >= unit->getCost())
    {
        actualPlayer.setGold(actualPlayer.getGold() - unit->getCost());
        actualPlayer.getBase().addUnitToBuild(*unit);
    }
}

void BuildAction(Player actualPlayer, std::string *words)
{
    //First, check if id is equal to player and base isn't in building state
    if (actualPlayer.getBase().getIndex() == stoi(words[0]) && !actualPlayer.getBase().getIsOnBuild())
    {
        char* array = new char[words[2].length() + 1];

        strcpy(array, words[2].c_str());

        //Create a appropriately unit from char
        //Susbstracting gold from player by cost of unit.
        switch(array[0])
        {
            case 'K':
            {
                Knight *k = new Knight();
                createUnit(actualPlayer, (AUnit*) k);
                delete k;
                return;
            }
            case 'S':
            {
                Swordsman *s = new Swordsman();
                createUnit(actualPlayer, (AUnit*) s);
                delete s;
                return;
            }                       
            case 'A':
            {
                Archer *a = new Archer();
                createUnit(actualPlayer, (AUnit*) a);
                delete a;
                return;
            }
            case 'P':
            {
                Pikeman *p = new Pikeman();
                createUnit(actualPlayer, (AUnit*) p);
                delete p;
                return;
            }
            case 'C':
            {
                Catapult *c = new Catapult();
                createUnit(actualPlayer, (AUnit*) c);
                delete c;
                return;
            }
            case 'R':
            {
                Ram *r = new Ram();
                createUnit(actualPlayer, (AUnit*) r);
                delete r;
                return;
            }
            case 'W':
            {
                Worker *w = new Worker();
                createUnit(actualPlayer, (AUnit*) w);
                delete w;
                return;
            }
            default:
            {
                std::cout << "Unit doesn't exist" << std::endl;
                return;
            }
        }
    }
}