﻿#include "Common.h"
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
#include "ShutterController.h"
#include "MaxAmmo.h"
#include "IncomeDouble.h"
#include "GameSceneUI.h"
#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
    // フォントサイズ設定
    SetFontSize(GameSceneFontSize);

    // 乱数を初期化
    srand(unsigned int(time(nullptr)));

    // 入力処理
    input                   = new Input();

    // 演出関連
    effectManager           = EffectManager::GetInstance();
    soundManager            = SoundManager::GetInstance();

    // 当たり判定
    collisionManager        = CollisionManager::GetInstance();

    // オブジェクト関連
    stage                   = new Stage();
    player                  = new Player();
    enemyGroupController    = new EnemyGroupController(player->GetPlayerAddMoney());
    enemyWaveController     = new EnemyWaveController();
    shutterController       = new ShutterController();

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
    delete(enemyGroupController);
    delete(enemyWaveController);
    delete(shutterController);
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
    enemyGroupController->Initialize();
    enemyWaveController->Initialize();
    shutterController->Initialize();
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* GameScene::UpdateScene()
{
    // オブジェクト更新
    input->Update();                                                // 入力処理
    player->Update(*input,*stage);                                  // プレイヤー
    enemyGroupController->Update(player->GetPosition(), *stage,
        enemyWaveController->GetEnemySpawnFlag());                  // エネミーの集合体
    enemyWaveController->Update(enemyGroupController->GetEnemyGroupSize());
    shutterController->Update();                                    // シャッター
    collisionManager->Update();                                     // 当たり判定処理
    effectManager->Update();                                        // エフェクト管理クラス更新
    UpdateSound();                                                  // 音の更新
    gameSceneUI->Update();                                          // UIの更新

    UpdateEffekseer3D();                                            // エフェクト更新

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
    stage->Draw();                      // ステージ
    player->Draw(*stage);               // プレイヤー
    enemyGroupController->Draw(player->GetPosition());       // エネミーの集合体
    enemyWaveController->Draw();        // エネミーウェーブ
    shutterController->Draw();          // シャッター
    DrawEffekseer3D();                  // 3Dエフェクト描画
    DrawUI();                           // UIの描画
}

/// <summary>
/// UIの描画
/// </summary>
void GameScene::DrawUI()
{
    gameSceneUI->Draw(*player,enemyWaveController->GetCurrentWaveState());
}

/// <summary>
/// 音の更新
/// </summary>
void GameScene::UpdateSound()
{
    // インタラクト時のサウンドを再生
    if (player->GetIsInteracted())
    {
        // お金を払った時の音
        soundManager->PlaySoundListSE(SoundManager::MoneyUseSE);

        // シャッターを開けた場合
        if (player->GetInteractLocationState() == Player::InteractLocationState::Shutter)
        {
            soundManager->PlaySoundListSE(SoundManager::ShutterOpenSE);
        }
    }

    // プレイヤーのステートごとの音
    switch (player->GetState())
    {
        case Player::State::Run:
        {
            // 走る音
            soundManager->PlaySoundListSETypeLoop(SoundManager::PlayerRunSE);

            break;
        }
        case Player::State::Walk:
        {
            // それ以外は歩く音
            soundManager->PlaySoundListSETypeLoop(SoundManager::PlayerWalkingSE);

            break;
        }
        default:
        {
            break;
        }
    }

    // 銃の発砲音
    if (player->GetIsShooting())
    {
        soundManager->PlaySoundListSE(SoundManager::SubmachineGunShootingSE);
    }

    // 空撃ち音
    if (input->GetMouseCurrentFrameInput() & MOUSE_INPUT_LEFT && !player->GetEquippedGunAmmo())
    {
        soundManager->PlaySoundListSE(SoundManager::DryFireSE);
    }

    // リロード音
    switch (player->GetReloadState())
    {
        case Player::ReloadState::None:
        {
            // 処理なし
            break;
        }
        case Player::ReloadState::Start:
        {
            // マガジンを抜く音を再生
            soundManager->PlaySoundListSE(SoundManager::GunReloadStartSE);
            break;
        }
        case Player::ReloadState::End:
        {
            // マガジンを挿入する音を再生
            soundManager->PlaySoundListSE(SoundManager::GunReloadEndSE);

            break;
        }
        default:
        {
            break;
        }
    }
}

/// <summary>
/// エフェクトの更新
/// </summary>
void GameScene::UpdateEffect()
{

}
