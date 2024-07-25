#include "GunBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
GunBase::GunBase()
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
/// 回転の更新
/// </summary>
/// <param name="setPosition">設定する座標</param>
/// <param name="pitch">上下の視点傾度</param>
void GunBase::UpdateAngle(VECTOR setPosition, float pitch)
{
    // 銃モデルをプレイヤーカメラの回転率と同様に回転させる

    // プレイヤー専用カメラの方向を取得
    VECTOR cameraForward = setPosition;
    float cameraPitch = pitch;

    // モデルの水平方向回転値を計算
    float gunAngleY = atan2f(cameraForward.x, cameraForward.z);

    // 腰だめの角度に修正
    gunAngleY -= 3.0f * DX_PI_F / 180.f;
    cameraPitch += 30.0f * DX_PI_F / 180.0f;

    // モデルの回転
    MV1SetRotationXYZ(modelHandle, VGet(-cameraPitch, gunAngleY, 0.0f));
}
