#include "PlayerWalkState.h"
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerWalkState::PlayerWalkState()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerModelHandle"></param>
/// <param name="previousStateData"></param>
PlayerWalkState::PlayerWalkState(int& playerModelHandle, AnimationData previousStateData)
{
    modelHandle = playerModelHandle;
    playAnimationSpeed = PlayAnimationSpeed;
    animationBlendSpeed = AnimationBlendSpeed;
    animationBlendRate = -1.0f;
    currentPlayAnimation = -1;
    currentAnimationCount = 0;
    previousPlayAnimation = -1;
    previousAnimationCount = 0;

    nowStateData.currentAnimationCount = 0;
    nowStateData.currentPlayAnimation = 0;
    nowStateData.previousAnimationCount = 0;
    nowStateData.previousPlayAnimation = 0;

    // 前のステートの情報を書き込み
    currentAnimationCount   = previousStateData.currentAnimationCount;
    currentPlayAnimation    = previousStateData.currentPlayAnimation;
    previousAnimationCount  = previousStateData.previousAnimationCount;
    previousPlayAnimation   = previousStateData.previousPlayAnimation;

    // 新しいアニメーションを再生する
    PlayNewAnimation(AnimationStateType::Walk);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerWalkState::~PlayerWalkState()
{
}

/// <summary>
/// 更新
/// </summary>
void PlayerWalkState::Update()
{
    // アニメーションの更新
    UpdateAnimation();

    // アニメーションデータの更新
    UpdateAnimationData();
}

/// <summary>
/// アニメーションデータの更新
/// </summary>
void PlayerWalkState::UpdateAnimationData()
{
    nowStateData.currentAnimationCount = currentAnimationCount;
    nowStateData.currentPlayAnimation = currentPlayAnimation;
    nowStateData.previousAnimationCount = previousAnimationCount;
    nowStateData.previousPlayAnimation = previousPlayAnimation;
}

/// <summary>
/// 新しくアニメーションを再生する
/// </summary>
/// <param name="type">再生したいアニメーション番号</param>
void PlayerWalkState::PlayNewAnimation(AnimationStateType type)
{
    // HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
    // 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
    if (previousPlayAnimation != NoAnimationAttached)
    {
        MV1DetachAnim(modelHandle, previousPlayAnimation);
        previousPlayAnimation = NoAnimationAttached;
    }

    // 今まで再生中のモーションだったものの情報をPrevに移動する
    previousPlayAnimation = currentPlayAnimation;
    previousAnimationCount = currentAnimationCount;

    // 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
    currentPlayAnimation = MV1AttachAnim(modelHandle, static_cast<int>(type));
    currentAnimationCount = 0.0f;

    // ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
    animationBlendRate = previousPlayAnimation == -1 ? 1.0f : 0.0f;
}

/// <summary>
/// アニメーションの更新
/// </summary>
void PlayerWalkState::UpdateAnimation()
{
    float animationTotalTime;       // 再生しているアニメーションの総時間

    // ブレンド率が１以下の場合は１に近づける
    if (animationBlendRate < MaxAnimationBlendRate)
    {
        animationBlendRate += animationBlendSpeed;
        if (animationBlendRate > MaxAnimationBlendRate)
        {
            animationBlendRate = MaxAnimationBlendRate;
        }
    }

    // 再生しているアニメーション１の処理
    if (currentPlayAnimation != -1)
    {
        // アニメーションの総時間を取得
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnimation);

        // 再生時間を進める
        currentAnimationCount += playAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (currentAnimationCount >= animationTotalTime)
        {
            // fmod→float版の「 % 」計算
            currentAnimationCount = static_cast<float>(fmod(currentAnimationCount, animationTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(modelHandle, currentPlayAnimation, currentAnimationCount);

        // アニメーション１のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnimation, animationBlendRate);
    }

    // 再生しているアニメーション２の処理
    if (previousPlayAnimation != -1)
    {
        // アニメーションの総時間を取得
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, previousPlayAnimation);

        // 再生時間を進める
        previousAnimationCount += playAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (previousAnimationCount > animationTotalTime)
        {
            // fmod → float版の「 % 」計算
            previousAnimationCount = static_cast<float>(fmod(previousAnimationCount, animationTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(modelHandle, previousPlayAnimation, previousAnimationCount);

        // アニメーション２のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(modelHandle, previousPlayAnimation,
            MaxAnimationBlendRate - animationBlendRate);
    }

}
