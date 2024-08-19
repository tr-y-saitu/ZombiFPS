#pragma once
#include "Common.h"

/// <summary>
/// シーン用のカメラ
/// </summary>
class SceneCamera
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneCamera();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SceneCamera();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="initializePosition">カメラの座標</param>
    /// <param name="initializeTargetPosition">カメラの見ている座標</param>
    void Initialize(VECTOR initializePosition, VECTOR initializeTargetPosition);

    /// <summary>
    /// タイトルシーンでのカメラ更新
    /// </summary>
    void UpdateTitleScene(VECTOR targetPosition);

    /// <summary>
    /// リザルトシーンでのカメラ更新
    /// </summary>
    void UpdateResultScene();

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  CameraNearClip          = 0.1f;     // カメラのニアクリップ
    static constexpr float  CameraFarClip           = 200.0f;   // カメラのファークリップ
    static constexpr float  AngleSpeed              = 0.05f;    // 旋回速度
    static constexpr float  AngleVerticalOffset     = 2.6f;     // 一定角度以上上を向かないようにするためのバフ値
    static constexpr float  AngleVerticalDownOffset = 1.4f;     // 下入力時に一定以上角度が下にならないようにするためのバフ値
    static constexpr float  MouseInputDeadZoneMin   = 0.009f;   // マウスの入力を受け付ける最小値

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    float   angleHorizon;           // 水平角度
    float   angleVertical;          // 垂直角度
    float   cameraPitch;            // 上下の角度量
    VECTOR  targetPosition;         // カメラが見る視点座標
    VECTOR  cameraPosition;         // カメラ自身の座標
    VECTOR  cameraForwardVector;    // カメラの前方向ベクトル

};

