#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
#include <sstream>
#include <thread>
#include <chrono>
#include <memory>

#include "Player/Player.h"
#include "FUnitOnBoard/AttackOnBoard.h"

#include "FData/FUnitData/Catapult.h"
#include "FData/FUnitData/Archer.h"
#include "FData/FUnitData/Knight.h"
#include "FData/FUnitData/Pikeman.h"
#include "FData/FUnitData/Ram.h"
#include "FData/FUnitData/Swordsman.h"
#include "FData/FUnitData/Worker.h"

#include "FGameActions/AttackAction.cpp"
#include "FGameActions/MoveAction.cpp"
#include "FGameActions/BuildAction.cpp"

//Map file name
const char* mapFileName;

//Status file name
const char* statusFileName;

//Order file name
const char* orderFileName;

//Twodimensional map, readed from board file
char** boardMap;

int boardX = 0;
int boardY = 0;

int player1X = 0;
int player1Y = 0;

int player2X = 0;
int player2Y = 0;

//Pointer to time
int timeOut;

//Index for bases and units
int unitIndex = 1;

//actual Player
short playerTurn = 0;

//Player classes
enum playerNames{player1, player2, playerEnd};

Player** players;

//PlayerTurns
std::shared_ptr<int[]> playerTurns;

//Predefined functions
void ResetAttacksStateFromPlayer();
void GetGoldFromWorkers();
void checkBuild();
bool checkCommand(std::vector<std::string> listwords);
void ReadOrderToCommand();
Player getPlayer(short playerTurn);
void mapRead();
void saveStatsToFile();
void GameMenu();
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);

//If a base is building, decreases time,
//If a base time to build equals zero, create a class and adds to list of units from actual player and changes base data from building
void checkBuild()
{
    if (!players[playerTurn]->getBaseData()->isBuilding())
    {
        return;
    }
    
    players[playerTurn]->getBaseData()->setTimeToCreateUnit(players[playerTurn]->getBaseData()->getTimeToCreate() - 1);

    if (players[playerTurn]->getBaseData()->getTimeToCreate() > 0)
    {
        return;
    }

    auto createUnit = [](AUnit unit)
    {
        std::unique_ptr<UnitOnBoard> u(new UnitOnBoard(
            players[playerTurn]->getBaseData()->getUnitType(), 
            unitIndex, 
            players[playerTurn]->getBaseData()->getXCord(), 
            players[playerTurn]->getBaseData()->getYCord(),
            unit.getHp(),
            unit.getSpeed(),
            unit.getAttackRange(),
            players[playerTurn]->getBaseData()->getOwner()));

        players[playerTurn]->addUnit(*u);
    };
    switch(players[playerTurn]->getBaseData()->getUnitType())
    {
        case 'K':
        {
            std::unique_ptr<Knight> k(new Knight());
            createUnit((AUnit) *k);
            break;
        }
        case 'S':
        {
            std::unique_ptr<Swordsman> s(new Swordsman());
            createUnit((AUnit) *s);
            break;
        }                       
        case 'A':
        {
            std::unique_ptr<Archer> a(new Archer());
            createUnit((AUnit) *a);
            break;
        }
        case 'P':
        {
            std::unique_ptr<Pikeman> p(new Pikeman());
            createUnit((AUnit) *p);
            break;
        }
        case 'C':
        {
            std::unique_ptr<Catapult> c(new Catapult());
            createUnit((AUnit) *c);
            break;
        }
        case 'R':
        {
            std::unique_ptr<Ram> r(new Ram());
            createUnit((AUnit) *r);
            break;
        }
        case 'W':
        {
            std::unique_ptr<Worker> w(new Worker());
            createUnit((AUnit) *w);
            break;
        }
        default:
            break;
        }
    unitIndex += 1;
    //resets building state on base
    players[playerTurn]->getBaseData()->isNotBuilding();
}

//Each turn gets money from workers and add to player's wallet.
void GetGoldFromWorkers()
{
    std::list<UnitOnBoard> units = players[playerTurn]->getUnitList();
    if (units.size() > 0)
    {
        for(UnitOnBoard it : players[playerTurn]->getUnitList())
        {
            char point = boardMap[it.getXCord()][it.getYCord()];
            std::string a(std::string() + point);

            if (a == "6")
            {
                players[playerTurn]->AddMoneyFromWorker();
            }
        }
    }
}

