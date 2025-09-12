#include <Minefields/GameContext.h>
#include <Minefields/States.h>
#include <Minefields/Game.h>
#include <iostream>
namespace Minefields
{
void clearConsoleBuffer();

void clearConsoleBuffer()
{
    char const* const kClearConsoleBufferCommand = "cls";
    system(kClearConsoleBufferCommand);
}
void playTurns(int height, int width, int totalMines, CoordGenerator const& generateCoord);
void playerTurn(std::vector<std::vector<Cell>>& board, std::vector<std::vector<bool>>& matrix, int width, int height, int& playerMinesLeft, int& cpuMinesLeft);

State stateQuitUpdate(GameContext& context)
{
    return {nullptr};
}

State stateOptionsUpdate(GameContext& context)
{
    std::cout << "Inside options\n";

    return context.currentState;
}

State stateMainMenuUpdate(GameContext& context)
{
    if (context.width > 0 && context.height > 0 && context.playerMinesLeft > 0 && context.cpuMinesLeft > 0 && context.board.grid.empty())
    {
        context.board = Board(context.width, context.height);
        context.resetAttemptedShots(context);

        placePlayerMines(context.board.grid, context.playerMinesLeft);
        placeCpuMines(context.board.grid, context.cpuMinesLeft, context.generateCoord);
    }

    std::cout << "Inside main menu\n";

    int userSelection = 0;
    static unsigned int const Option1 = 1;
    static unsigned int const Option2 = 2;

    std::cout << "Welcome to Game! Select an option to continue:\n1. Options\n2. Quit\n> ";
    std::cin >> userSelection;
    if (userSelection == Option1)
    {
        std::cout << "MainMenu: User selected options\n";
        return {&stateOptionsUpdate};
    }
    else if (userSelection == Option2)
    {
        std::cout << "MainMenu: User selected quit\n";
        return {&stateQuitUpdate};
    }

    std::cout << "MainMenu: User did not select anything\n";
    return context.currentState;
}

void runMainLoop()
{
    bool quit = false;
    GameContext context;
    context.currentState = {&stateMainMenuUpdate};
    while (!quit)
    {
        if (context.currentState.updateFunction != nullptr)
        {
            context.currentState = (*context.currentState.updateFunction)(context);
        }
        quit = context.currentState.updateFunction == nullptr;
    }
}
	
	
}