﻿#pragma once
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
    /// コンストラクタ
    /// </summary>
    /// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
    /// <param name="previousStateData">前のステートの情報</param>
    PlayerWalkState(int playerModelHandle, AnimationData previousStateData);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerWalkState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

    // アニメーション
    static constexpr float  PlayAnimationSpeed  = 0.5f;     // アニメーション速度
    static constexpr float  AnimationBlendSpeed = 0.1f;     // アニメーションのブレンド率変化速度

};

