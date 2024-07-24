#pragma once
#include "GunStateBase.h"

/// <summary>
/// 銃を撃っている状態
/// </summary>
class GunShotState : public GunStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunShotState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunShotState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};

