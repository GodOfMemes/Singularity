#include "../../include/Core/Engine.h"
#include "../../include/Graphics/GraphicsEngine.h"
#include "../../include/Core/Log.h"
#include "GLFW/glfw3.h"
#include "fmt/core.h"

AppConfig* Engine::Config;
GLFWwindow* Engine::window;
std::shared_ptr<GraphicsEngine> Engine::_graphicsEngine;

float currentFPS;
bool isRunning;

void glfwErrorCallback(int error_code,const char* description)
{
    ENGINE_ERROR(fmt::format("GLFW Error:{0} {1}",error_code,description).c_str());
}

void Engine::Start(AppConfig* config)
{
    if(isRunning) return;
    srand(time(nullptr));

    //Log::InitLogger();
    LogManager::InitLogger();

    if(!glfwInit())
    {
        ENGINE_CRITICAL("GLFW couldn't init");
        return;
    }

    if(!config)
    {
        ENGINE_CRITICAL("AppConfig was null");
        return;
    }
    Config = config;

    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwSetErrorCallback(glfwErrorCallback);

    window = glfwCreateWindow(config->width, config->height, config->title, nullptr, nullptr);

    if(!window)
    {
        ENGINE_CRITICAL("GLFW couldn't create window");
        glfwTerminate();
        return;
    }

    isRunning = true;

    _graphicsEngine = std::make_shared<GraphicsEngine>();

    if(!_graphicsEngine->Init())
    {
        glfwTerminate();
        return;
    }

    if(Config->on_create) Config->on_create();
    double lastTime = 0;
    while(!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();
        double deltaTime = time - lastTime;

        glfwPollEvents();

        if(Config->on_update) Config->on_update();

        if(Config->targetFps > 0)
        {
            if(deltaTime >= 1.0/Config->targetFps)
            {
                lastTime = time;
                currentFPS = 1.0/deltaTime;

                //_graphicsEngine->StartRendering();
                if(Config->on_frame_independent_update) Config->on_frame_independent_update();
                //_graphicsEngine->EndRendering();
            }
        }
        else
        {
            lastTime = time;
            currentFPS = 1.0/deltaTime;

            //_graphicsEngine->StartRendering();
            if(Config->on_frame_independent_update) Config->on_frame_independent_update();
            //_graphicsEngine->EndRendering();
        }
    }

    CleanUp();
}

AppConfig* Engine::GetConfig()
{
    return Config;
}

void Engine::CleanUp()
{
    if(Config->on_shutdown) Config->on_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    isRunning = false;
}

float Engine::GetFPS()
{
    return currentFPS;
}
