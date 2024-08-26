#pragma once
#include "Common.h"


/// <summary>
/// 影設定クラス
/// </summary>
class ShadowMap
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShadowMap();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShadowMap();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    void Update();
private:

    int shadowMapHandle;    // シャドウマップのハンドル
};


