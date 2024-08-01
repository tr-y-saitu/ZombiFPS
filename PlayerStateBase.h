#pragma once
#include "Common.h"

/// <summary>
/// プレイヤーステート基礎クラス
/// </summary>
class PlayerStateBase
{
public:
    /// <summary>
    /// アニメーションタイプ
    /// </summary>
    enum class AnimationStateType : int
    {
        Idle = 8,    // 何もしていない
        Walk = 9,    // 歩き
        Stop = 8,    // 停止
        Run = 8,    // 走り
        Jump = 8,    // ジャンプ
        Shooting,       // 射撃中
    };

    /// <summary>
    /// アニメーション変更時に受け渡す用のデータ
    /// </summary>
    struct AnimationData
    {
        int         currentPlayAnimation;       // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
        float       currentAnimationCount;      // 再生しているアニメーションの再生時間
        int         previousPlayAnimation;      // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
        float       previousAnimationCount;     // 前の再生アニメーションの再生時間
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerStateBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerStateBase();

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() abstract;

    // Getter
    const AnimationData GetStateAnimationData()const { return nowStateData; }

protected:
    /// <summary>
    /// 新しくアニメーションを再生する
    /// </summary>
    /// <param name="type">再生したいアニメーション番号</param>
    virtual void PlayNewAnimation(AnimationStateType type);

    /// <summary>
    /// アニメーション更新処理
    /// </summary>
    virtual void UpdateAnimation();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  MaxAnimationBlendRate   = 1.0f;     // アニメーションのブレンド率の最大値
    static constexpr int    NoAnimationAttached     = -1;       // アニメーションアタッチがされていない

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//

    // アニメーション関係
    int             modelHandle;                // モデルハンドル
    int             currentPlayAnimation;       // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float           currentAnimationCount;      // 再生しているアニメーションの再生時間
    int             previousPlayAnimation;      // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float           previousAnimationCount;     // 前の再生アニメーションの再生時間
    float           animationBlendRate;         // 現在と過去のアニメーションのブレンド率
    bool            currentFrameMove;           // そのフレームで動いたかどうか
    bool            pressMoveButton;            // 移動用のボタンが入力されているか
    float           animationBlendSpeed;        // アニメーションのブレンド速度
    float           playAnimationSpeed;         // アニメーション再生速度
    AnimationData   nowStateData;               // 次のステートへ渡す情報
};

