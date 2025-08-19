#pragma once
#include <functional>
#include "Cell.h"

typedef std::function<std::pair<int, int>()> CoordGenerator;

void playTurns(int height, int width, int totalMines, CoordGenerator const& generateCoord);
void playerTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft);
void cpuTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix,int width, int height, int& playerMinesLeft, int& cpuMinesLeft, CoordGenerator const& generateCoord);
void printBoard(std::vector<std::vector<Cell>> const& board);
void placePlayerMines(std::vector<std::vector<Cell>>& board, int mineCount);
void setCellStatus(std::vector<std::vector<Cell>>& board, unsigned int x, unsigned int y, Owner owner);
bool shoot(int const& x, int const& y, int const& width, int const& height, int& cpuMinesLeft, int& playerMinesLeft, std::vector<std::vector<Cell>>& board);