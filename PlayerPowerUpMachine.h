#pragma once
#include "Common.h"


/// <summary>
/// プレイヤー強化マシン
/// </summary>
class PlayerPowerUpMachine
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerPowerUpMachine();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayerPowerUpMachine();

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

