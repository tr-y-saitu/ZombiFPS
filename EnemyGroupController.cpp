#include "EnemyGroupController.h"
#include "EnemyGroup.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroupController::EnemyGroupController()
{
    // メモリ確保
    for (int i = 0; i < TestEnmeyGroupNumber; i++)
    {
        enemyGroup.push_back(new EnemyGroup());
    }
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyGroupController::~EnemyGroupController()
{
    // メモリ解放
    for (int i = 0; i < enemyGroup.size(); i++)
    {
        delete(enemyGroup[i]);
    }
}

/// <summary>
/// 初期化
/// </summary>
void EnemyGroupController::Initialize()
{
    // エネミーグループの数だけ初期化
    for (int i = 0; i < enemyGroup.size(); i++)
    {
        enemyGroup[i]->Initialize();
    }
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPosition">プレイヤー座標</param>
/// <param name="stage">ステージ</param>
void EnemyGroupController::Update(VECTOR playerPosition, Stage& stage)
{
    // エネミーグループの数だけ更新
    for (int i = 0; i < enemyGroup.size(); i++)
    {
        enemyGroup[i]->Update(playerPosition, stage);
    }
}

/// <summary>
/// 描画
/// </summary>
void EnemyGroupController::Draw(VECTOR playerPosition)
{
    // エネミーの数だけ描画
    for (int i = 0; i < enemyGroup.size(); i++)
    {
        enemyGroup[i]->Draw(playerPosition);
    }
}
