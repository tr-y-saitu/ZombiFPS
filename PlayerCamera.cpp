#include "PlayerCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerCamera::PlayerCamera()
    : angleHorizon          (DX_PI_F)
    , angleVertical         (0.0f)
    , targetPosition        (VGet(-100,5,-5))
    , cameraPosition        (VGet(10,5,5))
{
    // 描画範囲の設定
    SetCameraNearFar(0.1f, 600.0f);

    // カメラを設定
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerCamera::~PlayerCamera()
{
    // 処理なし
}

/// <summary>
/// 初期化
/// </summary>
void PlayerCamera::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void PlayerCamera::Update()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    

}