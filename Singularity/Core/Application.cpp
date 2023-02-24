#include "Application.h"
#include "Platform/Win32/Win32Application.h"

Application::Application()
{
}

Application::~Application()
{
}

Application* Application::create(app_config* config)
{
#ifdef _WINDOWS
    return new Win32Application(config);
#endif
}

time_data Application::get_app_time_data()
{
    return {0,0};
}
