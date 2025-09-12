#include <iostream>
#include <cstdlib>
#include <Minefields/Utils.h>
#include <string>


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
    static unsigned int const MaxMines = 4;
    static unsigned int const MinMines = 2;
    std::string message = "Enter the number of mines (" + std::to_string(MinMines) + " to " + std::to_string(MaxMines) + "): ";
    do
    {
        player.playerMines = inputInt(message);
    } while (player.playerMines < MinMines || player.playerMines > MaxMines);
    return player.playerMines;
}


std::pair<int, int> generateRandomCoord(int width, int height) 
{
    return { rand() % width, rand() % height };
}


int inputInt(const std::string& message)
{
    int x = 0;
    std::cout << message;
    std::cin >> x;
    return x;
}