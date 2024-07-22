#pragma once


#include "Common.h"
#include "Enemy.h"

class Enemy;

/// <summary>
/// エネミーのオブジェクトプール
/// </summary>
class EnemyObjectPools
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyObjectPools();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyObjectPools();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

private:
    // 定数
    static constexpr int EnemyTotalNum = 100;   // エネミーの総合数

    // 変数
    Enemy   activeEnemy[EnemyTotalNum];         // 使用中エネミー
    Enemy   nonActiveEenmy[EnemyTotalNum];      // 使用していないエネミー


};

