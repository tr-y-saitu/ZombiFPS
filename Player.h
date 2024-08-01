﻿#pragma once
#include "Common.h"
#include "PlayerStateBase.h"

class PlayerStateBase;
class GunBase;
class Input;
class PlayerCamera;
class Stage;
class ModelDataManager;
class BulletObjectPools;
struct AnimationData;

/// <summary>
/// プレイヤー
/// </summary>
class Player
{
public:
    /// <summary>
    /// プレイヤーの状態
    /// </summary>
    enum class State : int
    {
        Idle,           // 何もしていない
        Walk,           // 歩き
        Run,            // 走り
        Jump,           // ジャンプ
        OnHitEnemy,     // エネミーに当たった状態
    };

    /// <summary>
    /// アニメーションタイプ
    /// </summary>
    enum class AnimationType : int
    {
        Idle        = 8,        // 何もしていない
        Walk        = 9,        // 歩き
        Stop        = 10,       // 停止
        Run         = 11,       // 走り
        Jump        = 12,       // ジャンプ
        Shooting    = 13,       // 射撃中
    };

    /// <summary>
    /// 所持している銃の種類
    /// </summary>
    enum  class GunType : int
    {
        AssaultRifle,       // アサルトライフル
        BattleRifle,        // バトルライフル
        SubmachineGun,      // サブマシンガン
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Player();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="input">入力情報</param>
    /// <param name="stage">ステージ</param>
    void Update(const Input& input, Stage& stage);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(const Stage& stage);

    /// <summary>
    /// プレイヤーカメラの更新
    /// </summary>
    /// <param name="input">入力情報</param>
    /// <param name="stage">ステージ</param>
    void UpdatePlayerCamera(const Input& input,Stage& stage);

    /// <summary>
    /// 天井に接触した時の処理
    /// </summary>
    void OnHitRoof();

    /// <summary>
    /// 床に当たった時の処理
    /// </summary>
    void OnHitFloor();

    // ゲッター、セッター
    const VECTOR& GetPosition() const { return position; }
    bool GetCurrentFrameMove() const { return currentFrameMove; }
    bool GetIsShooting()const { return isShooting; }
    State GetState() const { return state; }
    float GetCurrentJumpPower() const { return currentJumpPower; }

private:
    /// <summary>
    /// ルートフレームのZ軸方向の移動パラメータを無効にする
    /// </summary>
    void DisableRootFrameZMove();

    /// <summary>
    /// 移動ベクトルの更新
    /// </summary>
    /// <param name="input">入力情報</param>
    /// <param name="upModveVector">上方向ベクトル</param>
    /// <param name="leftMoveVector">左方向ベクトル</param>
    /// <param name="currentFrameMoveVector">移動ベクトル</param>
    void UpdateMoveVector(const Input& input, VECTOR& upModveVector,
        VECTOR& leftMoveVector, VECTOR& currentFrameMoveVector);

    /// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="MoveVector">移動ベクトル</param>
    /// <param name="stage">ステージ</param>
    void Move(const VECTOR& MoveVector, Stage& stage);

    /// <summary>
    /// 回転制御
    /// </summary>
    void UpdateAngle();

    /// <summary>
    /// アニメーションを新しく再生する
    /// </summary>
    /// <param name="type">アニメーションの種類</param>
    void PlayAnimation(AnimationType type);

    /// <summary>
    /// アニメーション処理
    /// </summary>
    void UpdateAnimation();

    /// <summary>
    /// 銃を撃つ
    /// </summary>
    /// <param name="input">入力情報</param>
    void UpdateShootingEquippedWeapon(const Input& input);

    /// <summary>
    /// 使い終わった弾丸をオブジェクトプールに返す
    /// </summary>
    void DeactivateBulletReturn();

    /// <summary>
    /// 入力に応じたステートの切り替えを行う
    /// </summary>
    /// <param name="input">入力情報</param>
    void TransitionInputState(const Input& input);

    /// <summary>
    /// ステートの切り替え
    /// </summary>
    /// <param name="newState">新しいステート</param>
    void ChangeState(State newState);


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // ステータス
    static constexpr float  MoveSpeed               = 0.5f;                         // 移動速度
    static constexpr float  AngleSpeed              = 0.2f;                         // 角度変化速度
    static constexpr float  JumpPower               = 100.0f;                       // ジャンプ力
    static constexpr float  MoveLimitY              = 4.5f;                         // Y軸の移動制限
    static constexpr VECTOR ZeroVector              = { 0.0f,0.0f,0.0f };           // ゼロベクトル
    static constexpr VECTOR PlayerScale             = { 0.05f,0.05f,0.05f };        // プレイヤーのスケール
    // 重力関係
    static constexpr float  Gravity                 = 3.0f;                         // 重力
    static constexpr float  FallUpPower             = 20.0f;                        // 足を踏み外した時のジャンプ力
    // アニメーション
    static constexpr float  PlayAnimationSpeed      = 0.5f;                         // アニメーション速度
    static constexpr float  AnimationBlendSpeed     = 0.1f;                         // アニメーションのブレンド率変化速度
    // 腰だめ時
    static constexpr float  HipUpPositionAngleY     = 170.0f * DX_PI_F / 180.0f;    // 水平回転用：腰だめの位置に調整するために回転させるY軸回転度(ラジアン)
    static constexpr float  HipUpPositionANglePitch = 20.0f * DX_PI_F / 180.0f;     // 垂直回転用：腰だめの位置に調整するために回転させる水平方向からの角度(ラジアン)
    // デバッグ
    static constexpr int    DebugPositionDrawX      = 100;                          // 座標情報を描画するX位置
    static constexpr int    DebugPositionDrawY      = 0;                            // 座標情報を描画するY位置

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // ロード関係
    ModelDataManager*   modelDataManager;   // モデルデータマネージャー
    
    // 基本情報
    PlayerCamera*       playerCamera;       // プレイヤー専用のカメラ(FPS視点カメラ)
    VECTOR              position;           // 座標
    PlayerStateBase*    currentState;       // 現在のステート
    GunBase*            equippedGun;        // 銃
    BulletObjectPools*  bulletObjectPools;  // 弾丸のオブジェクトプール
    int                 shootFireRateCount; // 銃の連射力をカウント
    bool                isHitEnemyAttack;   // エネミーの攻撃を受けている

    // 移動状態
    VECTOR      targetMoveDirection;        // モデルが向くべき方向のベクトル
    float       currentJumpPower;           // Ｙ軸方向の速度
    int         modelHandle;                // モデルハンドル
    State       state;                      // 状態
    bool        isShooting;                 // 発砲状態か

    // アニメーション関係
    int         currentPlayAnimation;       // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       currentAnimationCount;      // 再生しているアニメーションの再生時間
    int         previousPlayAnimation;      // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       previousAnimationCount;     // 前の再生アニメーションの再生時間
    float       animationBlendRate;         // 現在と過去のアニメーションのブレンド率
    bool        currentFrameMove;           // そのフレームで動いたかどうか
    bool        pressMoveButton;            // 移動用のボタンが入力されているか
    PlayerStateBase::AnimationData animationData;       // アニメーション再生に必要なデータ

};

