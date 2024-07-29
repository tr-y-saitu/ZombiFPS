#include "EnemyGroup.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroup::EnemyGroup()
{
    enemys.push_back(new Enemy());
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

}

/// <summary>
/// 更新
/// </summary>
void EnemyGroup::Update()
{

}
