#pragma once
#include "Common.h"

class EnemyGroup;

/// <summary>
/// 集合したエネミーを一つにまとめる
/// </summary>
class EnemyGroupController
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyGroupController();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyGroupController();

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
};


