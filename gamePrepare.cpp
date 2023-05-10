#include <iostream>
#include <fstream>
#include "unitgame.cpp"

//Predefined functions
void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);
void prepare(int argc, char **argv);
void createOrderFile(const char* orderName);

//Function to create to file with map
bool prepareMapFromFile(const char* mapName)
{
//Open and take data from file

    std::ifstream boardLoading(mapName);
    std::string row;

    std::list<std::string>rowsData;

    bool firstLineRead = false;
    int columnCount = 1;
    int rowCount = 1;

    if (boardLoading)
    {
        bool isColumnsEqual = true;
        while (!boardLoading.eof()) {
            getline(boardLoading, row);
            if (!firstLineRead)
            {
                columnCount = row.length();
                firstLineRead = true;
                rowCount += 1;
                rowsData.push_back(row);
                continue;
            }
            if (columnCount != row.length())
            {
                isColumnsEqual = false;
            }
            rowCount += 1;
            rowsData.push_back(row);
        }
        if (!isColumnsEqual)
        {
            std::cout << "Your columns aren't equal.\n";
            row.clear();
            rowsData.clear();
            return false;
        }
        else 
        {
            boardX = rowCount;
            boardY = columnCount;

            bool player1Base = false;
            bool player2Base = false;
            bool allowedChars = true;

            boardMap = new char*[boardX];
            for(int i=0; i<boardX; i++)
            {
                boardMap[i] = new char[boardY];
            }

            int rowX = 0;
            for (std::list<std::string>::iterator it = rowsData.begin(); 
                it != rowsData.end(); ++it)
            {
                std::string row = *it;
                for(int j=0; j<row.length(); j++)
                {
                    if ((int)row.at(j) == (int)'1') 
                    {
                        player1Base = true;
                        player1X = rowX;
                        player1Y = j;
                    }
                    if ((int)row.at(j) == (int)'2')
                    {
                        player2Base = true;
                        player2X = rowX;
                        player2Y = j;
                    }

                    if ((int)row.at(j) != (int)'0' && (int)row.at(j) != (int)'1' && 
                        (int)row.at(j) != (int)'2' && (int)row.at(j) != (int)'6' && (int)row.at(j) != (int)'9')
                    {
                        allowedChars = false;
                    } 
                    boardMap[rowX][j] = row.at(j);
                }
                rowX += 1;
            }
            if (player1Base && player2Base && allowedChars) return true;
            return false;
        }
    }
    return false;
}

void createOrderFile(const char* orderName)
{
    std::ofstream myFile(orderName);

    myFile.close();
}

//Function to run preparations with arguments or not, if not writed in terminal.
void prepare(int argc, char **argv)
{
    switch(argc)
    {
        case 1:
        case 2:
        case 3:
        {
            std::cout << "Not enough parameters: " << argc << std::endl;
            return;
        }
        case 4:
        {
            const char* mapName = argv[1];
            const char *statusName = argv[2];
            const char *orderName = argv[3];
            gamePrepare(mapName, statusName, orderName);
            break;
        }
        case 5:
        {
            const char *mapName = argv[1];
            const char *statusName = argv[2];
            char *orderName = argv[3];
            const int timeOut = atoi(argv[4]);
            gamePrepare(mapName, statusName, orderName, timeOut);
            break;
        }
        default:
        {
            if (argc > 5)
            {
                std::cout << "Too much parameters: " << argc << std::endl;
            }
            break;
        }
    }
}

//Creates status File. orderFile and run a game
void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{
    if (prepareMapFromFile(mapName))
    {
        createOrderFile(orderName);
        playPrepare(mapName, statusName, orderName, time);
    }
}
