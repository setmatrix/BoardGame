class ABase
{
    protected:
        int hp;
        int speed;

    public:
        ABase(int _hp, int _speed)
        {
            this->hp = _hp;
            this->speed = _speed;
        }
        virtual int getHp() = 0;
        virtual int getSpeed() = 0;
};