#include "PlayerCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerCamera::PlayerCamera()
    : angleHorizon          (DX_PI_F)
    , angleVertical         (0.0f)
    , targetPosition        (VGet(0,0,0))
    , cameraPosition        (VGet(0,0,0))
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerCamera::~PlayerCamera()
{
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

}