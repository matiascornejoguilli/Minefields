#pragma once

struct Mine 
{
    enum class Status {
        Active = 0,
        Destroyed = 1,
    };

    Status status = Status::Active;
};