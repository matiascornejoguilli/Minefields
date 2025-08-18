#include <iostream>
#include "Utils.h"
#include "Game.h"
#include "Player.h"

int main() 
{
    int height = 0;
    int width = 0;
    inputBoardSize(height, width);

    Player player;
    int totalMines = inputMines(player);

    CoordGenerator generateCoord = std::bind(generateRandomCoord, width, height);

    playTurns(height, width, totalMines, generateCoord);

    return 0;
}