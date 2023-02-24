#include "Engine.h"
#include "Application.h"

Application* app;
app_config* Config;
message_delegate error_callback;

void Engine::send_error(const char* message)
{
    if(error_callback)
    {
        error_callback(const_cast<char*>(message));
    }
}

app_config* Engine::get_config()
{
    return Config;
}

void Engine::start(app_config* config,message_delegate callback)
{
    srand(time(nullptr));
    error_callback = callback;
    if(!config)
    {
        send_error("Config is null");
        return;
    }
    Config = config;
    
    app = Application::create(Config);
    //GraphicsSystem::Init();
    app->start();
    delete app;
}

time_data Engine::get_time_data()
{
    if(!app) return {0,0};
    return app->get_app_time_data();
}



