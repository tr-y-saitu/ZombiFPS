#include "SceneCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneCamera::SceneCamera()
    : angleHorizon(DX_PI_F)
    , angleVertical(0.0f)
    , cameraPitch(0.0f)
    , targetPosition(VGet(0, 0, 0))
    , cameraPosition(VGet(0, 0, 0))
{
    // 描画範囲の設定
    SetCameraNearFar(0.1f, 600.0f);

    // カメラを設定
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
SceneCamera::~SceneCamera()
{
    // 処理なし
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="initializeTargetPosition">カメラの座標</param>
/// <param name="targetPosition">カメラの見ている座標</param>
void SceneCamera::Initialize(VECTOR initializePosition, VECTOR initializeTargetPosition)
{
    // カメラ設定
    // initializePositionからtargetPositionを見る
    cameraPosition = initializePosition;
    targetPosition = initializeTargetPosition;

    SetCameraPositionAndTarget_UpVecY(initializePosition, targetPosition);
}

/// <summary>
/// 更新
/// </summary>
void SceneCamera::UpdateTitleScene()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    // カメラの更新
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// リザルトシーンでのカメラ更新
/// </summary>
void SceneCamera::UpdateResultScene()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    // カメラの更新
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}
