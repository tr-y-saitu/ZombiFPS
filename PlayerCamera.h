#pragma once
#include "Common.h"

/// <summary>
/// プレイヤー専用のカメラ
/// </summary>
class PlayerCamera
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerCamera();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayerCamera();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

private:
    // 定数
    static constexpr float AngleSpeed = 0.05f;                  // 旋回速度
    static constexpr float CameraPlayerTargetHeight = 400.0f;   // プレイヤー座標からどれだけ高い位置を注視点とするか
    static constexpr float ToPlayerLength = 1600.0f;            // プレイヤーとの距離
    static constexpr float CollisionSize = 50.0f;               // カメラの当たり判定サイズ

    // 変数
    float   angleHorizon;       // 水平角度
    float   angleVertical;      // 垂直角度
    VECTOR  targetPosition;     // カメラが見る視点座標
    VECTOR  cameraPosition;     // カメラ自身の座標
};

