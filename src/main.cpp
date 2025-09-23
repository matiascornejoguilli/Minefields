#include <iostream>
#include <Minefields/Utils.h>
#include <Minefields/Game.h>
#include <Minefields/Player.h>
#include <Minefields/States.h>

int main() 
{
    int height = 0;
    int width = 0;
    //inputBoardSize(height, width);

    Player player;
    //int totalMines = inputMines(player);

    CoordGenerator generateCoord = std::bind(generateRandomCoord, width, height);

    Minefields::runMainLoop();
   // playTurns(height, width, totalMines, generateCoord);

    return 0;
}