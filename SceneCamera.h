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
    /// <param name="targetPosition">カメラの見ている座標</param>
    void Initialize(VECTOR initializePosition, VECTOR targetPosition);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

private:

    // 変数
    VECTOR  position;           // ポジション
    float   angle;              // 角度

};

