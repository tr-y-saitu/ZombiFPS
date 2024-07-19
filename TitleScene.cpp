#include "Common.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
    : isKeyOn           (false)
    , isKeyRelease      (false)
    , isPreviousKeyOn   (false)
{
    titleSceneUI = TitleSceneUI();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{

}

/// <summary>
/// シーンの更新処理
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* TitleScene::UpdateScene()
{
    // テスト描画
    DrawString(0, 0, "Title", GetColor(255, 255, 255), true);

    // キー入力の更新
    UpdateKeyState();

    // オブジェクト更新
    titleSceneUI.Update();      // UIの更新

    // スペースキーが入力されたらシーン推移
    if (isKeyRelease)
    {
        // キーは離れていません
        isKeyRelease = false;

        // ゲームシーンに推移
        return new GameScene();
    }

    // 現状のシーン
    return this;
}

/// <summary>
/// 音の更新
/// </summary>
void TitleScene::UpdateSound()
{

}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
    // UIの描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void TitleScene::DrawUI()
{
    titleSceneUI.Draw();
}

/// <summary>
/// 入力更新
/// </summary>
void TitleScene::UpdateKeyState()
{
    // キー入力すでにされている場合
    if (isKeyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            isKeyOn = false;          // キーが入力されていない
            isKeyRelease = true;      // キーが離れた
        }
    }
    else if (isPreviousKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        // キーは長押しされていない && 前フレームで入力なし && キーが押された
        isKeyRelease = false;   // キーは離れていない
        isKeyOn = true;         // キーが押された
    }

    // キー入力されたら
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        isPreviousKeyOn = true;   // このフレームではキーが押された
    }
    else
    {
        isPreviousKeyOn = false;  // このフレームでキーは押されなかった
    }
}