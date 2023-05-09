#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstring>
#include <sstream>

#include "Player/Player.h"
#include "FUnitOnBoard/AttackOnBoard.h"

#include "FGameActions/AttackAction.cpp"
#include "FGameActions/MoveAction.cpp"
#include "FGameActions/BuildAction.cpp"

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
enum playerNames{player1, player2};

Player** players;

//PlayerTurns
//Player 1
int turn1 = 0;
//Player 2
int turn2 = 0;

//Predefined functions
void changePlayer();
void ResetAttacksStateFromPlayer();
void GetGoldFromWorkers();
void checkBuild();
void ReadOrderToCommand();
Player getPlayer(short playerTurn);
void checkCommand(std::list<std::string> listwords);
void mapRead();
void saveStatsToFile();
void GameMenu();
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);

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
                        k->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        s->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        a->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        p->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        c->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        r->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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
                        w->getAttackRange(),
                        getPlayer(playerTurn).getBase().getBaseLetter());
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

//Each turn gets money from workers and add to player's wallet.
void GetGoldFromWorkers()
{
    std::list<UnitOnBoard> units = getPlayer(playerTurn).getUnitList();
    if (units.size() > 0)
    {
        int goldFromWorkers = 0;
        for (std::list<UnitOnBoard>::iterator it= getPlayer(playerTurn).getUnitList().begin(); 
            it != getPlayer(playerTurn).getUnitList().end(); ++it)
        {
            std::string a(boardMap[it->getXCord(), it->getYCord()]);

            if (a.compare("6"))
            {
                goldFromWorkers += 50;
            }
        }

        getPlayer(playerTurn).setGold(getPlayer(playerTurn).getGold() + goldFromWorkers);
    }
}

//Resets all action flag
void ResetAttacksStateFromPlayer()
{
    if (getPlayer(playerTurn).getUnitList().size() > 0)
    {
        for(std::list<UnitOnBoard>::iterator it = getPlayer(playerTurn).getUnitList().begin(); 
            it != getPlayer(playerTurn).getUnitList().end(); it++)
        {
            it->resetAction();
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
            listwords.clear();
		}
    }
}

//Get actual player
Player getPlayer(short playerTurn)
{
    switch(playerTurn)
    {
        case 1:{return *players[player1]; break;}
        case 2:{return *players[player2]; break;}
    }
    return Player();
}

//Commands from orderFile on name defined by users
//Respectively do action saved in file ('M' - move, 'A' - attack, 'B' - build)
void checkCommand(std::list<std::string> listwords)
{
    auto enemyPlayer = [](int playerTurn) -> int {
        return (playerTurn == 1 ? 2: 1);
    };
    //First, check if is more or less than 3 or 4 elements
    if(listwords.size() < 3 && listwords.size() > 4)
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
            MoveAction(getPlayer(playerTurn), getPlayer(enemyPlayer(playerTurn)), words, boardMap);
        }

        //If attack was detected:
        if (words[1].compare("A") == 0)
        {   
            AttackAction(getPlayer(playerTurn), getPlayer(enemyPlayer(playerTurn)), words);
        }

        //If build was detected
        if (words[1].compare("B") == 0)
        {
            BuildAction(getPlayer(playerTurn), words);
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
        << "B" << " " << playerStats.getBase().getIndex() 
        << " " << playerStats.getBase().getXCord()
        << " " << playerStats.getBase().getYCord()
        << " " << playerStats.getBase().getHp()
        << " " << playerStats.getBase().getUnitType() << "\n";

    Player enemyStats = getPlayer(oppositePlayer(playerTurn));

    //Saves data from enemy player base
    myFile << enemyStats.getBase().getBaseLetter() << " " 
        << "B" << " " << enemyStats.getBase().getIndex() 
        << " " << enemyStats.getBase().getXCord()
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

    players = new Player*[2];

    players[player1] = new Player(unitIndex, 'P', 0, 0);
    unitIndex += 1;
    players[player2] = new Player(unitIndex, 'E', 4, 32);

    unitIndex += 1;
    mapRead();

    GameMenu();
}

//Main function to terminal
void GameMenu()
{

    while((turn1 < 1000 || turn2 < 1000) || (players[player1]->getBase().getHp() > 0 && players[player2]->getBase().getHp() > 0)) 
    {
        system("clear");
        for(int i=0; i<5; i++)
        {
            std::cout << boardMap[i] << std::endl;
        }

        char orderCommand[100];

        GetGoldFromWorkers();

        saveStatsToFile();

        std::cout << "Player: " << playerTurn << std::endl;
        std::cout << "Write your command on file " << orderFileName << " and press any key on terminal to continue" << std::endl;
        //std::cin.getline(orderCommand, 100); // use getline() function to read a string from input stream  

        //Important - crashes a game in Ubuntu/Debian
        system("read");

        ReadOrderToCommand();

        checkBuild();
        ResetAttacksStateFromPlayer();

        if (playerTurn == 1) turn1 += 1;
        else turn2 += 1;

        changePlayer();
    }

    if(players[player1]->getBase().getHp() <= 0 || players[player2]->getBase().getHp() <= 0)
    {
        if (players[player1]->getBase().getHp() <= 0)
        {
            std::cout << "Player2 wins. Congratulations!\n";
        }
        if (players[player2]->getBase().getHp() <= 0)
        {
            std::cout << "Player1 wins. Congratulations!\n";
        }
    }
    if(turn1 >= 1000 || turn2 >= 1000)
    {
        int player1Units = players[player1]->getUnitList().size();
        int player2Units = players[player2]->getUnitList().size();

        if (player1Units > player2Units)
        {
            std::cout << "Player 1 has more units and wins. Congratulations!\n";
        } 
        else if (player1Units < player2Units)
        {
            std::cout << "Player 2 has more units and wins. Congratulations!\n";
        } else {
            std::cout << "Draw!\n";
        }
    }

    std::string str; 
    std::cout<<"Write a nameFile to print a result:\n";

    getline(std::cin, str);
    if (str.length() > 1)
    {
        std::ofstream myFile(statusFileName);

        myFile << "Player1:" << std::endl;

        myFile << "Data about base:\n";
        myFile << players[player1]->getBase().getIndex() << std::endl;
        myFile << players[player1]->getBase().getHp() << std::endl;

        myFile << "\n\nData about units:\n";
        for (std::list<UnitOnBoard>::iterator it= players[player1]->getUnitList().begin(); 
            it != players[player1]->getUnitList().end(); ++it)
        {
            myFile << it->getUnitId() << " " << it->getUnitType() << " " << it->getHp() << " " << it->getXCord() << " " << it->getYCord() << std::endl;
        }
        myFile << std::endl;

        myFile << "Player2:" << std::endl;

        myFile << "Data about base:\n";
        myFile << players[player2]->getBase().getIndex() << std::endl;
        myFile << players[player2]->getBase().getHp() << std::endl;

        myFile << "\n\nData about units:\n";
        for (std::list<UnitOnBoard>::iterator it= players[player2]->getUnitList().begin(); 
            it != players[player2]->getUnitList().end(); ++it)
        {
            myFile << it->getUnitId() << " " << it->getUnitType() << " " << it->getHp() << " " << it->getXCord() << " " << it->getYCord() << std::endl;
        }
        myFile << std::endl;

        myFile.close();

        //Remove all pointers and elements
        delete mapFileName, statusFileName, orderFileName;

        for(int i=0; i<5; i++)
        {
            delete boardMap[i];
        }
        delete boardMap;

        delete timeOut;
        delete players[player1];
        delete players[player2];
        return;
    }
}