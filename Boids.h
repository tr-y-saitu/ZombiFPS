#pragma once
#include "Common.h"

/// <summary>
/// 集合計算処理クラス
/// </summary>
class Boids
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Boids();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Boids();

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

