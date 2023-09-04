#include "SceneGame.h"

#include "../Graphics/Graphics.h"
#include "../Input/Input.h"

#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneTitle.h"

enum SWORD
{
    // １本
    LEFT_UP,    // 左上
    LEFT_DOWN,  // 左下
    RIGHT_UP,   // 右上
    RIGHT_DOWN, // 右下

    // ２本
    LEFT_UP__LEFT_DOWN,     // 左上。左下
    LEFT_UP__RIGHT_UP,      // 左上。右上
    LEFT_UP__RIGHT_DOWN,    // 左上。右下
    LEFT_DOWN__RIGHT_UP,    // 左下。右上
    LEFT_DOWN__RIGHT_DOWN,  // 左下。右下
    RIGHT_UP__RIGHT_DOWN,   // 右上。右下

    // ３本
    LEFT_UP__LEFT_DOWN__RIGHT_UP,   // 左上。左下。右上
    LEFT_UP__LEFT_DOWN__RIGHT_DOWN, // 左上。左下。右下
    LEFT_UP__RIGHT_UP__RIGHT_DOWN,  // 左上。右上。右下
    LEFT_DOWN__RIGHT_UP__RIGHT_DOWN // 左下。右上。右下
};

bool haveSword[14][4]
{
    // １本                        // 刀の所持場所   
    { TRUE, FALSE, FALSE, FALSE }, // 左上
    { FALSE, TRUE, FALSE, FALSE }, // 左下
    { FALSE, FALSE, TRUE, FALSE }, // 右上
    { FALSE, FALSE, FALSE, TRUE }, // 右下

    // ２本
    { TRUE, TRUE, FALSE, FALSE }, // 左上。左下
    { TRUE, FALSE, TRUE, FALSE }, // 左上。右上
    { TRUE, FALSE, FALSE, TRUE }, // 左上。右下
    { FALSE, TRUE, TRUE, FALSE }, // 左下。右上
    { FALSE, TRUE, FALSE, TRUE }, // 左下。右下
    { FALSE, FALSE, TRUE, TRUE }, // 右上。右下

    // ３本
    { TRUE, TRUE, TRUE, FALSE }, // 左上。左下。右上
    { TRUE, TRUE, FALSE, TRUE }, // 左上。左下。右下
    { TRUE, FALSE, TRUE, TRUE }, // 左上。右上。右下
    { FALSE, TRUE, TRUE, TRUE }, // 左下。右上。右下

};

// リソース生成
void SceneGame::CreateResource()
{
    Graphics& graphics = Graphics::Instance();

    // samurai
    samurai = std::make_unique<Sprite>(graphics.GetDevice(),
        L"./Resources/Image/sanaImage/plus.png");

    // sword
    {
        // 左上
        sword[0] = std::make_unique<Sprite>(graphics.GetDevice(),
            L"./Resources/Image/sanaImage/GamePadA.png");

        // 左下
        sword[1] = std::make_unique<Sprite>(graphics.GetDevice(),
            L"./Resources/Image/sanaImage/GamePadB.png");

        // 右上
        sword[2] = std::make_unique<Sprite>(graphics.GetDevice(),
            L"./Resources/Image/sanaImage/GamePadX.png");

        // 右下
        sword[3] = std::make_unique<Sprite>(graphics.GetDevice(),
            L"./Resources/Image/sanaImage/GamePadY.png");
    }


    // sprite
    {
        for (std::unique_ptr<Sprite>& s : sprite)
        {
            s = nullptr;
        }

        sprite[static_cast<UINT>(SPRITE::LOAD)] =
            std::make_unique<Sprite>(graphics.GetDevice(),
                //L"./Resources/Image/sanaImage/load.png");
                L"./Resources/Image/sanaImage/GamePadY.png");
        sprite[static_cast<UINT>(SPRITE::LOAD)]->
            GetSpriteTransform()->SetTexSize(DirectX::XMFLOAT2(128.0f, 128.0f));
        sprite[static_cast<UINT>(SPRITE::LOAD)]->
            GetSpriteTransform()->SetSize(DirectX::XMFLOAT2(200.0f, 200.0f));

        numSprite = std::make_unique<Sprite>(graphics.GetDevice(),
            L"./Resources/Image/number.png");
    }


}

// 初期化
void SceneGame::Initialize()
{
    // カメラ
    Camera::Instance().Initialize();

    button = false;
    backColor = { 1.0f, 0.2f, 1.0f, 1.0f };

    numSprite->GetSpriteTransform()->SetTexSize(DirectX::XMFLOAT2(100, 100));
    numSprite->GetSpriteTransform()->SetSize(DirectX::XMFLOAT2(100, 100));

    // samurai
    samurai->GetSpriteTransform()->SetPos(DirectX::XMFLOAT2(500, 300));
    samurai->GetSpriteTransform()->SetSize(DirectX::XMFLOAT2(256, 256));
    samurai->GetSpriteTransform()->SetTexSize(DirectX::XMFLOAT2(128, 128));

    // sword
    {
        // 位置
        sword[0]->GetSpriteTransform()->SetPos(DirectX::XMFLOAT2(0, 0));
        sword[1]->GetSpriteTransform()->SetPos(DirectX::XMFLOAT2(0, 400));
        sword[2]->GetSpriteTransform()->SetPos(DirectX::XMFLOAT2(900, 0));
        sword[3]->GetSpriteTransform()->SetPos(DirectX::XMFLOAT2(900, 400));

        // サイズ
        for (int i = 0; i < 4; ++i)
        {
            sword[i]->GetSpriteTransform()->SetSize(DirectX::XMFLOAT2(256, 256));
            sword[i]->GetSpriteTransform()->SetTexSize(DirectX::XMFLOAT2(128, 128));
        }
    }
}

