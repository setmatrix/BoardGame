#include <iostream>
#include <fstream>
#include "unitgame.cpp"

void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time = 5);
void prepare(int argc, char **argv);
void createOrderFile(const char* orderName);

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

void createOrderFile(const char* orderName)
{
    std::ofstream myFile(orderName);

    myFile.close();
}

void prepare(int argc, char **argv)
{
    switch(argc)
    {
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
            if (argc < 4)
            {
                std::cout << "Za mało parametrow: " << argc << std::endl;
            } else 
            {
                std::cout << "Za dużo parametrow: " << argc << std::endl;
            }
            break;
        }
    }
}

void gamePrepare(const char* mapName, const char* statusName, const char* orderName, int time)
{
    prepareMapToFile(mapName);
    createOrderFile(orderName);
    playPrepare(mapName, statusName, orderName, time);
}
