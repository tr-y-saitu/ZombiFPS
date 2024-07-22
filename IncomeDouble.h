#pragma once
#include "Common.h"

/// <summary>
/// 取得金額が2倍になるアイテム
/// </summary>
class IncomeDouble
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    IncomeDouble();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~IncomeDouble();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    VECTOR position;            // 座標
};

