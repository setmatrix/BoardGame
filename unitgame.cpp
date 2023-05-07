#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstring>
#include <sstream>

#include "Player/Player.h"
#include "FUnitOnBoard/AttackOnBoard.h"

#include "FData/FUnitData/Catapult.h"
#include "FData/FUnitData/Archer.h"
#include "FData/FUnitData/Knight.h"
#include "FData/FUnitData/Pikeman.h"
#include "FData/FUnitData/Ram.h"
#include "FData/FUnitData/Swordsman.h"
#include "FData/FUnitData/Worker.h"

//Map file name
const char* mapFileName;

//Status file name
const char* statusFileName;

//Order file name
const char* orderFileName;

//Twodimensional map, readed from map file
char** boardMap;

//Pointer to time
int* timeOut;

//Index for bases and units
int unitIndex = 1;

//1 - Player1
//2 - Player2
short playerTurn = 1;

//Player classes
Player *player1;
Player *player2;

//PlayerTurns
//Player 1
int turn1 = 0;
//Player 2
int turn2 = 0;

//Predefined functions
bool rangeCalculate(int range, int x1, int y1, int x2, int y2);
int changeActionPoints(UnitOnBoard unit, int x, int y);
bool IsEnemyUnitOnBoard(int x, int y);
void changePlayer();
void checkBuild();
void ReadOrderToCommand();
Player getPlayer(short playerTurn);
void checkCommand(std::list<std::string> listwords);
void mapRead();
void saveStatsToFile();
void GameMenu();
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);

//Returns true, if enemy is on range
bool rangeCalculate(int range, int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2) <= range ? true: false);
}

//Decreases action points
int changeActionPoints(UnitOnBoard unit, int x, int y) {
    int availablePoints = unit.getActionPoints();
    int usingActionPoints = abs(x - unit.getXCord()) + abs(y - unit.getYCord());

    return availablePoints - usingActionPoints;
}

//If enemy is on place x and y, returns true
bool IsEnemyUnitOnBoard(int x, int y)
{

    auto oppositePlayer = [](int playerTurn) -> int {
        return (playerTurn == 1 ? 2: 1);
    };
    std::list<UnitOnBoard> units = getPlayer(oppositePlayer(playerTurn)).getUnitList();

    for (std::list<UnitOnBoard>::iterator it= units.begin(); 
            it != units.end(); ++it)
        {
            if (it->getXCord() == x && it->getYCord() == y)
            {
                units.clear();
                return true;
            }
        }
    units.clear();
    return false;
}

//Function to change turn
void changePlayer()
{
    playerTurn++;
    if (playerTurn > 2)
    {
        playerTurn = 1;
    }
}

//If a base is building, decreases time,
//If a base time to build equals zero, create a class and adds to list of units from actual player and changes base data from building
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
                        k->getHp(),
                        k->getSpeed(),
                        k->getAttackRange());
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
                        s->getHp(),
                        s->getSpeed(),
                        s->getAttackRange());
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
                        a->getHp(),
                        a->getSpeed(),
                        a->getAttackRange());
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
                        p->getHp(),
                        p->getSpeed(),
                        p->getAttackRange());
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
                        c->getHp(),
                        c->getSpeed(),
                        c->getAttackRange());
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
                        r->getHp(),
                        r->getSpeed(),
                        r->getAttackRange());
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
                        w->getHp(),
                        w->getSpeed(),
                        w->getAttackRange());
                    getPlayer(playerTurn).addUnit(*unit);
                    delete w, unit;
                    break;
                }
                default:
                    return;
            }
            unitIndex += 1;

            //resets building state on base
            getPlayer(playerTurn).getBase().isNotBuilding();
        }
    }
}

//Reads command from file line by line

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
            //Each line are goint to function checkCommands, where do some actions, if writed properly.
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

