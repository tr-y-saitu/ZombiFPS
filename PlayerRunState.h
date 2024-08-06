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
    /// コンストラクタ
    /// </summary>
    /// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
    /// <param name="previousStateData">前のステートの情報</param>
    PlayerRunState(int playerModelHandle, AnimationData previousStateData);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerRunState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:
    /// <summary>
    /// アニメーションデータの更新
    /// </summary>
    void UpdateAnimationData();

    // アニメーション
    static constexpr float  PlayAnimationSpeed = 0.5f;              // アニメーション速度
    static constexpr float  AnimationBlendSpeed = 0.1f;             // アニメーションのブレンド率変化速度



};



