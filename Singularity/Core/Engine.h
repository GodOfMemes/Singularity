#pragma once

#include "Types.h"
#include "../Defines.h"

class Engine
{
public:
    static void send_error(const char* message);
    static app_config* get_config();
    static void start(app_config* config,message_delegate callback);
    static time_data get_time_data();
};

SAPI inline void Start(app_config* config,message_delegate callback)
{
    Engine::start(config,callback);
}

SAPI inline time_data GetTimeData()
{
    return Engine::get_time_data();
}