#include <string>
#include <memory>

//Includes all headers from units

void createUnit(Player* actualPlayer, std::shared_ptr<AUnit> unit)
{
    if (actualPlayer->getGold() >= unit->getCost())
    {
        actualPlayer->setGold(actualPlayer->getGold() - unit->getCost());
        actualPlayer->getBaseData()->addUnitToCreate(*unit);
    }
}

bool BuildAction(Player* actualPlayer, std::vector<std::string> words)
{
    //First, check if id is equal to player and base isn't in building state
    if (actualPlayer->getBaseData()->getIndex() == stoi(words[0]) && !actualPlayer->getBaseData()->isBuilding())
    {
        char* array = new char[words[2].length() + 1];

        strcpy(array, words[2].c_str());

        //Create a appropriately unit from char
        //Susbstracting gold from player by cost of unit.
        switch(array[0])
        {
            case 'K':
            {
                std::shared_ptr <Knight> k(new Knight());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(k));
                delete array;
                return true;
            }
            case 'S':
            {
                std::shared_ptr <Swordsman> s(new Swordsman());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(s));
                delete array;
                return true;
            }                       
            case 'A':
            {
                std::shared_ptr <Archer> a(new Archer());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(a));
                delete array;
                return true;
            }
            case 'P':
            {
                std::shared_ptr <Pikeman> p(new Pikeman());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(p));
                delete array;
                return true;
            }
            case 'C':
            {
                std::shared_ptr <Catapult> c(new Catapult());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(c));
                delete array;
                return true;
            }
            case 'R':
            {
                std::shared_ptr <Ram> r(new Ram());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(r));
                delete array;
                return true;
            }
            case 'W':
            {
                std::shared_ptr <Worker> w(new Worker());
                createUnit(actualPlayer, std::static_pointer_cast<AUnit>(w));
                delete array;
                return true;
            }
            default:
            {
                std::cout << "Unit doesn't exist" << std::endl;
                delete array;
                return false;
            }
        }
        delete array;
        return false;
    }
    return false;
}