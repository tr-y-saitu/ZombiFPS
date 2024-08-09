﻿#include "PlayerIdleState.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdleState::PlayerIdleState()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
/// <param name="previousStateData">前のステートの情報</param>
PlayerIdleState::PlayerIdleState(int playerModelHandle, AnimationData previousStateData)
    : PlayerStateBase(playerModelHandle, previousStateData)
{
    playAnimationSpeed  = PlayAnimationSpeed;
    animationBlendSpeed = AnimationBlendSpeed;

    // 新しいアニメーションを再生する
    PlayNewAnimation(AnimationStateType::Idle);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerIdleState::~PlayerIdleState()
{
}

/// <summary>
/// 更新
/// </summary>
void PlayerIdleState::Update()
{
    // プレイヤーの座標修正
    UpdateOffsetValue();

    // アニメーションの更新
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}


