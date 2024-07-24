#pragma once
#include "Common.h"

/// <summary>
/// 所持弾薬が最大まで補充されるアイテム
/// </summary>
class MaxAmmo
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MaxAmmo();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~MaxAmmo();

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

