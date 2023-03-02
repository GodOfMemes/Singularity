#pragma once

#include <chrono>
#include <memory>
#include "../Defines.h"

typedef void (__stdcall * generic_delegate)(void);
typedef void (__stdcall * update_delegate)(void);

// TODO Create Bindings for Beef and C#

struct AppConfig
{
    char* title = nullptr;
    int width = 1280;
    int height = 720;
    int targetFps = 120;
    generic_delegate on_create = nullptr;
    update_delegate on_update = nullptr;
    update_delegate on_frame_independent_update = nullptr;
    generic_delegate on_shutdown = nullptr;
};

class GLFWwindow;
class GraphicsEngine;

class Engine
{
public:
    static void Start(AppConfig *config);
    static AppConfig* GetConfig();
    static float GetFPS();

private:
    static AppConfig* Config;
    static GLFWwindow* window;

    static std::shared_ptr<GraphicsEngine> _graphicsEngine;

    static void CleanUp();
};

SAPI inline void Start(AppConfig* config)
{
    Engine::Start(config);
}
