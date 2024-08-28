#include "ClearScene.h"
#include "ClearSceneUI.h"
#include "ImageDataManager.h"
#include "SoundManager.h"
#include "Input.h"
#include "ResultScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ClearScene::ClearScene()
    : isKeyOn(false)
    , isKeyRelease(false)
    , isPreviousKeyOn(false)
{
    // リソース管理
    imageDataManager    = ImageDataManager::GetInstance();

    // 演出関連
    soundManager        = SoundManager::GetInstance();

    // 入力関連
    input               = new Input();

    // UI
    clearSceneUI        = new ClearSceneUI();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ClearScene::~ClearScene()
{
    delete(input);
    delete(clearSceneUI);
}

/// <summary>
/// 初期化
/// </summary>
void ClearScene::Initialize()
{
    clearSceneUI->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* ClearScene::UpdateScene()
{
    // キー入力の更新
    UpdateKeyState();
    input->Update();

    // UIの更新
    clearSceneUI->Update();

    // スペースキーが入力されたらシーン推移
    if (isKeyRelease)
    {
        // キーは離れていません
        isKeyRelease = false;

        // チュートリアルシーンに推移
        return new ResultScene();
    }

    // 現状のシーン
    return this;
}

/// <summary>
/// 音の更新
/// </summary>
void ClearScene::UpdateSound()
{

}

/// <summary>
/// 描画
/// </summary>
void ClearScene::Draw()
{
    // UIの描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void ClearScene::DrawUI()
{
    clearSceneUI->Draw();
}

/// <summary>
/// 入力更新
/// </summary>
void ClearScene::UpdateKeyState()
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
