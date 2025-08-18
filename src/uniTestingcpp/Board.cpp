#include "Board.h"

Board::Board(size_t width, size_t height) 
{
    grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}