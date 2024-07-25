#pragma once
#include "Common.h"

/// <summary>
/// 銃の状態基礎クラス
/// </summary>
class GunStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunStateBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunStateBase();

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() abstract;

protected:

};

