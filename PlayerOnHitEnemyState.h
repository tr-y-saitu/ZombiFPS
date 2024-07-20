#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// プレイヤーがエネミーの攻撃を受けた状態
/// </summary>
class PlayerOnHitEnemyState : public PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerOnHitEnemyState();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerOnHitEnemyState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

};


