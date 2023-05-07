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

int turn1 = 0;
int turn2 = 0;

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

void checkBuild()
{
    if (getPlayer(playerTurn).getBase().getIsOnBuild())
    {
        getPlayer(playerTurn).getBase().setTimeToBuild(getPlayer(playerTurn).getBase().getTimeToBuild() - 1);

        if (getPlayer(playerTurn).getBase().getTimeToBuild() <= 0)
        {
            switch(getPlayer(playerTurn).getBase().getUnitType())
            {
                case 'K':
                {
                    Knight* k = new Knight();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        k->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete k, unit;
                    break;
                }
                case 'S':
                {
                    Swordsman* s = new Swordsman();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        s->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete s, unit;
                    break;
                }                       
                case 'A':
                {
                    Archer* a = new Archer();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        a->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete a, unit;
                    break;
                }
                case 'P':
                {
                    Pikeman* p = new Pikeman();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        p->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete p, unit;
                    break;
                }
                case 'C':
                {
                    Catapult* c = new Catapult();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        c->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete c, unit;
                    break;
                }
                case 'R':
                {
                    Ram* r = new Ram();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        r->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete r, unit;
                    break;
                }
                case 'W':
                {
                    Worker* w = new Worker();
                    UnitOnBoard* unit = new UnitOnBoard(
                        getPlayer(playerTurn).getBase().getUnitType(), 
                        unitIndex, 
                        getPlayer(playerTurn).getBase().getXCord(), 
                        getPlayer(playerTurn).getBase().getYCord(),
                        w->getHp());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete w, unit;
                    break;
                }
                default:
                    return;
            }
            unitIndex += 1;
        }
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
            words->clear();
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
                    if (!friendly->getwasAttacking())
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
            }
            words->clear();
            return;
        }
        if (words[1].compare("B") == 0)
        {
            if (getPlayer(playerTurn).getBase().getIndex() == stoi(words[0]) && getPlayer(playerTurn).getBase().getIsOnBuild() == false)
            {
                char* array = new char[words[2].length() + 1];
                strcpy(array, words[2].c_str());
                switch(array[0])
                {
                    case 'K':
                    {
                        Knight *k = new Knight();
                        if (getPlayer(playerTurn).getGold() >= k->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - k->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *k);
                        }
                        delete k;
                        break;
                    }
                    case 'S':
                    {
                        Swordsman *s = new Swordsman();
                        if (getPlayer(playerTurn).getGold() >= s->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - s->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *s);
                        }
                        delete s;
                        break;
                    }                       
                    case 'A':
                    {
                        Archer *a = new Archer();
                        if (getPlayer(playerTurn).getGold() >= a->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - a->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *a);
                        }
                        delete a;
                        break;
                    }
                    case 'P':
                    {
                        Pikeman *p = new Pikeman();
                        if (getPlayer(playerTurn).getGold() >= p->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - p->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *p);
                        }
                        delete p;
                        break;
                    }
                    case 'C':
                    {
                        Catapult *c = new Catapult();
                        if (getPlayer(playerTurn).getGold() >= c->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - c->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *c);
                        }
                        delete c;
                        break;
                    }
                    case 'R':
                    {
                        Ram *r = new Ram();
                        if (getPlayer(playerTurn).getGold() >= r->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - r->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *r);
                        }
                        delete r;
                        break;
                    }
                    case 'W':
                    {
                        Worker *w = new Worker();
                        if (getPlayer(playerTurn).getGold() >= w->getCost())
                        {
                            getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() - w->getCost());
                            getPlayer(playerTurn).getBase().addUnitToBuild((AUnit) *w);
                        }
                        delete w;
                        break;
                    }
                }
            }
        }
        words->clear();
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

void saveStatsToFile()
{
    auto oppositePlayer = [](int playerTurn) -> int {
        return (playerTurn == 1 ? 2: 1);
    };

    std::ofstream myFile(statusFileName);    

    Player playerStats = getPlayer(playerTurn);
    myFile << playerStats.getGold() << "\n";
    myFile << playerStats.getBase().getBaseLetter() << " " 
        << "B" << " " << playerStats.getBase().getXCord()
        << " " << playerStats.getBase().getYCord()
        << " " << playerStats.getBase().getHp()
        << " " << playerStats.getBase().getUnitType() << "\n";

    Player enemyStats = getPlayer(oppositePlayer(playerTurn));

    myFile << enemyStats.getBase().getBaseLetter() << " " 
        << "B" << " " << enemyStats.getBase().getXCord()
        << " " << enemyStats.getBase().getYCord()
        << " " << enemyStats.getBase().getHp()
        << " " << enemyStats.getBase().getUnitType() << "\n";

    for (std::list<UnitOnBoard>::iterator it= getPlayer(playerTurn).getUnitList().begin(); 
        it != getPlayer(playerTurn).getUnitList().end(); ++it)
    {
        myFile << playerStats.getBase().getBaseLetter() << " "
            << it->getUnitId() << " " << it->getXCord() << " "
            << it->getYCord() << " " << it->getHp() << "\n";
    }
    for (std::list<UnitOnBoard>::iterator it= getPlayer(oppositePlayer(playerTurn)).getUnitList().begin(); 
        it != getPlayer(oppositePlayer(playerTurn)).getUnitList().end(); ++it)
    {
        myFile << enemyStats.getBase().getBaseLetter() << " "
            << it->getUnitId() << " " << it->getXCord() << " "
            << it->getYCord() << " " << it->getHp();
    }
    // Close the file
    myFile.close();
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

void GameMenu()
{

    while(turn1 < 1000 || turn2 < 1000)
    {
        system("clear");
        for(int i=0; i<5; i++)
        {
            std::cout << boardMap[i] << std::endl;
        }

        char orderCommand[100];

        saveStatsToFile();

        std::cout << "Player: " << playerTurn << std::endl;
        std::cout << "Write your command on file " << orderFileName << " and press any key on terminal to continue" << std::endl;
        //std::cin.getline(orderCommand, 100); // use getline() function to read a string from input stream  
        system("read");
        ReadOrderToCommand();

        if (playerTurn == 1) turn1 += 1;
        else turn2 += 1;

        changePlayer();
    }
}
