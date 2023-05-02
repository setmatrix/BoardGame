class UnitOnBoardEnum
{
    private:
        enum UnitEnum
        {
            Knight = 'K',
            Swordsman = 'S',
            Archer = 'A',
            Pikeman = 'P',
            Catapult = 'C',
            Ram = 'R',
            Worker = 'W',
            Base = 'B'
        };
    public:
        char UnitType(const UnitEnum _unitName)
        {
            switch(_unitName)
            {
                case Knight: return Knight;
                case Swordsman: return Swordsman;
                case Archer: return Archer;
                case Pikeman: return Pikeman;
                case Catapult: return Catapult;
                case Ram: return Ram;
                case Worker: return Worker;
                case Base: return Base;
                default: return '0';
            }
        }
};