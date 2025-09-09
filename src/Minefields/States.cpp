#include <Minefields/GameContext.h>
#include <Minefields/States.h>
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
    std::cout << "Inside main menu\n";

    int userSelection = 0;
    std::cout << "Welcome to Game! Select an option to continue:\n1. Options\n2. Quit\n> ";
    std::cin >> userSelection;
    if (userSelection == 1)

    {
        std::cout << "MainMenu: User selected options\n";
        return {&stateOptionsUpdate};
    }
    else if (userSelection == 2)
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