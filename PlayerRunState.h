#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// プレイヤーが入ってる状態
/// </summary>
class PlayerRunState : public PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerRunState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerRunState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:
};



