#include "EnemyObjectPools.h"
#include "EnemyGroupController.h"
#include "EnemyGroup.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroupController::EnemyGroupController()
{
    // エネミーのオブジェクトプール
    enemyObjectPools = new EnemyObjectPools();

}

/// <summary>
/// デストラクタ
/// </summary>
EnemyGroupController::~EnemyGroupController()
{
    // メモリ解放
    for (EnemyGroup* enemy : activeEnemyGroup)
    {
        delete(enemy);
    }

    delete(enemyObjectPools);
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
    // 未使用のエネミーをオブジェクトプールから取得
    EnemyGroup* enemy = enemyObjectPools->GetInactiveEnemy();

    // 取得したエネミーがあるなら使用中に追加
    if (enemy != nullptr)
    {
        enemy->Initialize();                    // 初期化
        enemy->SetCollisionDataIsActive(true);  // 当たり判定をアクティブにする
        activeEnemyGroup.push_back(enemy);      // エネミーの追加
    }

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
    for (auto& enemyGroup : activeEnemyGroup)
    {
        enemyGroup->Update(playerPosition, stage);
    }

    // 使い終わったエネミーがいればプールに返却する
    enemyObjectPools->ReturnActiveEnemyInstance(activeEnemyGroup);
}

/// <summary>
/// 描画
/// </summary>
void EnemyGroupController::Draw(VECTOR playerPosition)
{
    // エネミーグループの数だけ更新
    for (auto& enemyGroup : activeEnemyGroup)
    {
        enemyGroup->Draw(playerPosition);
    }

    // エネミーの総数を描画
    DrawFormatString(100, 800, DebugFontColor, "EnemySize:%d", activeEnemyGroup.size());
}
