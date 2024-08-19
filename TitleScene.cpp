﻿#include "Common.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "CollisionData.h"
#include "Stage.h"
#include "ShutterController.h"
#include "Enemy.h"
#include "SceneCamera.h"
#include "Input.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
    : isKeyOn           (false)
    , isKeyRelease      (false)
    , isPreviousKeyOn   (false)
{
    // リソース管理
    imageDataManager    = ImageDataManager::GetInstance();
    modelDataManager    = ModelDataManager::GetInstance();

    // 当たり判定
    //collisionManager    = CollisionManager::GetInstance();

    // 演出関連
    soundManager        = SoundManager::GetInstance();
    effectManager       = EffectManager::GetInstance();

    // オブジェクト関連
    stage               = new Stage();
    shutterController   = new ShutterController();

    // カメラ
    sceneCamera         = new SceneCamera();

    // UI
    titleSceneUI        = new TitleSceneUI();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    // メモリ開放
    delete(stage);
    delete(sceneCamera);
    delete(titleSceneUI);
    delete(shutterController);
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
    stage->InitializeTitleScene();
    sceneCamera->Initialize(InitializeCameraPosition, InitializeCameraTargetPosition);
    shutterController->InitializeTitleScene();
}

/// <summary>
/// シーンの更新処理
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* TitleScene::UpdateScene()
{
    // キー入力の更新
    UpdateKeyState();

    // オブジェクト更新
    shutterController->Update();        // シャッター
    sceneCamera->UpdateTitleScene();    // カメラ
    titleSceneUI->Update();             // UI

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
    // オブジェクト描画
    stage->Draw();
    shutterController->Draw();

    // UIの描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void TitleScene::DrawUI()
{
    titleSceneUI->Draw();
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
