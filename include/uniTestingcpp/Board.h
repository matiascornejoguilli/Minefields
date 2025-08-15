#pragma once
#include <vector>
#include "Cell.h"

struct Board 
{
    std::vector<std::vector<Cell>> grid;

    Board(size_t width, size_t height);
};