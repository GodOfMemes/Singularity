#pragma once

typedef void (__stdcall * generic_delegate)(void);
typedef void (__stdcall * double_delegate)(double);
typedef void (__stdcall * message_delegate)(char*);

enum graphics_backend
{
    D3D11 = 0
};

struct time_data
{
    double delta_time;
    float runtime;
};

struct app_config
{
public:
    char16_t* title;
    int width;
    int height;
    graphics_backend graphics_backend;
    generic_delegate on_create;
    generic_delegate on_exit;
    double_delegate on_update;
    double_delegate on_render;
};