#pragma once
#include "Boids.h"
#include "Enemy.h"
#include "Pathfinding.h"


class Boids;
class Enemy;
class Pathfinding;
class Stage;

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
    /// <param name="targetPosition">進べき座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR targetPosition, Stage& stage);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    // 定数

    // 変数
    vector<Enemy*>  enemys;         // エネミー(ゾンビ)
    Boids*          boids;          // 集合計算用
    Pathfinding*    pathfinding;    // 線形探索用

};

