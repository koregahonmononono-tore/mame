#pragma once

#include "../Graphics/Model.h"

class Character
{
public:
    Character();
    virtual ~Character() {}

    virtual void Initialize();
    virtual void Update(const float& elapsedTime);
    virtual void Render(const float& elapsedTime, const float& scale);
    virtual void DrawDebug();


public: // �擾�E�ݒ�@�֘A
    Transform* GetTransform() { return model->GetTransform(); }
    Transform* GetCollisionSqhereTransform() { return &collisionSqhereTransform; }

    void SetDebugSqhereOffset(DirectX::XMFLOAT3 offset) { debugSqhereOffset = offset; }
    DirectX::XMFLOAT3 GetDebugSqhereOffset() { return debugSqhereOffset; }

    void SetRange(const float& r) { range = r; }
    float GetRange() { return range; }

public:
    std::unique_ptr<Model> model = nullptr;

#ifdef _DEBUG
    std::unique_ptr<Model> debugSqhere = nullptr;   // �����蔻��p�Q��
#endif // _DEBUG

private:
    Transform collisionSqhereTransform{};
    DirectX::XMFLOAT3 debugSqhereOffset{};  // �����蔻��p
    float range = 1.0f;                     // �������蔻�蔼�a
    
    
public: // --- ImGui�p --- //
    const char* GetName() const { return name.c_str(); }
    void SetName(std::string n) { name = n; }
    static int nameNum;

private: // --- ImGui�p --- //
    std::string name = {};
};

