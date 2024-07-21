#pragma once
#include "Common.h"

/// <summary>
/// 銃の強化マシン
/// </summary>
class GunPowerUpMachine
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunPowerUpMachine();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GunPowerUpMachine();

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
    VECTOR position;        // 座標
};

