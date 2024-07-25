﻿#pragma once
#include "Common.h"

class   GunStateBase;
enum    GunState;

/// <summary>
/// 銃の基礎クラス
/// </summary>
class GunBase
{
public:
    /// <summary>
    /// 銃の状態
    /// </summary>
    enum class GunState : int
    {
        IdleState,      // 何もしていない状態
        RunState,       // 走り状態
        ShotState,      // 発砲状態
        ReloadState,    // リロード状態
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GunBase();

    /// <summary>
    /// 初期化
    /// </summary>
    virtual void Initialize() abstract;

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update(VECTOR setPosition, VECTOR cameraVector, float cameraPitch) abstract;

    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() abstract;

    /// <summary>
    /// 回転の更新
    /// </summary>
    /// <param name="setPosition">設定する座標</param>
    void UpdateAngle(VECTOR setPosition,float pitch);

protected:
    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 腰だめ
    static constexpr float  HipUpPositionAngleY     = 3.0f * DX_PI_F / 180.0f;      // 水平回転用：腰だめの位置に調整するために回転させるY軸回転度(ラジアン)
    static constexpr float  HipUpPositionANglePitch = 30.0f * DX_PI_F / 180.0f;     // 垂直回転用：腰だめの位置に調整するために回転させる水平方向からの角度(ラジアン)

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    int             modelHandle;            // モデルハンドル
    VECTOR          position;               // 座標
    GunState        state;                  // 銃の状態
    GunStateBase*   currentState;           // 現在の銃の更新を行う状態
    float           shotDamagePower;        // 弾丸の威力
    float           shotPenetrationPower;   // 弾丸の貫通力
    float           fireRate;               // 銃の連射力
    float           recoil;                 // 銃の反動
    float           accuracy;               // 銃の精度(拡散度合い)
};


