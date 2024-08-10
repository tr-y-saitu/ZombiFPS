#include "EnemyGroupController.h"
#include "EnemyGroup.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroupController::EnemyGroupController()
{
    // メモリ確保
    for (int i = 0; i < TestEnemyGroupNumber; i++)
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
/// エネミーを作成する
/// </summary>
void EnemyGroupController::CreateEnemy()
{
    // 新しいエネミーグループを作成
    EnemyGroup* newEnemyGroup = new EnemyGroup();

    // 初期化
    newEnemyGroup->Initialize();

    // リストに追加
    enemyGroup.push_back(newEnemyGroup);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPosition">プレイヤー座標</param>
/// <param name="stage">ステージ</param>
void EnemyGroupController::Update(VECTOR playerPosition, Stage& stage, bool enemySpawnFlag)
{
    // エネミー作成指示が出れば作成
    if (enemySpawnFlag)
    {
        CreateEnemy();
    }

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

    // エネミーの総数を描画
    DrawFormatString(100, 800, DebugFontColor, "EnemySize:%d", enemyGroup.size());
}
