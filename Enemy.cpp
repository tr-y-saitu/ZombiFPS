#include "Enemy.h"
#include "ModelDataManager.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
    modelDataManager = ModelDataManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
    MV1DeleteModel(modelHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize()
{
    position = InitializePosition;

    // モデルハンドルを取得
    modelHandle = modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ModelDataType::EnemyModelData);

    // モデルサイズを再設定
    MV1SetScale(modelHandle, EnemyScale);

    // 状態を初期化
    state = State::None;

    // ジャンプ力は初期状態では０
    currentJumpPower = 0.0f;

    // 初期状態でプレイヤーが向くべき方向はＸ軸方向
    targetMoveDirection = VGet(1.0f, 0.0f, 0.0f);

    // アニメーションのブレンド率を初期化
    animationBlendRate = 1.0f;

    // 初期状態ではアニメーションはアタッチされていないにする
    currentPlayAnimation = -1;
    previousPlayAnimation = -1;

    // アニメーション設定
    PlayAnimation(AnimationType::Idle);
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
    // 移動

    // 回転制御

    // アニメーション更新
    UpdateAnimation();

    // 座標設定
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw()
{
    MV1DrawModel(modelHandle);
}

/// <summary>
/// ルートフレームのZ軸方向の移動パラメータを無効にする
/// </summary>
void Enemy::DisableRootFrameZMove()
{

}

/// <summary>
/// 移動ベクトルの更新
/// </summary>
/// <param name="upModveVector">上方向ベクトル</param>
/// <param name="leftMoveVector">左方向ベクトル</param>
/// <param name="currentFrameMoveVector">移動ベクトル</param>
void Enemy::UpdateMoveVector(VECTOR& upModveVector,
    VECTOR& leftMoveVector, VECTOR& currentFrameMoveVector)
{

}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="MoveVector">移動ベクトル</param>
/// <param name="stage">ステージ</param>
void Enemy::Move(const VECTOR& MoveVector, Stage& stage)
{

}

/// <summary>
/// 回転制御
/// </summary>
void Enemy::UpdateAngle()
{

}

/// <summary>
/// アニメーションを新しく再生する
/// </summary>
/// <param name="type">アニメーションの種類</param>
void Enemy::PlayAnimation(AnimationType type)
{
    // HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
    // 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
    if (previousPlayAnimation != -1)
    {
        MV1DetachAnim(modelHandle, previousPlayAnimation);
        previousPlayAnimation = -1;
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
/// アニメーション処理
/// </summary>
void Enemy::UpdateAnimation()
{
    float animationTotalTime;       // 再生しているアニメーションの総時間

    // ブレンド率が１以下の場合は１に近づける
    if (animationBlendRate < 1.0f)
    {
        animationBlendRate += AnimationBlendSpeed;
        if (animationBlendRate > 1.0f)
        {
            animationBlendRate = 1.0f;
        }
    }

    // 再生しているアニメーション１の処理
    if (currentPlayAnimation != -1)
    {
        // アニメーションの総時間を取得
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnimation);

        // 再生時間を進める
        currentAnimationCount += PlayAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (currentAnimationCount >= animationTotalTime)
        {
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
        previousAnimationCount += PlayAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (previousAnimationCount > animationTotalTime)
        {
            previousAnimationCount = static_cast<float>(fmod(previousAnimationCount, animationTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(modelHandle, previousPlayAnimation, previousAnimationCount);

        // アニメーション２のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(modelHandle, previousPlayAnimation, 1.0f - animationBlendRate);
    }
}
