#include "Enemy.h"
#include "ModelDataManager.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
    : position      (VGet(0,0,0))
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

}

/// <summary>
/// アニメーション処理
/// </summary>
void Enemy::UpdateAnimation()
{

}
