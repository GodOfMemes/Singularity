#pragma once
#include <d3d11.h>

struct VertexBuffer
{
public:
    VertexBuffer(void* data, unsigned int size,unsigned int list_size)
        : vertex_size(0), list_size(0), _buffer(nullptr),_layout(nullptr)
    {
        D3D11_BUFFER_DESC buffer_desc = {};
        buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        buffer_desc.ByteWidth = size * list_size;
        buffer_desc.CPUAccessFlags = 0;
        buffer_desc.MiscFlags = 0;
    }

private:
    unsigned int vertex_size;
    unsigned int list_size;

    ID3D11Buffer* _buffer;
    ID3D11InputLayout* _layout;
};
