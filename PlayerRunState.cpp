#include "PlayerRunState.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerRunState::PlayerRunState()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
/// <param name="previousStateData">前のステートの情報</param>
PlayerRunState::PlayerRunState(int playerModelHandle, AnimationData previousStateData)
    : PlayerStateBase(playerModelHandle, previousStateData)
{
    playAnimationSpeed  = DefaultAnimationSpeed;
    animationBlendSpeed = AnimationBlendSpeed;

    // 新しいアニメーションを再生する
    PlayNewAnimation(AnimationStateType::Idle);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRunState::~PlayerRunState()
{
}

/// <summary>
/// 更新
/// </summary>
void PlayerRunState::Update()
{
    // プレイヤーの座標修正
    UpdateOffsetValue();

    // アニメーションの更新
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}

/// <summary>
/// 走りステートのプレイヤーオフセット量の更新
/// </summary>
void PlayerRunState::UpdateOffsetValue()
{
    // アニメーションの適用率を上昇
    // 上昇させることで腕を下げる
    animationFactor += RunAnimationSpeed;
    if (animationFactor > 1.0f)
    {
        animationFactor = 1.0f;
    }

    // 走りステートのずらし量を決める
    stateOffsetValue = VScale(RunAnimationOffsetValue, animationFactor);
}
