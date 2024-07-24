#pragma once
#include "Common.h"

/// <summary>
/// 銃の状態基礎クラス
/// </summary>
class GunStateBase
{
public:
    /// <summary>
    /// 銃の状態
    /// </summary>
    enum GunState
    {
        IdleState,      // 何もしていない状態
        RunState,       // 走り状態
        ShotState,      // 発砲状態
        ReloadState,    // リロード状態
    };

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

private:

};

