#pragma once
#include "PlayerStateBase.h"


/// <summary>
/// プレイヤーが何もしていない状態
/// </summary>
class PlayerIdleState : public PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerIdleState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerIdleState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};