//Commands from orderFile on name defined by users
//Respectively do action saved in file ('M' - move, 'A' - attack, 'B' - build)
void checkCommand(std::list<std::string> listwords)
{
    //First, check if is more or less than 3 or 4 elements
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
        //If move was detected:
        if (words[1].compare("M") == 0)
        {
            for (std::list<UnitOnBoard>::iterator it= getPlayer(playerTurn).getUnitList().begin(); 
                it != getPlayer(playerTurn).getUnitList().end(); ++it)
            {
                //Check if unit Id is equal to Id from file.
                if (it->getUnitId() == stoi(words[0]))
                {
                    //Then check, if Cordinates are on board
                    if (stoi(words[2]) > 0 && stoi(words[2]) < 32 && stoi(words[3]) > 0 && stoi(words[3]) < 5)
                    {
                        std::string s(boardMap[(stoi(words[2]), stoi(words[3]))]);
                        //Lastly, check if Coordinates from file are pointing to road, base, or cave and are on range to unit.
                        if ((s == "0" || s == "6") && !IsEnemyUnitOnBoard(stoi(words[2]), stoi(words[3])) 
                            && rangeCalculate(it->getActionPoints(), it->getXCord(), it->getYCord(), stoi(words[2]), stoi(words[3])))
                        {
                            //Decreases action points from move and set new Coorinates to unit.
                            it->setActionPoints(changeActionPoints(*it, stoi(words[2]), stoi(words[3])));
                            it->setXCord(stoi(words[2]));
                            it->setYCord(stoi(words[3]));
                        }
                        else {
                            std::cout << "Not enough Action Points or Enemy on this coordination exists or place is obstacle or cave\n";
                        }
                        break;
                    } else {
                        std::cout << "Your coordication are outside from board\n";
                    }
                }
            }
            words->clear();
            return;
        }
        //If attack was detected:
        if (words[1].compare("A") == 0)
        {
            
            auto oppositePlayer = [](int playerTurn) -> int {
                return (playerTurn == 1 ? 2: 1);
            };
            
            for (std::list<UnitOnBoard>::iterator friendly= getPlayer(playerTurn).getUnitList().begin(); 
                friendly != getPlayer(playerTurn).getUnitList().end(); ++friendly)
            {
                //First, get unit id and check, is equal to data from file
                if (friendly->getUnitId() == stoi(words[0]))
                {
                    //Then check, if unit was Attacking
                    if (!friendly->getwasAttacking())
                    {
                        for (std::list<UnitOnBoard>::iterator enemy= getPlayer(oppositePlayer(playerTurn)).getUnitList().begin(); 
                        enemy != getPlayer(oppositePlayer(playerTurn)).getUnitList().end(); ++enemy)
                        {
                            //Like on previous comentary, get enemy unit id and check, is equal to data from file
                            if (enemy->getUnitId() == stoi(words[2]))
                            {
                                //Check, if is on range
                                if(rangeCalculate(friendly->getRange(), friendly->getXCord(), friendly->getYCord(),
                                    enemy->getXCord(), enemy->getYCord()))
                                {
                                    //Get hp from unit and attackDamage from static method 
                                    int enemyHp = enemy->getHp();
                                    int attackDamage = AttackOnBoard::AttackOnEnemy(friendly->getUnitType(), enemy->getUnitType());

                                    //Then set hp, substracting from damage.
                                    enemy->setHp(enemyHp - attackDamage);
                                    friendly->setActionPoints(friendly->getActionPoints() - 1);

                                    //Set flag to true
                                    friendly->SetwasAttacking(true);

                                    //If unit has 0 or less hp
                                    if(enemy->getHp() <= 0)
                                    {   
                                        //Delete from list of units
                                        getPlayer(oppositePlayer(playerTurn)).deleteUnit(*enemy);
                                    }
                                }
                                else {
                                    std::cout << "Your enemy is out of range\n";
                                }
                                break;
                            }
                        }
                    } else {
                        std::cout << "Your unit already attacked\n";
                        break;
                    }
                    break;
                }
            }
            words->clear();
            return;
        }
        //If build was detected
        if (words[1].compare("B") == 0)
        {
            //First, check if id is equal to player and base isn't in building state
            if (getPlayer(playerTurn).getBase().getIndex() == stoi(words[0]) && !getPlayer(playerTurn).getBase().getIsOnBuild())
            {
                char* array = new char[words[2].length() + 1];

                strcpy(array, words[2].c_str());

                //Create a appropriately unit from char
                //Susbstracting gold from player by cost of unit.
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

//Read map from file to twodimensional array
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

//Saves status from two players, including units and bases
void saveStatsToFile()
{
    auto oppositePlayer = [](int playerTurn) -> int {
        return (playerTurn == 1 ? 2: 1);
    };

    std::ofstream myFile(statusFileName);    

    Player playerStats = getPlayer(playerTurn);

    //Saves gold from actual player
    myFile << playerStats.getGold() << "\n";

    //Saves data from actual player base
    myFile << playerStats.getBase().getBaseLetter() << " " 
        << "B" << " " << playerStats.getBase().getXCord()
        << " " << playerStats.getBase().getYCord()
        << " " << playerStats.getBase().getHp()
        << " " << playerStats.getBase().getUnitType() << "\n";

    Player enemyStats = getPlayer(oppositePlayer(playerTurn));

    //Saves data from enemy player base
    myFile << enemyStats.getBase().getBaseLetter() << " " 
        << "B" << " " << enemyStats.getBase().getXCord()
        << " " << enemyStats.getBase().getYCord()
        << " " << enemyStats.getBase().getHp()
        << " " << enemyStats.getBase().getUnitType() << "\n";

    if (getPlayer(playerTurn).getUnitList().size() > 0)
    {
        //Saves actual player data from list of units
        for (std::list<UnitOnBoard>::iterator it= getPlayer(playerTurn).getUnitList().begin(); 
            it != getPlayer(playerTurn).getUnitList().end(); ++it)
        {
            myFile << playerStats.getBase().getBaseLetter() << " "
                << it->getUnitId() << " " << it->getXCord() << " "
                << it->getYCord() << " " << it->getHp() << "\n";
        }
    }
        //Saves enemy player data from list of units
    if (getPlayer(oppositePlayer(playerTurn)).getUnitList().size() > 0)
    {
        for (std::list<UnitOnBoard>::iterator it= getPlayer(oppositePlayer(playerTurn)).getUnitList().begin(); 
            it != getPlayer(oppositePlayer(playerTurn)).getUnitList().end(); ++it)
        {
            myFile << enemyStats.getBase().getBaseLetter() << " "
                << it->getUnitId() << " " << it->getXCord() << " "
                << it->getYCord() << " " << it->getHp();
        }
    }
    // Close the file
    myFile.close();
}

//Prepares names and create player classes
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{
    mapFileName = mapName;
    statusFileName = statusName;
    orderFileName = orderName;
    timeOut = &time;

    player1 = new Player(unitIndex, 'P', 0, 0);
    unitIndex += 1;
    player2 = new Player(unitIndex, 'E', 4, 32);
    unitIndex += 1;
    mapRead();

    GameMenu();
}

//Main function to terminal
void GameMenu()
{

    while((turn1 < 1000 || turn2 < 1000) && (player1->getBase().getHp() > 0 || player2->getBase().getHp() > 0)) 
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
