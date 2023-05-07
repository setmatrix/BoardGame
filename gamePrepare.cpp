#include <iostream>
#include <fstream>
#include "unitgame.cpp"

//Predefined functions
void gamePrepare(const char* mapName = "plansza.txt", const char* statusName = "status.txt", const char* orderName = "rozkazy.txt", int time = 5);
void prepare(int argc, char **argv);
void createOrderFile(const char* orderName);

//Function to create to file with map
void prepareMapToFile(const char* mapName)
{
// Create and open a text file
    std::ofstream myFile(mapName);

    int arr[][32] = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2}
    };

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<32; j++)
        {
            myFile << arr[i][j];
        }
        myFile << std::endl;
    }

    // Close the file
    myFile.close();
}

//Function to create an empty oder file
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
        {
            gamePrepare();
            break;
        }
        case 2:
        {
            const char* mapName = argv[1];
            gamePrepare(mapName);
            break;
        }
        case 3:
        {
            const char* mapName = argv[1];
            const char *statusName = argv[2];
            gamePrepare(mapName, statusName);
            break;
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
                std::cout << "Too much parameters " << argc << std::endl;
            }
            break;
        }
    }
}

//Creates status File. orderFile and run a game
void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{
    prepareMapToFile(mapName);
    createOrderFile(orderName);
    playPrepare(mapName, statusName, orderName, time);
}
