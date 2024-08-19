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
    /// タイトルシーンでの初期化
    /// </summary>
    void InitializeTitleScene();

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR playerPosition, Stage& stage);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(VECTOR playerPosition);

    /// <summary>
    /// エネミーの線形探索の更新
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    /// <param name="stage">ステージ</param>
    /// <returns>そのエネミーが目指す座標</returns>
    VECTOR UpdateEnemyPathfinding(VECTOR playerPosition, Enemy& enemy,Stage& stage);

    // Getter
    const bool GetIsActive()const { return isActive; }

    // Setter
    void SetCollisionDataIsActive(bool set);

private:
    // 定数

    // 変数
    vector<Enemy*>  enemys;         // エネミー(ゾンビ)
    Boids*          boids;          // 集合計算用
    Pathfinding*    pathfinding;    // 線形探索用
    bool            isActive;       // エネミーが使用中かどうか

    Pathfinding::Room       playerPreviousRoom;     // プレイヤーが以前いた部屋
};

