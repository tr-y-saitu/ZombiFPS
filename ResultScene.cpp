#include "ResultScene.h"
#include "ResultSceneUI.h"
#include "TitleScene.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"
#include "Input.h"
#include "Stage.h"
#include "ShutterController.h"
#include "SceneCamera.h"
#include "GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
    : isKeyOn           (false)
    , isKeyRelease      (false)
    , isPreviousKeyOn   (false)
{
    // 管理クラス
    soundManager        = SoundManager::GetInstance();
    effectManager       = EffectManager::GetInstance();
    imageDataManager    = ImageDataManager::GetInstance();
    modelDataManager    = ModelDataManager::GetInstance();

    // 入力情報
    input               = new Input();

    // オブジェクト
    stage               = new Stage();
    shutterController   = new ShutterController();

    // カメラ
    sceneCamera         = new SceneCamera();

    // UI
    resultSceneUI       = new ResultSceneUI();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
    delete(input);
    delete(stage);
    delete(shutterController);
    delete(sceneCamera);
    delete(resultSceneUI);
}

/// <summary>
/// 初期化
/// </summary>
void ResultScene::Initialize()
{
    stage->InitializeTitleScene();
    shutterController->InitializeTitleScene();
    sceneCamera->Initialize(VGet(10, 10, 10), VGet(0, 0, 0));
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* ResultScene::UpdateScene()
{
    // 入力処理
    UpdateKeyState();

    // オブジェクト更新
    shutterController->Update();
    sceneCamera->UpdateResultScene();

    // UI更新
    resultSceneUI->Update();

    // 演出更新
    UpdateSound();
    UpdateEffect();

    // キーを入力したらシーン切り替え
    if (isKeyRelease || resultSceneUI->GetNextState() != SceneBase::SceneState::Same)
    {
        // キーは離れていません
        isKeyRelease = false;

        // UIで指定されたシーンに推移
        if (resultSceneUI->GetNextState() == SceneBase::SceneState::Title)
        {
            return new TitleScene();
        }
        else if (resultSceneUI->GetNextState() == SceneBase::SceneState::Game)
        {
            return new GameScene();
        }
    }

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
    // オブジェクトの描画
    stage->Draw();
    shutterController->Draw();


    // UIの描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void ResultScene::DrawUI()
{
    resultSceneUI->Draw();
}

/// <summary>
/// 音の更新
/// </summary>
void ResultScene::UpdateSound()
{

}

/// <summary>
/// エフェクトの更新
/// </summary>
void ResultScene::UpdateEffect()
{

}

/// <summary>
/// 入力更新
/// </summary>
void ResultScene::UpdateKeyState()
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
