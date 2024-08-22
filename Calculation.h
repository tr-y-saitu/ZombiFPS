#pragma once
#include "Common.h"

/// <summary>
/// 計算クラス
/// </summary>
class Calculation
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Calculation();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Calculation();

    /// <summary>
    /// ２点間の距離を計算
    /// </summary>
    /// <param name="position1">点１</param>
    /// <param name="position2">点２</param>
    /// <returns>２点間の距離</returns>
    static float Distance3D(VECTOR position1, VECTOR position2);

private:

};


