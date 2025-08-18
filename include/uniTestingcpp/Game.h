#pragma once
#include <functional>

typedef std::function<std::pair<int, int>()> CoordGenerator;

void playTurns(int height, int width, int totalMines, const CoordGenerator& generateCoord);
void printBoard(std::vector<std::vector<Cell>> const& board);
void placePlayerMines(std::vector<std::vector<Cell>>& board, int mineCount);
void setCellStatus(std::vector<std::vector<Cell>>& board, unsigned int x, unsigned int y, Owner owner);