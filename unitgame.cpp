#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstring>
#include <sstream>

#include "Player/Player.h"

#include "FData/FUnitData/Catapult.h"
#include "FData/FUnitData/Archer.h"
#include "FData/FUnitData/Knight.h"
#include "FData/FUnitData/Pikeman.h"
#include "FData/FUnitData/Ram.h"
#include "FData/FUnitData/Swordsman.h"
#include "FData/FUnitData/Worker.h"

const char* mapFileName;
const char* statusFileName;
const char* orderFileName;

char** boardMap;
int* timeOut;

int unitIndex = 1;

//1 - Player1
//2 - Player2
short playerTurn = 1;

Player *player1;
Player *player2;

void ReadOrderToCommand();
Player getPlayer(short playerTurn);
void checkCommand(std::list<std::string> listwords);
void mapRead();
void GameMenu();
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);

void changePlayer()
{
    playerTurn++;
    if (playerTurn > 2)
    {
        playerTurn = 1;
    }
}

void ReadOrderToCommand()
{
 std::string line;

	std::list<std::string> listwords;

	std::ifstream stream;

	stream.open(orderFileName);

	if(stream.is_open())
	{
		while(std::getline(stream,line))
		{
			std::stringstream ss(line);

			while (std::getline (ss,line,' '))
			{
				listwords.push_back(line);
			}
            checkCommand(listwords);
		}
        listwords.clear();
    }
}

Player getPlayer(short playerTurn)
{
    switch(playerTurn)
    {
        case 1:{return *player1; break;}
        case 2:{return *player2; break;}
    }
    return Player();
}

void checkCommand(std::list<std::string> listwords)
{
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
    if(words[1].length() == 1)
    {
        if (words[1].compare("M") == 0)
        {
            for (std::list<UnitOnBoard>::iterator it= getPlayer(playerTurn).getUnitList().begin(); 
                it != getPlayer(playerTurn).getUnitList().end(); ++it)
            {
                if (it->getUnitId() == stoi(words[0]))
                {
                    it->setXCord(stoi(words[2]));
                    it->setYCord(stoi(words[3]));
                    break;
                }
            }
            delete words;
            return;
        }
        if (words[1].compare("A") == 0)
        {
            
            auto oppositePlayer = [](int playerTurn) -> int {
                return (playerTurn == 1 ? 2: 1);
            };
            
            for (std::list<UnitOnBoard>::iterator friendly= getPlayer(playerTurn).getUnitList().begin(); 
                friendly != getPlayer(playerTurn).getUnitList().end(); ++friendly)
            {
                if (friendly->getUnitId() == stoi(words[0]))
                {
                    for (std::list<UnitOnBoard>::iterator enemy= getPlayer(playerTurn).getUnitList().begin(); 
                    enemy != getPlayer(playerTurn).getUnitList().end(); ++enemy)
                    {
                        if (enemy->getUnitId() == stoi(words[2]))
                        {
                            enemy->setHp(enemy->getHp() - 30);
                            break;
                        }
                        break;
                    }
                }
            }
            delete words;
            return;
        }
        if (words[1].compare("B") == 0)
        {
            if (getPlayer(playerTurn).getBase().getIsOnBuild() == false)
            {
                char* array = new char[words[2].length() + 1];
                strcpy(array, words[2].c_str());
                switch(array[0])
                {
                    case 'K':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Knight());
                        unitIndex += 1;
                        break;
                    }
                    case 'S':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Swordsman());
                        unitIndex += 1;
                        break;
                    }                       
                    case 'A':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Archer());
                        unitIndex += 1;
                        break;
                    }
                    case 'P':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Pikeman());
                        unitIndex += 1;
                        break;
                    }
                    case 'C':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Catapult());
                        unitIndex += 1;
                        break;
                    }
                    case 'R':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Ram());
                        unitIndex += 1;
                        break;
                    }
                    case 'W':
                    {
                        getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) Worker());
                        unitIndex += 1;
                        break;
                    }
                }
            }
        }
        delete words;
        return;
    }
    std::cout << "Unknown command" << std::endl;
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
    system("clear");

    while(player1->getTurnCount() < 1000 && player2->getTurnCount() < 1000)
    {

        for(int i=0; i<5; i++)
        {
            std::cout << boardMap[i] << std::endl;
        }

        char orderCommand[100];

        std::cout << "Write your command on file " << orderFileName << " and press any key on terminal to continue" << std::endl;
        //std::cin.getline(orderCommand, 100); // use getline() function to read a string from input stream  
        system("read");
        ReadOrderToCommand();

        getPlayer(playerTurn).setTurnCount();

        changePlayer();
    }
}

void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{
    mapFileName = mapName;
    statusFileName = orderName;
    orderFileName = orderName;
    timeOut = &time;

    player1 = new Player(unitIndex, 'P', 0, 0);
    unitIndex+=1;
    player2 = new Player(unitIndex, 'E', 4, 32);

    mapRead();

    GameMenu();
}