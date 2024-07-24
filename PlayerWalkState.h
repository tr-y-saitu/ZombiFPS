#pragma once
#include "PlayerStateBase.h"


/// <summary>
/// プレイヤーが歩いている状態
/// </summary>
class PlayerWalkState : public PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerWalkState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerWalkState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};

