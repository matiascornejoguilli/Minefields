#pragma once
#include <functional>
#include "Cell.h"
#include "Utils.h"
#include <iostream>

typedef std::function<std::pair<int, int>()> CoordGenerator;

void playTurns(int height, int width, int totalMines, CoordGenerator const& generateCoord, std::ostream& outputStream = std::cout);
void playerTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft, std::ostream& outputStream = std::cout, std::istream& inputStream = std::cin);
void cpuTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft, CoordGenerator const& generateCoord, std::ostream& outputStream = std::cout);
void printBoard(std::vector<std::vector<Cell>> const& board, std::ostream& outputStream = std::cout);
void placePlayerMines(std::vector<std::vector<Cell>>& board, int mineCount, std::ostream& outputStream = std::cout);
void setCellStatus(std::vector<std::vector<Cell>>& board, unsigned int x, unsigned int y, Owner owner);
bool shoot(int const& x, int const& y, int const& width, int const& height, int& cpuMinesLeft, int& playerMinesLeft, std::vector<std::vector<Cell>>& board, std::ostream& outputStream = std::cout);
void placeCpuMines(std::vector<std::vector<Cell>>& board, int mineCount, CoordGenerator const& generateCoord);

