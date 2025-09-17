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
    static unsigned int const kOption1 = 1;
    static unsigned int const kOption2 = 2;

    std::cout << "Welcome to Game! Select an option to continue:\n1. Options\n2. Quit\n> ";
    std::cin >> userSelection;
    if (userSelection == kOption1)
    {
        std::cout << "MainMenu: User selected options\n";
        return {&stateOptionsUpdate};
    }
    else if (userSelection == kOption2)
    {
        std::cout << "MainMenu: User selected quit\n";
        return {&stateQuitUpdate};
    }

    std::cout << "MainMenu: User did not select anything\n";
    return context.currentState;
}

State statePlayingUpdate(GameContext& context)
{
    std::vector<std::vector<bool>> matrix(context.height, std::vector<bool>(context.width, false));

    std::cout << "\n===== NEW ROUND =====\n";

    std::cout << "\n--- Player's turn ---\n";

    playerTurn(context.board.grid, matrix, context.width, context.height, context.playerMinesLeft, context.cpuMinesLeft);

    if (context.cpuMinesLeft <= 0)
    {
        std::cout << "CPU has no mines left. You win!\n";
        return {&stateQuitUpdate}; // o volvé a menú si preferís
    }

    std::cout << "\n--- CPU's turn ---\n";
    cpuTurn(context.board.grid, matrix, context.width, context.height, context.playerMinesLeft, context.cpuMinesLeft, context.generateCoord);

    printBoard(context.board.grid);
    std::cout << "\nMines left - Player: " << context.playerMinesLeft << ", CPU: " << context.cpuMinesLeft << "\n";

    if (context.playerMinesLeft <= 0)
    {
        std::cout << "You have no mines left. CPU wins!\n";
        return {&stateQuitUpdate}; // o volvé a menú si preferís
    }
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
	
