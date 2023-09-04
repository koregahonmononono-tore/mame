#pragma once
#include "BaseScene.h"

#include <memory>

#include "../Resource/sprite.h"

class SceneGame : public Mame::Scene::BaseScene
{
public:
    SceneGame() {}
    ~SceneGame()override {}

    void CreateResource()override;                  // ���\�[�X����
    void Initialize()   override;                   // ������
    void Finalize()     override;                   // �I����
    void Begin()        override;                   // ���t���[����ԍŏ��ɌĂ΂��
    void Update(const float& elapsedTime) override; // �X�V����
    void End()          override;                   // ���t���[����ԍŌ�ɌĂ΂��
    void Render(const float& elapsedTime) override; // �`�揈��

    void DrawDebug()    override;

    void SwordRender(bool s[4]);

private:
    // imgui�p
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

