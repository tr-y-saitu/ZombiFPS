#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// プレイヤーが発砲している状態
/// </summary>
class PlayerShotState : public PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerShotState();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="playerModelHandle">プレイヤーのモデルハンドル</param>
    /// <param name="previousStateData">前のステートの情報</param>
    PlayerShotState(int& playerModelHandle, AnimationData previousStateData);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerShotState();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

private:

    // アニメーション
    static constexpr float  DefaultAnimationSpeed = 1.0f;      // アニメーション速度
    static constexpr float  AnimationBlendSpeed = 0.1f;     // アニメーションのブレンド率変化速度

};


