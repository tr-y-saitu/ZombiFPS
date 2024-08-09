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
    // プレイヤーの座標修正
    UpdateOffsetValue();

    // アニメーションの再生
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}

