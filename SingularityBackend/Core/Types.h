#pragma once

typedef void (__stdcall * Create)(void);
typedef void (__stdcall * Exit)(void);
typedef void (__stdcall * Update)(double);
typedef void (__stdcall * Render)(double);

struct GameConfig
{
public:
    char* Title;
    int Width;
    int Height;
    Create OnCreate;
    Exit OnExit;
    Update OnUpdate;
    Render OnRender;
    
};
