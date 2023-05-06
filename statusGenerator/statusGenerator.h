#include <fstream>
#include <string>
#include <list>
#include <UnitOnBoard.h>

void GenerateStatus(std::string filename, int Gold, std::list<UnitOnBoard> map)
{
    std::ofstream myFile(filename);

    if (myFile.is_open())
    {
        myFile << Gold << std::endl;
        for(std::list<UnitOnBoard>::iterator it = map.begin(); it != map.end(); it++)
        {
            myFile << it->printUnit() << std::endl;
        }
    }
}