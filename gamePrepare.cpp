#include <iostream>
#include <fstream>
#include "unitgame.cpp"
#include <algorithm>

//Predefined functions
void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);
void prepare(int argc, char **argv);
void createOrderFile(const char* orderName);

//Creating board Map from File
bool prepareMapFromFile(const char* mapName)
{
    try
    {
        std::ifstream boardReading(mapName);
        std::string row;

        std::list<std::string>listOfFileData;

        bool firstLineRead = false;
        bool lastLineEmpty = false;
        int columnCount = 0;
        int rowCount = 0;

        //File exist, starting reading process
        if (boardReading)
        {
            bool isColumnLengthEqual = true;
            int index = -1;

            //Reading each line of file
            while (!boardReading.eof()) {
                index += 1;
                getline(boardReading, row);

                //Removing white spaces
                row.erase(std::remove_if(row.begin(), row.end(), ::isspace), row.end());

                //Skipping lines until detect line of data
                if(!firstLineRead && row.length() == 0) {continue;}

                //Line has data
                if (!firstLineRead && row.length() > 0)
                {
                    columnCount = row.length();
                    firstLineRead = true;
                    rowCount += 1;
                    listOfFileData.push_back(row);
                    continue;
                }

                //Program detects length which isn't equal to first Line length
                if (columnCount != row.length())
                {

                    //If line is empty, then check if file is ending.
                    if(row.length() == 0 && columnCount > 1)
                    {
                        lastLineEmpty = true;
                        continue;
                    }

                    //But if data exists after empty line, throws exception
                    if(row.length() > 0 && lastLineEmpty)
                    {
                        std::string errorMessage;
                        errorMessage = "Empty value on line: " + std::to_string(index) + " detected. Fix that problem and run the program again.\n";
                        throw errorMessage;
                    }

                    isColumnLengthEqual = false;
                }
                if (isColumnLengthEqual)
                {
                    rowCount += 1;
                    listOfFileData.push_back(row);
                }
            }
            if (!isColumnLengthEqual)
            {
                row.clear();
                listOfFileData.clear();
                throw std::string("Your columns aren't equal.\n");
            }
            else 
            {
                //After that
                //Check if Character is consistent with the assumption and
                //Save data from list into twodimensional array
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
                for (std::string &it : listOfFileData)
                {
                    std::string row = it;
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
                std::string errorMessage = "Character not allowed";
                throw errorMessage;
            }
        }
        else{
            std::string errorMessage;
            errorMessage = "Error: File " + std::string(mapName) + " doesn't exist.\n";
            throw errorMessage;
        }
    }
    catch(std::string errorMessage)
    {
            std::cout << errorMessage;
            return false;
    }
}

//Open and take data from file
void createOrderFile(const char* orderName)
{
    std::ofstream myFile(orderName);

    myFile.close();
}

//Function to run preparations with arguments or not, if not writed in terminal.
void prepare(int argc, char **argv)
{
    try
    {
        switch(argc)
        {
            case 1:
            case 2:
            case 3:
            {
                throw std::string("Not enough parameters: " + std::to_string(argc));
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
                    throw std::string("Too much parameters: " + std::to_string(argc));
                }
                break;
            }
        }
    }
    catch(std::string errorMessage)
    {
        std::cout << errorMessage << std::endl;
        return;
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
