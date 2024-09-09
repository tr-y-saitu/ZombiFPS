#include "Common.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "CollisionData.h"
#include "Stage.h"
#include "ShutterController.h"
#include "EnemyGroup.h"
#include "SceneCamera.h"
#include "Input.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"
#include "Input.h"
#include "TutorialScene.h"

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

    // 入力関連
    input               = new Input();

    // オブジェクト関連
    stage               = new Stage();
    shutterController   = new ShutterController();
    enemy               = new EnemyGroup();

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
    delete(enemy);
    delete(input);
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
    // オブジェクトの初期化関数を呼ぶ
    stage->InitializeTitleScene();
    sceneCamera->Initialize(InitializeCameraPosition, InitializeCameraTargetPosition);
    shutterController->InitializeTitleScene();
    enemy->InitializeTitleScene();

    // 初期化
    enemyTargetPosition = Pathfinding::East4RoomCenterPosition;
}

/// <summary>
/// シーンの更新処理
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* TitleScene::UpdateScene()
{
    // キー入力の更新
    UpdateKeyState();
    input->Update();

    // オブジェクト更新
    shutterController->Update();                            // シャッター
    sceneCamera->UpdateTitleScene(enemy->GetPosition());    // カメラ
    enemy->Update(enemyTargetPosition,*stage);              // エネミー
    UpdateEnemy();                                          // エネミーの更新
    UpdateSound();                                          // サウンド
    titleSceneUI->Update();                                 // UI

    // スペースキーが入力されたらシーン推移
    if (isKeyRelease)
    {
        // キーは離れていません
        isKeyRelease = false;

        // チュートリアルシーンに推移
        return new TutorialScene();
    }

    // 現状のシーン
    return this;
}

/// <summary>
/// 音の更新
/// </summary>
void TitleScene::UpdateSound()
{
    // タイトルシーンのBGMを再生
    soundManager->PlaySoundListSETypeLoop(SoundManager::TitleSceneBGM);
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
    // オブジェクト描画
    stage->Draw();
    enemy->Draw(enemyTargetPosition);
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
        if (!CheckHitKey(KEY_INPUT_SPACE))
        {
            isKeyOn = false;          // キーが入力されていない
            isKeyRelease = true;      // キーが離れた
        }
    }
    else if (!isPreviousKeyOn && CheckHitKey(KEY_INPUT_SPACE))
    {
        // キーは長押しされていない && 前フレームで入力なし && キーが押された
        isKeyRelease = false;   // キーは離れていない
        isKeyOn = true;         // キーが押された
    }

    // キー入力されたら
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        isPreviousKeyOn = true;   // このフレームではキーが押された
    }
    else
    {
        isPreviousKeyOn = false;  // このフレームでキーは押されなかった
    }
}

/// <summary>
/// エネミーの更新
/// </summary>
void TitleScene::UpdateEnemy()
{
    // エネミーがEast4とWest4を行き来するように処理

    // East4にたどり着いたら
    if (enemy->GetCurrentRoom().roomNumber == Pathfinding::RoomNumber::East4)
    {
        enemyTargetPosition = Pathfinding::West4RoomCenterPosition;
    }

    // West4にたどり着いたら
    if (enemy->GetCurrentRoom().roomNumber == Pathfinding::RoomNumber::West4)
    {
        enemyTargetPosition = Pathfinding::East4RoomCenterPosition;
    }
}

