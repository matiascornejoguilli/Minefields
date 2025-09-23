#include <Minefields/GameContext.h>
#include <Minefields/States.h>
#include <Minefields/Game.h>
#include <iostream>
namespace Minefields
{
static constexpr int kNoMinesLeft = 0;
static unsigned int const kOption1 = 1;
static unsigned int const kOption2 = 2;
static unsigned int const kOption3 = 3;


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

State statePlayingUpdate(GameContext& context)
{
    std::vector<std::vector<bool>> matrix(context.height, std::vector<bool>(context.width, false));

    std::cout << "\n===== NEW ROUND =====\n";

    std::cout << "\n--- Player's turn ---\n";

    playerTurn(context.board.grid, matrix, context.width, context.height, context.playerMinesLeft, context.cpuMinesLeft);

    if (context.cpuMinesLeft <= kNoMinesLeft)
    {
        return {&stateWonUpdate};
    }

    std::cout << "\n--- CPU's turn ---\n";
    cpuTurn(context.board.grid, matrix, context.width, context.height, context.playerMinesLeft, context.cpuMinesLeft, context.generateCoord);

    printBoard(context.board.grid);
    std::cout << "\nMines left - Player: " << context.playerMinesLeft << ", CPU: " << context.cpuMinesLeft << "\n";

    if (context.playerMinesLeft <= kNoMinesLeft)
    {
        return {&stateLostUpdate};
    }

    return {&statePlayingUpdate};
}

State stateWonUpdate(GameContext& context)
{
    std::cout << "CPU has no mines left. You win!\n";
    return {nullptr};
}

State stateLostUpdate(GameContext& context)
{
    std::cout << "You have no mines left. CPU wins!\n";
    return {nullptr};
}

State stateOptionsUpdate(GameContext& context)
{
    std::cout << "Inside options\n";

    std::cout << "1) Back to menu\n2) Quit\n> ";

    int sel = 0;

    std::cin >> sel;

    if (sel == kOption2)
    {
        return {&stateQuitUpdate};
    }

    return {&stateMainMenuUpdate};
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

    std::cout << "Welcome to Game! Select an option to continue:\n1. Options\n2. Quit\n3. Play\n> ";
    std::cin >> userSelection;
    if (userSelection == kOption1)
    {
        std::cout << "MainMenu: User selected options\n";
        return {&stateOptionsUpdate};
    }
    if (userSelection == kOption2)
    {
        std::cout << "MainMenu: User selected quit\n";
        return {&stateQuitUpdate};
    }
    else if (userSelection == kOption3)
    {
        return {&statePlayingUpdate};
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