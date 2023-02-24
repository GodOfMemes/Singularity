#pragma once
#include <d3d11.h>
#include <map>
#include <vector>

#include "../Defines.h"

struct VertexBuffer;

class GraphicsSystem
{
public:
    static GraphicsSystem* GetGraphicsSystem();
    static void Init();
private:
    ID3D11Device* _d3dDevice = nullptr;
    ID3D11DeviceContext* _immContext = nullptr;
    IDXGIDevice* _dxgiDevice = nullptr;
    IDXGIAdapter* _dxgiAdapter = nullptr;
    IDXGIFactory* _dxgiFactory = nullptr;

    std::pmr::map<unsigned int,std::vector<VertexBuffer*> > vertexBuffers;
};
