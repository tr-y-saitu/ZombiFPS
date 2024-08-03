#include "PlayerShotState.h"

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
PlayerShotState::PlayerShotState()
{
    // 処理なし
}

PlayerShotState::PlayerShotState(int& playerModelHandle, AnimationData previousStateData)
    : PlayerStateBase(playerModelHandle,previousStateData)
{
    playAnimationSpeed = PlayAnimationSpeed;
    animationBlendSpeed = AnimationBlendSpeed;

    // 新しいアニメーションを再生する
    PlayNewAnimation(AnimationStateType::Idle);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerShotState::~PlayerShotState()
{
    // 処理なし
}

/// <summary>
/// 更新
/// </summary>
void PlayerShotState::Update()
{
    // アニメーションの再生
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}

/// <summary>
/// アニメーションデータの更新
/// </summary>
void PlayerShotState::UpdateAnimationData()
{
    nowStateData.currentAnimationCount = currentAnimationCount;
    nowStateData.currentPlayAnimation = currentPlayAnimation;
    nowStateData.previousAnimationCount = previousAnimationCount;
    nowStateData.previousPlayAnimation = previousPlayAnimation;
}
