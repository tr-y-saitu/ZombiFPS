#pragma once
#include "GunStateBase.h"

/// <summary>
/// 銃が何もしていない状態
/// </summary>
class GunIdleState : public GunStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunIdleState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunIdleState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};

