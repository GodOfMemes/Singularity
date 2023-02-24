#pragma once

#include "Types.h"
#include "../Defines.h"

class Engine
{
public:
    static void send_error(const char* message);
    static GameConfig* get_config();
    static void start(GameConfig* config,ErrorCallback callback);
    static Time get_time_data();
};

SAPI inline void Start(GameConfig* config,ErrorCallback callback)
{
    Engine::start(config,callback);
}

SAPI inline Time GetTimeData()
{
    return Engine::get_time_data();
}