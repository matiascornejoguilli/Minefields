#include <iostream>
#include <cstdlib>
#include "Utils.h"

void inputBoardSize(int& height, int& width) 
{
    static const unsigned int MaxSize = 15;
    static const unsigned int MinSize = 5;
    do 
    {
        std::cout << "Enter height (" << MinSize << '-' << MaxSize << "): ";
        std::cin >> height;
    } while (height < MinSize || height > MaxSize);

    do {
        std::cout << "Enter width (" << MinSize << '-' << MaxSize << "): ";
        std::cin >> width;
    } while (width < MinSize || width > MaxSize);
}

int inputMines(Player& player) 
{
    static const unsigned int MaxMines = 4;
    static const unsigned int MinMines = 2;
    do 
    {
        std::cout << "Enter the number of mines (" << MinMines << "-" << MaxMines << "): ";
        std::cin >> player.playerMines;
    } while (player.playerMines < MinMines || player.playerMines > MaxMines);
    return player.playerMines;
}

std::pair<int, int> generateRandomCoord(int width, int height) 
{
    return { rand() % width, rand() % height };
}