#pragma once
#include "GameContext.h"

namespace Minefields
{

struct State;
struct GameContext;

using StateUpdateFn = State (*)(GameContext&);


struct State
{
    StateUpdateFn updateFunction{nullptr};
};

State stateMainMenuUpdate(GameContext& context);
State stateOptionsUpdate(GameContext& context);
State stateQuitUpdate(GameContext& context); 

void runMainLoop();

void clearConsoleBuffer();

} // namespace Minefields