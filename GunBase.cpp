#include "GunBase.h"\\\//////////////////////////////////////////////////////////////////////////////////\

/// <summary>
/// コンストラクタ
/// </summary>
GunBase::GunBase()
    : runAnimationCount     (0)
    , rotationMatrix        (MGetIdent())
{
}

/// <summary>
/// デストラクタ
/// </summary>
GunBase::~GunBase()
{
    // モデルの削除
    MV1DeleteModel(modelHandle);
}

/// <summary>
/// 移動の更新
/// </summary>
/// <param name="setPosition">設定したい座標</param>
/// <param name="playerState">プレイヤーの状態</param>
void GunBase::UpdateMove(VECTOR setPosition, Player::State playerState)
{

}

/// <summary>
/// 回転の更新
/// </summary>
/// <param name="cameraForwardVector">カメラの前ベクトル</param>
/// <param name="pitch">上下角度</param>
void GunBase::UpdateAngle(VECTOR cameraForwardVector, float pitch,Player::State playerState)
{
    // 銃モデルをプレイヤーカメラの回転率と同様に回転させる
    // プレイヤー専用カメラの方向を取得
    VECTOR cameraForward = cameraForwardVector;
    float cameraPitch = pitch;

    // モデルの水平方向回転値を計算
    float gunAngleY = atan2f(cameraForward.x, cameraForward.z);

    // 腰だめの角度に修正
    gunAngleY -= HipUpPositionAngleY;           // 水平方向回転度
    cameraPitch += HipUpPositionANglePitch;     // 垂直方向回転度

    // 回転行列に変更
    MATRIX rotationX = MGetRotX(-cameraPitch);
    MATRIX rotationY = MGetRotY(gunAngleY);
    MATRIX rotationZ = MGetRotZ(0.0f);

    // 回転行列を合成
    rotationMatrix = MMult(rotationX, rotationY);

    // 走るアニメーションを再生
    if (playerState == Player::State::Run)
    {
        // アニメーションカウントを進める
        runAnimationCount++;

        // 回転角度を設定
        // sin関数で[1]～[-1]を出してもらう
        // (アニメーションカウントを再生周期で割ることで現在どのくらい進んでいるかが分かる)
        float animationProgress = sin(DX_TWO_PI_F * runAnimationCount / Player::RunAnimationFrameCycle);
        // 最大アングル * [１～ -１] = 角度
        // sinを使うことでマイナスの条件式を省く
        float angle = Player::RunAnimationLimitAngle * animationProgress;

        // 回転行列を取得
        MATRIX runMatrixY = MGetRotY(angle);
        MATRIX runMatrixX = MGetRotX(0.2f);
        MATRIX runFinalMatrix = MMult(runMatrixX, runMatrixY);

        // 回転行列を合成
        rotationMatrix = MMult(runFinalMatrix, rotationMatrix);
    }

    // モデルに回転行列を適用
    MV1SetRotationMatrix(modelHandle, rotationMatrix);
}

/// <summary>
/// 銃の位置調整
/// </summary>
/// <param name="cameraForwardVector"></param>
void GunBase::FixedGunPosition(VECTOR setPosition, VECTOR cameraForwardVector)
{
    VECTOR horizonDirection = VGet(cameraForwardVector.x, 0.0f, cameraForwardVector.z);

    VECTOR velocity = VNorm(horizonDirection);

    VECTOR offset = VScale(velocity, -0.7f);
    position = VAdd(position, offset);

    MV1SetPosition(modelHandle, position);
}
