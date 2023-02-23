#include "GraphicsSystem.h"
#include <memory>
#include <d3dcommon.h>

std::unique_ptr<GraphicsSystem> graphics_system = std::make_unique<GraphicsSystem>();

GraphicsSystem* GraphicsSystem::GetGraphicsSystem()
{
    return graphics_system.get();
}

void GraphicsSystem::Init()
{
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
        D3D_DRIVER_TYPE_UNKNOWN
    };

    D3D_FEATURE_LEVEL feature_level[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };

    D3D_FEATURE_LEVEL _ = {};
    HRESULT result = {};
    for (const auto& driver_type : driver_types)
    {
        result = D3D11CreateDevice(nullptr, driver_type, nullptr, 0, feature_level,ARRAYSIZE(feature_level),
                                   D3D11_SDK_VERSION, &graphics_system->_d3dDevice, &_, &graphics_system->_immContext);
        if(SUCCEEDED(result)) break;
    }
    
    if(FAILED(result)) return;
    
    // TODO 
    //_deviceContext = std::make_shared<DeviceContext>(graphics_system->_immContext,graphics_system);
    graphics_system->_d3dDevice->QueryInterface(__uuidof(IDXGIDevice),(void**)&graphics_system->_dxgiDevice);
    graphics_system->_dxgiDevice->GetParent(__uuidof(IDXGIAdapter),(void**)&graphics_system->_dxgiAdapter);
    graphics_system->_dxgiAdapter->GetParent(__uuidof(IDXGIFactory),(void**)&graphics_system->_dxgiFactory);
}
