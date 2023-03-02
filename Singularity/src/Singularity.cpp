#include "../include/Core/Engine.h"

#include <GLFW/glfw3.h>

// TODO Remove this
void d()
{

}

void c()
{

}

int main()
{
    AppConfig config;
    config.title = "Test";
    config.width = 1600;
    config.height = 720;
    config.on_create = d;
    config.on_shutdown = c;
    Start(&config);
}
