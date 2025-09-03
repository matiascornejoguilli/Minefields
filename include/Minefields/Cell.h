#pragma once
#include <optional>
#include "Mine.h"

enum class Owner 
{
    None = '.',
    Player = 'J',
    Cpu = 'C',
    Shared = 'S',
    Destroy = 'x',
    Disabled = '#'
};

struct Cell 
{
    Owner owner = Owner::None;
    std::optional<Mine> mine;
};