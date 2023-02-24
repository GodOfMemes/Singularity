#include "Application.h"
#include "Platform/Win32/Win32Application.h"

Application::Application()
{
}

Application::~Application()
{
}

Application* Application::create(GameConfig* config)
{
#ifdef _WINDOWS
    return new Win32Application(config);
#endif
}

Time Application::get_app_time_data()
{
    return {0,0};
}
