class UnitOnBoard
{
    private:
        char unitAffiliation;
        char unitType;
        int unitId;
        int xCord;
        int yCord;
        int hp;
    public:
        UnitOnBoard(char _unitAffiliation, char _unitType, int _unitId, int _xCord, int _yCord, int _hp)
        {
            this->unitAffiliation = _unitAffiliation;
            this->unitType = _unitType;
            this->unitId = _unitId;
            this->xCord = _xCord;
            this->yCord = _yCord;
            this->hp = _hp;
        }
};