#include <chrono>

#include "../Defines.h"
#include "Types.h"
#include <Windows.h>

#include "../Graphics/GraphicsSystem.h"

HWND hwnd;
GameConfig* Config;
std::chrono::system_clock::time_point PreviousUpdate;
float TotalTime;

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LRESULT lparam)
{
    switch (message)
    {
    case WM_CREATE:
        //Config->OnCreate();
        break;
        // TODO Events for resizing and focusing
    /*case WM_CREATE:
        Config->OnCreate();
        break;
    case WM_CREATE:
        Config->OnCreate();
        break;*/
    case WM_DESTROY:
        if(Config->OnExit) Config->OnExit();
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd,message,wparam,lparam);
    }
    return NULL;
}

void InternalLoop()
{
    if(Config->OnCreate) Config->OnCreate();

    MSG msg = {};
    bool isRunning = true;
    while(isRunning)
    {
        if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            if(msg.message != WM_QUIT)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                isRunning = false;
                continue;
            }
        }

        auto ct = std::chrono::system_clock::now();
        auto elapsedSec = std::chrono::duration<double>();
        if(PreviousUpdate.time_since_epoch().count())
        {
            elapsedSec = ct - PreviousUpdate;
        }
        PreviousUpdate = ct;
        
        double dt = elapsedSec.count();
        TotalTime += dt;
        
        if(Config->OnUpdate) Config->OnUpdate(dt);
        if(Config->OnRender) Config->OnRender(dt);
        // TODO Internal Rendering
    }
}

void Start(GameConfig* config)
{
    if(!config) return;
    Config = config;

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = L"BackendWindowClass";
    wc.lpfnWndProc = &WndProc;

    ATOM id = RegisterClassEx(&wc);

    RECT size = {0,0,config->Width,config->Height};
    AdjustWindowRect(&size,WS_OVERLAPPEDWINDOW,false);

    hwnd = CreateWindowEx(NULL,L"BackendWindowClass", (const wchar_t*)config->Title,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
                          size.right - size.left, size.bottom - size.top, nullptr, nullptr, nullptr, nullptr);

    ShowWindow(hwnd,SW_SHOW);
    UpdateWindow(hwnd);

    GraphicsSystem::Init();
    InternalLoop();
}

double GetRuntime()
{
    return TotalTime;
}



