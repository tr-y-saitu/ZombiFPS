#include "EnemyGroup.h"
#include "Stage.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroup::EnemyGroup()
{
    // 線形探索クラス
    pathfinding = new Pathfinding();

    // ゾンビを生成
    enemys.push_back(new Enemy());

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyGroup::~EnemyGroup()
{
    // メモリ解放
    for (int i = 0; i < enemys.size(); i++)
    {
        delete(enemys[i]);
    }

    delete(pathfinding);
}

/// <summary>
/// 初期化
/// </summary>
void EnemyGroup::Initialize()
{
    // エネミーの数だけ初期化
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Initialize();
    }
}

/// <summary>
/// 更新
/// </summary>
void EnemyGroup::Update(VECTOR targetPosition, Stage& stage)
{
    // エネミーの数だけ更新
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Update(targetPosition,stage);
    }
}

/// <summary>
/// 描画
/// </summary>
void EnemyGroup::Draw()
{
    // エネミーの数だけ描画
    for (int i = 0; i < enemys.size(); i++)
    {
        //enemys[i]->Draw();
    }

    // 線形探索用に区切った部屋を描画
    pathfinding->Draw();

}
