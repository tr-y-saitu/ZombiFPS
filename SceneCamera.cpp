#include "SceneCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneCamera::SceneCamera()
    : angle         (0)
{
    // 描画範囲の設定
    SetCameraNearFar(0.1f, 600.0f);

    // カメラのポジション
    position = VGet(0,0,0);

    // カメラを設定
    SetCameraPositionAndTarget_UpVecY(position, VGet(-7, 5, 20));
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
/// <param name="initializePosition">カメラの座標</param>
/// <param name="targetPosition">カメラの見ている座標</param>
void SceneCamera::Initialize(VECTOR initializePosition, VECTOR targetPosition)
{
    // カメラ設定
    // initializePositionからtargetPositionを見る
    SetCameraPositionAndTarget_UpVecY(initializePosition, targetPosition);
}

/// <summary>
/// 更新
/// </summary>
void SceneCamera::Update()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();
}