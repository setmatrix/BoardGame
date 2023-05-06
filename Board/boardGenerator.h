#pragma once
#include <cstdlib>
#include <string>
#include <fstream>

void BoardGenerator(std::string nameFile = "plansza.txt")
{
    srand(time(NULL));

    const int X = rand() % 35 + 16;
    const int Y = rand() % 15 + 6;

    //9 - Obstacle
    //0 - Road
    //6 - Cave
    char marks[] = { '0', '9', '6' };
    float chanceAfterRoad[] = { 70, 90, 100};
    float chanceAfterObstacle[] = { 40, 90, 100 };
    float chanceAfterCave[] = { 70, 80, 100 };

    char** board = new char* [X];
    for (int i = 0; i < X; i++)
    {
        board[i] = new char[Y];
    }

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            board[i][j] = '0';
        }
    }

    for (int i = 1; i < X; ++i)
    {
        for (int j = 1; j < Y; ++j)
        {
            if (board[i][j - 1] == '9')
            {
                float s = rand() % 100;
                for (int k = 0; k < sizeof(marks); ++k)
                {
                    if (s < chanceAfterObstacle[k])
                    {
                        board[i][j] = marks[k];
                        break;
                    }
                }
            }
            else if (board[i - 1][j] == '6' || board[i][j - 1] == '6')
            {
                float s = rand() % 100;
                for (int k = 0; k < sizeof(marks); ++k)
                {
                    if (s < chanceAfterCave[k])
                    {
                        board[i][j] = marks[k];
                        break;
                    }
                }
            }
            else
            {
                float s = rand() % 100;
                for (int k = 0; k < sizeof(marks); ++k)
                {
                    if (s < chanceAfterRoad[k])
                    {
                        board[i][j] = marks[k];
                        break;
                    }
                }
            }
        }
    }
    board[0][0] = '1';
    board[X-1][Y-1] = '2';

    // Create and open a text file
    std::ofstream myFile("plansza.txt");

    // Write to the file
    if (myFile.is_open())
    {
        for (int i = 0; i < X != '\0'; i++)
        {
            for (int j = 0; j < Y != '\0'; j++)
            {
                myFile << std::to_string(board[i][j] - 48) + " ";
            }
            myFile << std::endl;
        }
    }

    // Close the file
    myFile.close();

    delete board;
}