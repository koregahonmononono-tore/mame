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


public: // 取得・設定　関連
    Transform* GetTransform() { return model->GetTransform(); }
    Transform* GetCollisionSqhereTransform() { return &collisionSqhereTransform; }

    void SetDebugSqhereOffset(DirectX::XMFLOAT3 offset) { debugSqhereOffset = offset; }
    DirectX::XMFLOAT3 GetDebugSqhereOffset() { return debugSqhereOffset; }

    void SetRange(const float& r) { range = r; }
    float GetRange() { return range; }

public:
    std::unique_ptr<Model> model = nullptr;

#ifdef _DEBUG
    std::unique_ptr<Model> debugSqhere = nullptr;   // 当たり判定用＿球
#endif // _DEBUG

private:
    Transform collisionSqhereTransform{};
    DirectX::XMFLOAT3 debugSqhereOffset{};  // 当たり判定用
    float range = 1.0f;                     // 球当たり判定半径
    
    
public: // --- ImGui用 --- //
    const char* GetName() const { return name.c_str(); }
    void SetName(std::string n) { name = n; }
    static int nameNum;

private: // --- ImGui用 --- //
    std::string name = {};
};

