#pragma once
#include <uniTestingcpp/Board.h>
#include <uniTestingcpp/Cell.h>

#include <functional>
#include <utility>
#include <vector>

using CoordGenerator = std::function<std::pair<int, int>()>;

struct GameContext
{
    int width = 0;
    int height = 0;
    int playerMinesLeft = 0;
    int cpuMinesLeft = 0;

    Board board{0, 0};                     
    std::vector<std::vector<bool>> matrix; 
    CoordGenerator generateCoord;

    void resetMatrix()
    {
        matrix.assign(height, std::vector<bool>(width, false));
    }
};