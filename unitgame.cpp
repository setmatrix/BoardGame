#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstring>

#include "FData/FBaseData/Base.h"

const char* mapFileName;
const char* statusFileName;
const char* orderFileName;

char** boardMap;
int* timeOut;

int unitIndex = 3;

Base baseArray[2] = {{1, 'P', 0, 0}, {2, 'E', 4, 32}};

void checkCommand(char orderCommand[])
{
    //Split orderCommand using list of strings and method strtok
    std::list<std::string> listwords;
    char *ptr;  
    ptr = strtok(orderCommand, " ");   
    while (ptr != NULL)  
    { 
        listwords.push_back(ptr);
        ptr = strtok(NULL, " ");  
    }

    delete ptr;

    //Check if is more or less than 3 or 4 elements
    if(listwords.size() < 3 || listwords.size() > 4)
    {
        std::cout << "Unknown command" << std::endl;
        return;
    } 

    //Create a array of string coresponds to index;
    std::string *words;
    words = new std::string[listwords.size()];
    int local_index = 0;
    for (auto i = listwords.begin(); i != listwords.end(); i++)
    {
        words[local_index] = *i;
        local_index += 1;
    }
    listwords.clear();
    char move;
    if(words[1].length() != 1 || (words[1][1] != 'M'|| words[1][1] != 'A'
     || words[1][1] != 'B'))
    {
        std::cout << "Unknown command" << std::endl;
        return;
    }
    move = words[1][1];
    if (move == 'M')
    {
        std::cout << "M" << std::endl;
        return;
    }
    if (move == 'A')
    {
        std::cout << "A" << std::endl;
        return;
    }
    if (move == 'B')
    {
        std::cout << "B" << std::endl;
        return;
    }
}

void mapRead()
{

    if(boardMap == NULL)
    {
        boardMap = new char*[5];
        for(int i=0; i<5; i++)
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
        std::cout << boardMap[i] << std::endl;
    }

    char orderCommand[100];

    std::cout << "Write your command according to: \'id\' \'M|A|K\' and parameters \n";
    std::cin.getline(orderCommand, 100); // use getline() function to read a string from input stream  

    checkCommand(orderCommand);

    std::cout << "Done" << std::endl;
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