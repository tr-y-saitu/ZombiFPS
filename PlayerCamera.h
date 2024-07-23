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
    /// <param name="input">入力更新情報</param>
    /// <param name="player">プレイヤー</param>
    /// <param name="stage">ステージ</param>
    void Update(const Input& input, const Player& player, const Stage& stage);

    /// <summary>
    /// カメラの角度を更新する
    /// </summary>
    /// <param name="input">入力更新情報</param>
    void UpdateCameraAngle(const Input& input);

    /// <summary>
    /// マウスでのカメラの角度更新
    /// </summary>
    /// <param name="input">入力更新情報</param>
    void UpdateCameraAngleMouse(const Input& input);

    /// <summary>
    /// カメラ座標の修正
    /// </summary>
    /// <param name="stage">ステージ</param>
    void FixCameraPosition(const Stage& stage);

    /// <summary>
    /// カメラの前方向ベクトルを更新する
    /// </summary>
    void UpdateCameraForwardVector();

    /// <summary>
    /// カメラのピッチ角度を更新する
    /// </summary>
    /// HACK:
    /// ピッチ：上下角度
    /// プレイヤーモデルとプレイヤーカメラの角度は同期しているので、
    /// 上下角度のみこの関数で更新
    void UpdateCameraPitch();

    // ゲッター
    const VECTOR& GetCameraPosition() const { return cameraPosition; }
    const VECTOR& GetTargetPosition() const { return targetPosition; }
    const VECTOR& GetCameraForwardVector() const { return cameraForwardVector; }
    const float GetAngleHorizon() const { return angleHorizon; }
    const float GetAngleVertical() const { return angleVertical; }
    const float GetCameraPitch() const { return cameraPitch; }

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  CameraNearClip              = 0.1f;     // カメラのニアクリップ
    static constexpr float  CameraFarClip               = 200.0f;   // カメラのファークリップ
    static constexpr float  AngleSpeed                  = 0.05f;    // 旋回速度
    static constexpr float  CameraPlayerTargetHeight    = 1.0f;     // プレイヤー座標からどれだけ高い位置を注視点とするか
    static constexpr float  ToPlayerLength              = 3.0f;     // プレイヤーとの距離
    static constexpr float  CollisionSize               = 1.0f;     // カメラの当たり判定サイズ
    static constexpr float  AngleVerticalOffset         = 2.6f;     // 一定角度以上上を向かないようにするためのバフ値
    static constexpr float  AngleVerticalDonwOffset     = 1.4f;     // 下入力時に一定以上角度が下にならないようにするためのバフ値
    static constexpr VECTOR CameraPlayerTargetPosition  = { 0.0f,CameraPlayerTargetHeight,0.0f };    // カメラの注視点の座標


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

