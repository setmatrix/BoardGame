class AUnit
{
    private:
        int basehp;
        int speed;
        int cost;
        int attackRange;
        int buildTime;

    public:
        AUnit(int _basehp, int _speed, int _cost, int _attackRange, int _buildTime)
        {
            this->basehp = _basehp;
            this->speed = _speed;
            this->cost = _cost;
            this->attackRange = _attackRange;
            this->buildTime = _buildTime;
        }
};