#include "../FData/FBaseData/Base.h"
#include "../FUnitOnBoard/UnitOnBoard.h"
#include <list>

class Player
{
    private:
        int gold;
        std::list<UnitOnBoard> units;
        Base *base;

    public:
        Player()
        {
            this->gold = 2000;
        }
        Player(int _index, char _baseLetter, int _xCord,
            int _yCord, bool _isOnBuild = false, char _unitType = 'B', int timeToBuild = -1) : Player()
        {
            this->base = new Base(_index, _baseLetter, _xCord, _yCord);
        }
        int getGold() { return this->gold; }
        void setGold(int _gold) { this->gold = _gold; }
        ~Player()
        {
            delete base;
            units.clear();
        }

        std::list<UnitOnBoard> getUnitList()
        {
            return this->units;
        }
        void addUnit(UnitOnBoard _unit)
        {
            this->units.push_back(_unit);
        }
        Base *getBaseData()
        {
            return this->base;
        }

        // Custom method to delete unit, when hp <= 0
        void deleteUnit(UnitOnBoard _unit)
        {
            std::list<UnitOnBoard>::iterator it = units.begin();

            while (it != units.end())
            {
                if (it->getUnitId() == _unit.getUnitId())
                {
                    it = units.erase(it);
                    break;
                }
            }
        }
};