// 終了化
void SceneGame::Finalize()
{
}

// Updateの前に呼び出される
void SceneGame::Begin()
{
}

// 更新処理
void SceneGame::Update(const float& elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    Mouse& mouse = Input::Instance().GetMouse();
    mousePos = { static_cast<float>(mouse.GetPositionX()), static_cast<float>(mouse.GetPositionY()) };

    DirectX::XMFLOAT2 sprite0Pos = sprite[0]->GetSpriteTransform()->GetPos();
    DirectX::XMFLOAT2 sprite0Size = sprite[0]->GetSpriteTransform()->GetSize();

    if (mouse.GetButtonDown() & mouse.BTN_LEFT
        && mousePos.x >= sprite0Pos.x && mousePos.x <= (sprite0Pos.x + sprite0Size.x) //* 1.5f
        && mousePos.y >= sprite0Pos.y && mousePos.y <= (sprite0Pos.y + sprite0Size.y) //* 1.5f
        )
    {
        button = true;
        backColor = { 0.2f, 0.2f, 0.0f, 1.0f };
    }
    else
    {
        button = false;
        backColor = { 0.2f, 0.2f, 0.2f, 1.0f };
    }



    //if (gamePad.GetButtonDown() & GamePad::BTN_A)
    //    Mame::Scene::SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
}

// Updateの後に呼び出される
void SceneGame::End()
{
}

// 描画処理
void SceneGame::Render(const float& elapsedTime)
{
    Graphics& graphics = Graphics::Instance();
    // 描画の初期化
    {
        ID3D11DeviceContext* immediate_context = graphics.GetDeviceContext();
        ID3D11RenderTargetView* render_target_view = graphics.GetRenderTargetView();
        ID3D11DepthStencilView* depth_stencil_view = graphics.GetDepthStencilView();

        //FLOAT color[]{ 0.2f, 0.2f, 1.0f, 1.0f };
        FLOAT color[]{ backColor.x, backColor.y, backColor.z, backColor.w };
        immediate_context->ClearRenderTargetView(render_target_view, color);
        immediate_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        immediate_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);

        // カメラ関係
        RenderContext rc;
        rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };

        Shader* shader = graphics.GetShader();
        shader->Begin(graphics.GetDeviceContext(), rc);
    }

    // 描画
    {
        //for (auto&s : sprite)
        //{
        //    if (s == nullptr)continue;
        //
        //    s->Render();
        //}
        //
        //Mouse& mouse = Input::Instance().GetMouse();
        //mousePos = { static_cast<float>(mouse.GetPositionX()), static_cast<float>(mouse.GetPositionY()) };
        //
        //
        //int mPosX = mousePos.x;
        //int mPosY = mousePos.y;
        //int temp;
        //
        //// X軸
        //{
        //    numSprite->GetSpriteTransform()->SetPosY(0.0f);
        //
        //    temp = mPosX / 1000 % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(0.0f);
        //    numSprite->Render();
        //
        //    temp = mPosX / 100 % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(100.0f);
        //    numSprite->Render();
        //
        //    temp = mPosX / 10 % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(200.0f);
        //    numSprite->Render();
        //
        //    temp = mPosX % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(300.0f);
        //    numSprite->Render();
        //}
        //
        //// Y軸
        //{
        //    numSprite->GetSpriteTransform()->SetPosY(100.0f);
        //
        //    temp = mPosY / 100 % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(0.0f);
        //    numSprite->Render();
        //
        //    temp = mPosY / 10 % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(100.0f);
        //    numSprite->Render();
        //
        //    temp = mPosY % 10 * 100;
        //    numSprite->GetSpriteTransform()->SetTexPosX(temp);
        //    numSprite->GetSpriteTransform()->SetPosX(200.0f);
        //    numSprite->Render();
        //}


        // samurai
        samurai->Render();

        // sword
        {
            SwordRender(haveSword[hSword]);
        }
    }
}

// debug用
void SceneGame::DrawDebug()
{
    // カメラ
    Camera::Instance().DrawDebug();

    ImGui::DragFloat2("mousePos", &mousePos.x);
    ImGui::InputInt("btn", &button);

    ImGui::SliderInt("haveSword", &hSword, 0, 13);
}

void SceneGame::SwordRender(bool s[4])
{
    for (int i = 0; i < 4; ++i)
    {
        if (s[i])sword[i]->Render();
    }
}
