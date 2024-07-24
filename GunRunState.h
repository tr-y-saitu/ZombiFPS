#pragma once
#include "GunStateBase.h"

/// <summary>
/// 銃を持って走っている状態
/// </summary>
class GunRunState : public GunStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunRunState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunRunState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};


