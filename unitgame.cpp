#include <iostream>
#include <string>
#include <fstream>

const char* mapFileName;
const char* statusFileName;
const char* orderFileName;

char** boardMap;
int* timeOut;

void mapRead()
{

    if(boardMap == NULL)
    {
        boardMap = new char*[4];
        for(int i=0; i<4; i++)
        {
            boardMap[i] = new char[32];
        }
    }

    std::string strToRead;

    std::ifstream readFile(mapFileName);

    int row = 0;
    while(getline(readFile, strToRead))
    {
        if(strToRead != "\n")
        {
            for(int i=0; i<strToRead.length(); i++)
            {
                boardMap[row][i] = strToRead[i];
            }
        }
        row += 1;
    }
}

void GameMenu()
{
    for(int i=0; i<5; i++)
    {
        std::cout << boardMap[i];
    }

    std::cout << "Tutaj";
}

void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5)
{
    mapFileName = mapName;
    statusFileName = orderName;
    orderFileName = orderName;
    timeOut = &time;

    mapRead();

    GameMenu();
}