﻿#pragma once
#include "Common.h"
#include "Player.h"

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
    /// <param name="input">入力情報</param>
    /// <param name="setPostion">設定する座標</param>
    /// <param name="stage">ステージ</param>
    void Update(const Input& input, VECTOR setPosition,
        const Stage& stage,Player::AimState playerAimState,bool isShooting);

    /// <summary>
    /// カメラの角度を更新する
    /// </summary>
    /// <param name="input">入力更新情報</param>
    void UpdateCameraAngle(const Input& input);

    /// <summary>
    /// マウスでのカメラの角度更新
    /// </summary>
    /// <param name="input">入力更新情報</param>
    void UpdateCameraAngleMouse(const Input& input,Player::AimState playerAimState);

    /// <summary>
    /// カメラ座標の修正
    /// </summary>
    /// <param name="stage">ステージ</param>
    void FixCameraPosition(const Stage& stage,VECTOR setPosition,Player::AimState playerAimState);

    /// <summary>
    /// カメラの前方向ベクトルを更新する
    /// </summary>
    void UpdateCameraForwardVector();

    /// <summary>
    /// カメラの右方向ベクトルを更新する
    /// </summary>
    void UpdateCameraRightVector();

    /// <summary>
    /// カメラを腰だめの位置に配置する
    /// </summary>
    /// <param name="setPosition">基準となる座標</param>
    void UpdateHipUpPosition(VECTOR setPosition);

    /// <summary>
    /// エイム時の位置に配置する(銃の覗き込み時)
    /// </summary>
    /// <param name="setPosition">基準となる座標</param>
    void UpdateAimPosition(VECTOR setPosition);

    /// <summary>
    /// カメラのピッチ角度を更新する
    /// </summary>
    /// HACK:
    /// ピッチ：上下角度
    /// プレイヤーモデルとプレイヤーカメラの角度は同期しているので、
    /// 上下角度のみこの関数で更新
    void UpdateCameraPitch();

    /// <summary>
    /// 視野角の更新
    /// </summary>
    void UpdateFov(Player::AimState playerAimState);

    /// <summary>
    /// リコイルの更新
    /// </summary>
    /// <param name="isShooting">射撃中かどうか</param>
    /// <param name="playerAimState">プレイヤーのエイム状態</param>
    void UpdateRecoil(bool isShooting,Player::AimState playerAimState);

    // ゲッター
    const VECTOR& GetCameraPosition() const { return cameraPosition; }
    const VECTOR& GetTargetPosition() const { return targetPosition; }
    const VECTOR& GetCameraForwardVector() const { return cameraForwardVector; }
    const VECTOR& GetCameraRightVector()const { return cameraRightVector; }
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
    static constexpr float  AngleSpeedHipShoot          = 0.005f;    // 腰だめ時のカメラ旋回速度
    static constexpr float  AngleSpeedAim               = AngleSpeedHipShoot / 2;   // エイム時のカメラ旋回速度
    static constexpr float  CameraPlayerTargetHeight    = 1.0f;     // プレイヤー座標からどれだけ高い位置を注視点とするか
    static constexpr float  ToPlayerLength              = 4.0f;     // プレイヤーとの距離
    static constexpr float  CollisionSize               = 1.0f;     // カメラの当たり判定サイズ
    static constexpr float  AngleVerticalOffset         = 2.6f;     // 一定角度以上上を向かないようにするためのバフ値
    static constexpr float  AngleVerticalDonwOffset     = 1.4f;     // 下入力時に一定以上角度が下にならないようにするためのバフ値
    static constexpr VECTOR CameraPlayerTargetPosition  = { 0.0f,CameraPlayerTargetHeight,0.0f };    // カメラの注視点の座標
    static constexpr float  MouseInputDeadZoneMin       = 0.0009f;   // マウスの入力を受け付ける最小値
    // 腰だめ
    static constexpr float  LeftOffset                  = -0.5f;    // 腰だめの位置を再現するために左にずらす量
    static constexpr float  BackOffset                  = -2.0f;    // 腰だめの位置を再現するために後ろにずらす量
    static constexpr float  ViewTargetShiftLeftOffset   = -0.5f;    // 腰だめの位置に調整するためのターゲットの視点ずらし量
    // 視野角
    static constexpr float  AimFov                      = 40.0f * DX_PI_F / 180.f;  // エイム時の視野角
    static constexpr float  AimFovScope                 = 10.0f * DX_PI_F / 180.0f; // スコープ使用時の視野角
    static constexpr float  HipShootFov                 = 60.0f * DX_PI_F / 180.f;  // 腰だめ時の視野角
    static constexpr float  FovChangeSpeed              = 2.0f * DX_PI_F / 180.f;   // 視野角の変更スピード
    // MEMO:現在の視野角と、目標の視野角をfloatで表しているが、
    //      目標の視野角に到達した場合の[＝]等号式で表したいが誤差があり無理なので
    //      絶対値を利用してその誤差をどこまで許容するかの値
    static constexpr float  FovMargin                   = 0.01f * DX_PI_F / 180.0f;

    // 反動
    static constexpr float  HipShootRecoil              = 0.005f;                   // 腰だめ時の銃の反動
    static constexpr float  AimShootRecoil              = 0.005f;                   // エイム時の銃の反動

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    float   angleHorizon;           // 水平角度
    float   angleVertical;          // 垂直角度
    float   cameraPitch;            // 上下の角度量
    float   angleSpeed;             // カメラの旋回速度
    VECTOR  targetPosition;         // カメラが見る視点座標
    VECTOR  cameraPosition;         // カメラ自身の座標
    VECTOR  cameraForwardVector;    // カメラの前方向ベクトル
    VECTOR  cameraRightVector;      // カメラの右方向ベクトル（プレイヤーを右に配置するために使用）

    // カメラ視野角
    float   currentFov;             // 現在の視野角
    float   targetFov;              // 目標の視野角
};

