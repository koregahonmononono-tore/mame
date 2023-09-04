#pragma once
#include "BaseScene.h"

#include <memory>

#include "../Resource/sprite.h"

class SceneGame : public Mame::Scene::BaseScene
{
public:
    SceneGame() {}
    ~SceneGame()override {}

    void CreateResource()override;                  // リソース生成
    void Initialize()   override;                   // 初期化
    void Finalize()     override;                   // 終了化
    void Begin()        override;                   // 毎フレーム一番最初に呼ばれる
    void Update(const float& elapsedTime) override; // 更新処理
    void End()          override;                   // 毎フレーム一番最後に呼ばれる
    void Render(const float& elapsedTime) override; // 描画処理

    void DrawDebug()    override;

    void SwordRender(bool s[4]);

private:
    // imgui用
    int hSword = 0;

private:
    enum class SPRITE
    {
        LOAD,
    };

private:
    std::unique_ptr<Sprite> samurai;
    std::unique_ptr<Sprite> sword[4];

    std::unique_ptr<Sprite> sprite[10];

    std::unique_ptr<Sprite> numSprite;

    DirectX::XMFLOAT4 backColor{ 0.2f, 0.2f, 1.0f, 1.0f };

    DirectX::XMFLOAT2 mousePos{};
    int button = false;
};

