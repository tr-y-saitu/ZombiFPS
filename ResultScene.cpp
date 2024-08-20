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

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
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
    sceneCamera->Initialize(VGet(0, 0, 0), VGet(10, 10, 10));
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* ResultScene::UpdateScene()
{
    // 入力処理
    input->Update();

    // オブジェクト更新
    shutterController->Update();
    sceneCamera->UpdateResultScene();

    // UI更新
    resultSceneUI->Update();

    // 演出更新
    UpdateSound();
    UpdateEffect();

    // キーを入力したらシーン切り替え
    if (1)
    {
        return new TitleScene();
    }

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
    DrawUI();       // UIの描画
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
