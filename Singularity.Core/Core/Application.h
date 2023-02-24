#pragma once

#include <chrono>
#include "Types.h"


class Application
{
public:
    Application();
    virtual ~Application();
    
    static Application* create(GameConfig* config);
    virtual void start() = 0;
    virtual Time get_app_time_data();
protected:
    std::chrono::system_clock::time_point previous_update;
    float total_time;
    double deltaTime;
};
