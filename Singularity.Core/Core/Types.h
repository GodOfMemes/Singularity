#pragma once

typedef void (__stdcall * VoidDelegate)(void);
typedef void (__stdcall * DoubleDelegate)(double);
typedef void (__stdcall * ErrorCallback)(char*);

enum GraphicsBackend
{
    D3D11 = 0
};

struct Time
{
    double deltaTime;
    float Runtime;
};

struct GameConfig
{
public:
    char* Title;
    int Width;
    int Height;
    GraphicsBackend graphics_backend;
    VoidDelegate OnCreate;
    VoidDelegate OnExit;
    DoubleDelegate OnUpdate;
    DoubleDelegate OnRender;
};