#pragma once

namespace Minefields
{

struct GameContext;
struct State;
using StateUpdateFn = State (*)(GameContext&);

struct State
{
    StateUpdateFn updateFunction;
};

State stateMainMenuUpdate(GameContext& context);
State stateOptionsUpdate(GameContext& context);
State stateQuitUpdate(GameContext& context);
State statePlayingUpdate(GameContext& context);

State stateWonUpdate(GameContext& context);
State stateLostUpdate(GameContext& context);

void runMainLoop();
void clearConsoleBuffer();

} // namespace Minefields