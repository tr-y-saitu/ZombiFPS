#pragma once
#include "Boids.h"
#include "Enemy.h"
#include "Pathfinding.h"


class Boids;
class Enemy;
class Pathfinding;

/// <summary>
/// エネミーの集合体
/// </summary>
class EnemyGroup
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyGroup();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyGroup();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

private:
    // 定数

    // 変数
    vector<Enemy>   enemys;         // エネミー(ゾンビ)
    Boids           boids;          // 集合計算用
    Pathfinding     Pathfinding;    // 線形探索用

};

