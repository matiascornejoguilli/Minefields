#pragma once
#include <utility>
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <string>

void inputBoardSize(int& height, int& width, std::ostream& outputStream = std::cout, std::istream& inputStream = std::cin);
int inputMines(Player& player, std::ostream& outputStream = std::cout, std::istream& inputStream = std::cin);
std::pair<int, int> generateRandomCoord(int width, int height);
int inputInt(std::string const& message, std::ostream& outputStream = std::cout, std::istream& inputStream = std::cin);