//Resets all action flag
void ResetAttacksStateFromPlayer()
{
    if (players[playerTurn]->getUnitList().size() > 0)
    {
        for(UnitOnBoard &it : players[playerTurn]->getUnitList())
        {
            UnitOnBoard u(it.getUnitType(), it.getUnitId(), it.getXCord(), it.getYCord(), it.getHp(), it.getSpeed(), it.getAttackRange(), it.getOwner());
            players[playerTurn]->deleteUnit(it);
            players[playerTurn]->addUnit(u);
        }
    }
}

//Reads command from file line by line
void ReadOrderToCommand()
{
    std::string line;

	std::vector<std::string> listwords;

	std::ifstream stream;

	stream.open(orderFileName);

    bool isCommandCorrect = true;

	if(stream.is_open())
	{
        try
        {    
            while(std::getline(stream,line) && isCommandCorrect)
            {
                //Each value are separated from white space and put to list.
                std::stringstream ss(line);

                while (std::getline (ss,line,' '))
                {
                    listwords.push_back(line);
                }
                //Each line are going to function checkCommands, where do some actions, if writed properly.
                isCommandCorrect = checkCommand(listwords);
                listwords.clear();
            }
        }
        catch(std::string error)
        {
            std::cout << error << std::endl;
        }
    }
}

//Commands from orderFile on name defined by users
//Respectively do action saved in file ('M' - move, 'A' - attack, 'B' - build)
bool checkCommand(std::vector<std::string> listwords)
{
    auto enemyPlayer = [](int playerTurn) -> int {
        return (playerTurn == 0 ? 1: 0);
    };
    //First, check if is more or less than 3 or 4 elements
    if(listwords.size() < 3 && listwords.size() > 4)
    {
        throw std::string("Unknown command");
    } 

    if(listwords[1].length() == 1)
    {
        bool isCommandCorrect = false;

        if(listwords[1].compare("M") == 0 || listwords[1].compare("A") == 0 || listwords[1].compare("B") == 0)
        {
            //If move was detected:
            if (listwords[1].compare("M") == 0)
            {
                isCommandCorrect = MoveAction(players[playerTurn], players[enemyPlayer(playerTurn)], listwords, boardMap, boardX, boardY);
            }

            //If attack was detected:
            if (listwords[1].compare("A") == 0)
            {   
                isCommandCorrect = AttackAction(players[playerTurn], players[enemyPlayer(playerTurn)], listwords);
            }

            //If build was detected:
            if (listwords[1].compare("B") == 0)
            {
                isCommandCorrect = BuildAction(players[playerTurn], listwords);
            }
            listwords.clear();
        }
        else 
        {
            throw std::string("Unknown Action");
        }
        return isCommandCorrect;
    }
    return false;
}

std::string getDataFromPlayers(Player* actualPlayer, Player* enemy)
{
    auto getDataFromBase = [](Player* player) -> std::string 
    {
        return std::string() + player->getBaseData()->getOwner() + " " 
        + player->getBaseData()->getBaseLetter()+ " " + std::to_string(player->getBaseData()->getIndex()) 
        + " " + std::to_string(player->getBaseData()->getXCord())
        + " " + std::to_string(player->getBaseData()->getYCord())
        + " " + std::to_string(player->getBaseData()->getHp())
        + " " + player->getBaseData()->getUnitType() +"\n";
    };

    auto getUnitsData = [](Player* player) -> std::string 
    {
        if (player->getUnitList().size() <= 0)
        {
            return "";
        }
        //Saves actual player data from list of unit
        std::string unitsData = "";
        for(UnitOnBoard &it : player->getUnitList())
        {
            unitsData += std::string() + player->getBaseData()->getOwner() + " " + it.getUnitType() + " "
                + std::to_string(it.getUnitId()) + " " + std::to_string(it.getXCord()) + " "
                + std::to_string(it.getYCord()) + " " + std::to_string(it.getHp()) + "\n";
        }
        return unitsData;
    };

    std::string returnData = "";

    //Saves gold from actual player
    returnData += std::to_string(actualPlayer->getGold()) + "\n";

    //Saves data from actual player base
    returnData += getDataFromBase(actualPlayer);

    //Saves data from enemy player base
    returnData += getDataFromBase(enemy);

    //Saves actual player data from list of units
    returnData += getUnitsData(actualPlayer);

    //Saves enemy player data from list of units
    returnData += getUnitsData(enemy);

    return returnData;
}
//Saves status from two players, including units and bases
void saveStatsToFile()
{
    auto oppositePlayer = [](int playerTurn) -> int {
        return (playerTurn == 0 ? 1: 0);
    };

    std::ofstream myFile(statusFileName);    
        
    myFile << getDataFromPlayers(players[playerTurn], players[oppositePlayer(playerTurn)]);


    // Close the file
    myFile.close();
}

