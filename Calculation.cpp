#include "Calculation.h"


/// <summary>
/// コンストラクタ
/// </summary>
Calculation::Calculation()
{
    // 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Calculation::~Calculation()
{
    // 処理なし
}

/// <summary>
/// ２点間の距離を計算
/// </summary>
/// <param name="position1">点１</param>
/// <param name="position2">点２</param>
/// <returns>２点間の距離</returns>
float Calculation::Distance3D(VECTOR position1, VECTOR position2)
{
    return sqrt((position2.x - position1.x) * (position2.x - position1.x) +
                (position2.y - position1.y) * (position2.y - position1.y) +
                (position2.z - position1.z) * (position2.z - position1.z));
}
