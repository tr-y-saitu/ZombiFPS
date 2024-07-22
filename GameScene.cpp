#include "Common.h"
#include "Input.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EnemyGroupController.h"
#include "EnemyWaveController.h"
#include "EnemyObjectPools.h"
#include "MaxAmmo.h"
#include "IncomeDouble.h"
#include "GameSceneUI.h"
#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
    // 入力処理
    input                   = new Input();

    // データ関連
    

    // 演出関連
    effectManager = EffectManager::GetInstance();
    soundManager = SoundManager::GetInstance();

    // 当たり判定
    collisionManager        = CollisionManager::GetInstance();

    // オブジェクト関連
    stage                   = new Stage();
    player                  = new Player();
    playerCamera            = new PlayerCamera();
    enemyGroupController    = new EnemyGroupController();
    enemyWaveController     = new EnemyWaveController();
    enemyObjectPools        = new EnemyObjectPools();

    // アイテム関連
    maxAmmoItem             = new MaxAmmo();
    incomeDoubleItem        = new IncomeDouble();

    // UI関連
    gameSceneUI             = new GameSceneUI();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
    delete(stage);
    delete(player);
    delete(playerCamera);
    delete(enemyGroupController);
    delete(enemyWaveController);
    delete(enemyObjectPools);
    delete(maxAmmoItem);
    delete(incomeDoubleItem);
    delete(gameSceneUI);
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize()
{
    stage->Initialize();
    player->Initialize();
    playerCamera->Initialize();
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* GameScene::UpdateScene()
{
    // テスト描画
    DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene", true);

    // オブジェクト更新
    input->Update();                                    // 入力処理
    player->Update(*input,*playerCamera,*stage);        // プレイヤー
    playerCamera->Update(*input, *player,*stage);       // プレイヤーカメラの更新
    gameSceneUI->Update();                              // UIの更新

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
    stage->Draw();          // ステージ
    player->Draw(*stage);   // プレイヤー
    DrawUI();               // UIの描画
}

/// <summary>
/// UIの描画
/// </summary>
void GameScene::DrawUI()
{
    gameSceneUI->Draw();
}

/// <summary>
/// 音の更新
/// </summary>
void GameScene::UpdateSound()
{

}

/// <summary>
/// エフェクトの更新
/// </summary>
void GameScene::UpdateEffect()
{

}