//Prepares names and create player classes
void playPrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{

    mapFileName = mapName;
    statusFileName = statusName;
    orderFileName = orderName;
    timeOut = time;

    players = new Player*[2];

    players[player1] = new Player(unitIndex, 'P', player1X, player1Y);
    unitIndex += 1;
    players[player2] = new Player(unitIndex, 'E', player2X, player2Y);

    playerTurns.reset(new int[playerEnd - 1], std::default_delete<int[]>());

    for(int i=player1; i<playerEnd; i++)
    {
        playerTurns[i] = 0;
    }

    unitIndex += 1;

    for(int i=0; i<boardX; i++)
    {
        std::cout << boardMap[i] << std::endl;
    }

    GameMenu();
}

std::string printResults(Player* playerStats)
{
    std::string printResult = "";
    printResult += "Player1\n:";

    printResult += "Data about base:\n";
    printResult += playerStats->getBaseData()->getIndex() + "\n";
    printResult += playerStats->getBaseData()->getHp() + "\n";

    printResult += "\n\nData about units:\n";
    if (playerStats->getUnitList().size() < 0)
    {
        return printResult;
    }
    for(UnitOnBoard &it : playerStats->getUnitList())
    {
        printResult += std::to_string(it.getUnitId()) + " " + std::to_string(it.getUnitType()) + " " + 
            std::to_string(it.getHp()) + " " + std::to_string(it.getXCord()) + " " + std::to_string(it.getYCord()) + "\n";
    }
    return printResult;
}

//Main function to terminal
void GameMenu()
{
    auto turnsExceeded = []() -> bool
    {
        int exceededCount = 0;
        for(int i=0; i<playerEnd; i++)
        {
            if(playerTurns[i] >= 1000)
            {
                exceededCount += 1;
            }
        }
        if (exceededCount == playerEnd - 1)
        {
            return true;
        }
        return false;
    };

    while(!turnsExceeded() && (players[player1]->getBaseData()->getHp() > 0 && players[player2]->getBaseData()->getHp() > 0)) 
    {

        char orderCommand[100];

        GetGoldFromWorkers();

        saveStatsToFile();

        std::ofstream myFile(orderFileName);
        myFile.close(); 
        
        std::cout << "Round: " << playerTurns[player1] + playerTurns[player2] << std::endl;
        std::cout << "Player: " << playerTurn + 1 << std::endl;
        std::cout << "Write your commands on file " << orderFileName << ". You have " << timeOut << " seconds." << std::endl;

        std::chrono::seconds duration(timeOut);
        std::this_thread::sleep_for(duration);

        ReadOrderToCommand();

        checkBuild();
        ResetAttacksStateFromPlayer();

        for(int i=0; i<playerEnd; i++)
        {
            if(i == playerTurn)
            {
                playerTurns[i] += 1;
                playerTurn++;
                if (playerTurn >= playerEnd)
                {
                    playerTurn = 0;
                }
                break;
            }
        }
    }

    if(players[player1]->getBaseData()->getHp() <= 0 || players[player2]->getBaseData()->getHp() <= 0)
    {
        if (players[player1]->getBaseData()->getHp() <= 0)
        {
            std::cout << "Player2 wins. Congratulations!\n";
        }
        if (players[player2]->getBaseData()->getHp() <= 0)
        {
            std::cout << "Player1 wins. Congratulations!\n";
        }
    }
    if(turnsExceeded())
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
        for(int i=0; i<playerEnd; i++)
        {
            myFile << printResults(players[i]);
        }
        myFile.close();

    }
    //Remove all pointers and elements
    delete mapFileName, statusFileName, orderFileName;

    for(int i=0; i<boardX; i++)
    {
        delete[] boardMap[i];
    }
    delete[] boardMap;

    for(int i=0; i<playerEnd; i++)
    {
        delete[] players[i];
    }
    delete[] players;
    return;
}