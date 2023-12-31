#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>

#include "../Resource/sprite.h"

class SkyBox
{
public:
    //SkyBox(ID3D11Device* device, Sprite* sprite);
    SkyBox(ID3D11Device* device, std::shared_ptr<Sprite> sprite);
    ~SkyBox() {}

    struct Vertex
    {
        DirectX::XMFLOAT3 position;
    };

    struct CbScene
    {
        DirectX::XMFLOAT4X4 inverseViewProjection;
        DirectX::XMFLOAT4 viewPosition;
    };

    void Render(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX V/*view*/, DirectX::XMMATRIX P/*projection*/);

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer>        sceneConstantBuffer;
    Microsoft::WRL::ComPtr<ID3D11VertexShader>  vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>   pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>   inputLayout;

    Microsoft::WRL::ComPtr<ID3D11BlendState>        blendState;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState>   rasterizerState;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
    Microsoft::WRL::ComPtr<ID3D11SamplerState>      samplerState;

    std::shared_ptr<Sprite> sprite;
};