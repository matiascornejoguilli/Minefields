#pragma once
#include <Minefields/Board.h>
#include <Minefields/Cell.h>
#include <functional>
#include <utility>
#include <vector>

namespace Minefields
{

using CoordGenerator = std::function<std::pair<int, int>()>;

    enum class Attempted : unsigned char
    {
        No,
        Yes
    };
struct GameContext
{
    int width = 0;
    int height = 0;
    int playerMinesLeft = 0;
    int cpuMinesLeft = 0;

    Board board{0, 0};
    std::vector<std::vector<Attempted>> attemptedShots;
    CoordGenerator generateCoord;

    inline void resetAttemptedShots(GameContext& gameContext)
    {
        gameContext.attemptedShots.assign(gameContext.height, std::vector<Attempted>(gameContext.width, Attempted::No));
    };

}; // namespace Minefields