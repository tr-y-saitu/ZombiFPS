#pragma once
#include "Common.h"


/// <summary>
/// シャッター(障害物のドア)
/// </summary>
class Shutter
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Shutter();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Shutter();

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

