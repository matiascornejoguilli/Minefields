#pragma once
#include <utility>
#include "Player.h"
#include <iostream>

void inputBoardSize(int& height, int& width);
int inputMines(Player& player);
std::pair<int, int> generateRandomCoord(int width, int height);
int inputFunc(const std::string& message);