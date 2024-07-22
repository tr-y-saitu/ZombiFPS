#pragma once
#include "Common.h"

/// <summary>
/// 線形探索クラス
/// </summary>
class Pathfinding
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Pathfinding();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Pathfinding();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

private:

};

