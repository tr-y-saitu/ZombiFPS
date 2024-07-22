#pragma once
#include "Common.h"

/// <summary>
/// 銃の基礎クラス
/// </summary>
class GunBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunBase();

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() abstract;

private:
    // 変数
    VECTOR position;        // 座標
};


