#pragma once
#include "Common.h"

class Input;
class Player;
class Stage;

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
    /// <param name="input">入力処理</param>
    /// <param name="player">プレイヤー</param>
    /// <param name="stage">ステージ</param>
    void Update(const Input& input, const Player& player, const Stage& stage);

    /// <summary>
    /// カメラの角度を更新する
    /// </summary>
    /// <param name="input"></param>
    void UpdateCameraAngle(const Input& input);

    /// <summary>
    /// カメラ座標の修正
    /// </summary>
    /// <param name="stage">ステージ</param>
    void FixCameraPosition(const Stage& stage);

    // ゲッター
    const VECTOR& GetCameraPosition() const { return cameraPosition; }
    const VECTOR& GetTargetPosition() const { return targetPosition; }

private:
    // 定数
    static constexpr float CameraNearClip = 0.1f;               // カメラのニアクリップ
    static constexpr float CameraFarClip = 5000.0f;             // カメラのファークリップ
    static constexpr float AngleSpeed = 0.05f;                  // 旋回速度
    static constexpr float CameraPlayerTargetHeight = 5.0f;     // プレイヤー座標からどれだけ高い位置を注視点とするか
    static constexpr float ToPlayerLength = 10.0f;              // プレイヤーとの距離
    static constexpr float CollisionSize = 1.0f;                // カメラの当たり判定サイズ
    static constexpr VECTOR CameraPlayerTargetPosition = { 10.0f,CameraPlayerTargetHeight,0.0f };    // カメラの注視点の座標
    static constexpr float AngleVerticalOffset = 2.6f;          // 一定角度以上上を向かないようにするためのバフ値

    // 変数
    float   angleHorizon;       // 水平角度
    float   angleVertical;      // 垂直角度
    VECTOR  targetPosition;     // カメラが見る視点座標
    VECTOR  cameraPosition;     // カメラ自身の座標
};

