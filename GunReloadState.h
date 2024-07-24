#pragma once
#include "GunStateBase.h"


/// <summary>
/// 銃をリロードしている状態
/// </summary>
class GunReloadState : public GunStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunReloadState();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunReloadState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};



