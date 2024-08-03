#include "PlayerReloadState.h"

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
PlayerReloadState::PlayerReloadState()
{
    // 処理なし
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
/// <param name="previousStateData">前のステートの情報</param>
PlayerReloadState::PlayerReloadState(int& playerModelHandle, AnimationData previousStateData)
    : PlayerStateBase(playerModelHandle,previousStateData)
{
    playAnimationSpeed  = PlayAnimationSpeed;
    animationBlendSpeed = AnimationBlendSpeed;

    // 新しいアニメーションを再生する
    PlayNewAnimation(AnimationStateType::Idle);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerReloadState::~PlayerReloadState()
{
    // 処理なし
}

/// <summary>
/// 更新
/// </summary>
void PlayerReloadState::Update()
{
    // アニメーションの更新
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}

/// <summary>
/// アニメーションデータの更新
/// </summary>
void PlayerReloadState::UpdateAnimationData()
{
    nowStateData.currentAnimationCount  = currentAnimationCount;
    nowStateData.currentPlayAnimation   = currentPlayAnimation;
    nowStateData.previousAnimationCount = previousAnimationCount;
    nowStateData.previousPlayAnimation  = previousPlayAnimation;
}

