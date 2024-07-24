#pragma once
#include "Common.h"

class PlayerStateBase;
class Gun;
class Input;
class PlayerCamera;
class Stage;
class ModelDataManager;

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
        None,   // 何もしていない
        Walk,   // 歩き
        Run,    // 走り
        Jump,   // ジャンプ
    };

    /// <summary>
    /// アニメーションタイプ
    /// </summary>
    enum class AnimationType : int
    {
        None = 8,   // 何もしていない
        Wolk = 8,   // 歩き
        Stop = 8,   // 停止
        Run,        // 走り
        Jump,       // ジャンプ
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


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  PlayAnimationSpeed   = 0.5f;     // アニメーション速度
    static constexpr float  MoveSpeed       = 0.5f;     // 移動速度
    static constexpr float  AnimationBlendSpeed  = 0.1f;     // アニメーションのブレンド率変化速度
    static constexpr float  AngleSpeed      = 0.2f;     // 角度変化速度
    static constexpr float  JumpPower       = 100.0f;   // ジャンプ力
    static constexpr float  Gravity         = 3.0f;     // 重力
    static constexpr float  ShadowSize      = 200.0f;   // 影の大きさ
    static constexpr float  ShadowHeight    = 700.0f;   // 影が落ちる高さ
    static constexpr float  FallUpPower     = 20.0f;    // 足を踏み外した時のジャンプ力
    static constexpr float  MoveLimitY      = 5.0f;     // Y軸の移動制限
    static constexpr VECTOR PlayerScale     = { 0.05f,0.05f,0.05f };    // プレイヤーのスケール
    static constexpr VECTOR ZeroVector      = { 0.0f,0.0f,0.0f };       // ゼロベクトル

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // ロード関係
    ModelDataManager*   modelDataManager; // モデルデータマネージャー
    
    // 基本情報
    PlayerCamera*       playerCamera;       // プレイヤー専用のカメラ(FPS視点カメラ)
    VECTOR              position;           // 座標
    PlayerStateBase*    playerState;        // プレイヤーの状態
    Gun*                gun;                // 銃

    // 移動状態
    VECTOR      targetMoveDirection;        // モデルが向くべき方向のベクトル
    float       currentJumpPower;           // Ｙ軸方向の速度
    int         modelHandle;                // モデルハンドル
    State       state;                      // 状態

    // アニメーション関係
    int         currentPlayAnimation;       // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       currentAnimationCount;      // 再生しているアニメーションの再生時間
    int         previousPlayAnimation;      // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       previousAnimationCount;     // 前の再生アニメーションの再生時間
    float       animationBlendRate;         // 現在と過去のアニメーションのブレンド率
    bool        currentFrameMove;           // そのフレームで動いたかどうか
    bool        pressMoveButton;            // 移動用のボタンが入力されているか


};

