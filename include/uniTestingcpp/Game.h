#pragma once
#include <functional>

typedef std::function<std::pair<int, int>()> CoordGenerator;

void playTurns(int height, int width, int totalMines, const CoordGenerator& generateCoord);