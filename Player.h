#pragma once
#include "Common.h"

class PlayerStateBase;
class Gun;
class Input;
class PlayerCamera;

/// <summary>
/// プレイヤー
/// </summary>
class Player
{
public:
    enum State
    {
        None,   // 何もしていない
        Run,    // 走り
        Jump,   // ジャンプ
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
    void Update(Input& input,PlayerCamera& palyerCamera);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 天井に接触した時の処理
    /// </summary>
    void OnHitRoof();
    
    /// <summary>
    /// 床に当たった時の処理
    /// </summary>
    void OnHitFloor();
    
    /// <summary>
    /// 落下が確定した時の処理
    /// </summary>
    void OnFall();


    // ゲッター、セッター
    const VECTOR& GetPosition() const { return position; }
    bool GetIsMove() const { return isMove; }
    State GetState() const { return state; }
    float GetJumpPower() const { return currentJumpPower; }

private:
    // 定数
    static constexpr float	PlayAnimSpeed = 250.0f; // アニメーション速度
    static constexpr float	MoveSpeed = 30.0f;      // 移動速度
    static constexpr float	AnimBlendSpeed = 0.1f;  // アニメーションのブレンド率変化速度
    static constexpr float	AngleSpeed = 0.2f;      // 角度変化速度
    static constexpr float	JumpPower = 100.0f;     // ジャンプ力
    static constexpr float	Gravity = 3.0f;         // 重力
    static constexpr float	ShadowSize = 200.0f;    // 影の大きさ
    static constexpr float	ShadowHeight = 700.0f;  // 影が落ちる高さ


    // 変数
    VECTOR              position;       // 座標
    PlayerStateBase*    playerState;    // プレイヤーの状態
    Gun*                gun;            // 銃
    // 移動状態
    VECTOR              targetMoveDirection;    // モデルが向くべき方向のベクトル
    float               angle;                  // モデルが向いている方向の角度
    float               currentJumpPower;       // Ｙ軸方向の速度
    int                 modelHandle;            // モデルハンドル
    int                 shadowHandle;           // 影画像ハンドル
    State               state;                  // 状態
    // アニメーション関係
    int         currentPlayAnim;        // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       currentAnimCount;       // 再生しているアニメーションの再生時間
    int         prevPlayAnim;           // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       prevAnimCount;          // 前の再生アニメーションの再生時間
    float       animBlendRate;          // 現在と過去のアニメーションのブレンド率
    bool        isMove;                 // そのフレームで動いたかどうか

    // ルートフレームのＺ軸方向の移動パラメータを無効にする
    void DisableRootFrameZMove();

    // パッド入力によって移動パラメータを設定する
    bool UpdateMoveParameterWithPad(const Input& input, const PlayerCamera& camera, VECTOR& UpMoveVec, VECTOR& LeftMoveVec, VECTOR& MoveVec);

    // 移動処理
    //void Move(const VECTOR& MoveVector, Stage& stage);

    void UpdateAngle();                                 // 回転制御
    //void PlayAnim(AnimKind PlayAnim);                 // 新たなアニメーションを再生する
    void UpdateAnimation();                             // アニメーション処理
    //void DrawShadow(const Stage& stage);              // 影を描画


};

