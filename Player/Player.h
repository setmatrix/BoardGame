#include "../FData/FBaseData/Base.h"
#include "../FUnitOnBoard/UnitOnBoard.h"
#include <list>
#include <memory>

class Player
{
    private:
        int gold;
        std::list<UnitOnBoard> units;
        std::shared_ptr<Base> base;
        int goldFromWorker = 50;

    public:
        Player()
        {
            Player::gold = 2000; 
        }
        Player(int _index, char _baseLetter, int _xCord, 
        int _yCord, bool _isOnBuild = false, char _unitType = 'B', int timeToBuild = -1) : Player()
        {
            base.reset(new Base(_index, _baseLetter, _xCord, _yCord));
        }

        Player(const Player& temp_obj) = delete;
        Player& operator=(const Player& temp_obj) = delete;

        int& getGold() {return Player::gold;}
        void setGold(int _gold) {Player::gold = _gold;}
        ~Player(){
            units.clear();
        }

        std::list<UnitOnBoard> &getUnitList()
        {
            return Player::units;
        }
        void addUnit(UnitOnBoard _unit)
        {
            Player::units.push_back(_unit);
        }
        std::shared_ptr<Base> &getBaseData()
        {
            return Player::base;
        }

        //Custom method to delete unit, when hp <= 0
        void deleteUnit(UnitOnBoard _unit)
        {
            std::list<UnitOnBoard>::iterator it = units.begin();

            while(it != units.end())
            {
                if(it->getUnitId() == _unit.getUnitId())
                {
                    it = units.erase(it);
                    break;
                }
            }
        }

        void AddMoneyFromWorker()
        {
            Player::gold += Player::goldFromWorker;
        }
};