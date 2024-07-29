#include "EnemyGroup.h"
#include "Stage.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroup::EnemyGroup()
{
    enemys.push_back(new Enemy());
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
        enemys[i]->Draw();
    }
}
