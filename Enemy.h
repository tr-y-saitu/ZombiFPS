#pragma once
#include "Common.h"
#include "CollisionData.h"
#include "Pathfinding.h"


class ModelDataManager;
class Stage;
class CollisionManager;
class SoundManager;
class EffectManager;
class HitObjectAddress;

/// <summary>
/// エネミー(ゾンビ)
/// </summary>
class Enemy : public HitObjectAddress
{
public:
    /// <summary>
    /// エネミーの状態
    /// </summary>
    enum class State : int
    {
        Idle,       // 停止
        Walk,       // 歩き
        Run,        // 走り
        Attack,     // 攻撃
        Death,      // 死亡
    };

    /// <summary>
    /// エネミーのアニメーションタイプ
    /// </summary>
    /// TODO:
    /// 不要なアニメーションデータの削除方法が分からないのでそのまま実装
    enum class AnimationType : int
    {
        CrawlingBiteAttack1,    // はいずり噛みつき攻撃(1,2は同じ)
        CrawlingBiteAttack2,    // はいずり噛みつき攻撃(1,2は同じ)
        Intimidation,           // 威嚇
        Crawling,               // はいずり移動
        RecoilDeath,            // のけぞり死亡
        NoAnimation1,           // アニメーションなし
        Attack,                 // 攻撃
        BiteAttack,             // 噛みつき攻撃
        Death,                  // 死亡
        Idle,                   // 何もしていない
        NoAnimation2,           // 走り
        Walk,                   // 歩き
        Run,                    // 走り
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Enemy();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// タイトルシーンでの初期化
    /// </summary>
    void InitializeTitleScene();

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="targetPosition">目標座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR targetPosition, Stage& stage, ObjectTag targetTag);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 当たり判定に必要なデータの更新
    /// </summary>
    void UpdateCollisionData();

    /// <summary>
    /// 攻撃の当たり判定に必要なデータの更新
    /// </summary>
    void UpdateAttackCollisionData();

    // Getter
    const VECTOR GetPosition()const { return position; }
    const Pathfinding::Room GetPreviousRoom()const { return previousRoom; }
    const Pathfinding::Room GetCurrentRoom()const { return currentRoom; }
    const bool GetIsTouchingRoomCenter()const { return isTouchingRoomCenter; }
    const Pathfinding::RoomEntryState GetRoomEntryState() const { return roomEntryState; }
    const bool GetIsActive()const { return isActive; }

    // Setter
    void SetPreviousRoom(Pathfinding::Room set) { previousRoom = set; }
    void SetCurrentRoom(Pathfinding::Room set) { currentRoom = set; }
    void SetTargetNextPosition(VECTOR set) { targetNextPosition = set; }
    void SetIsTouchingRoomCenter(bool set) { isTouchingRoomCenter = set; }
    void SetRoomEntryState(Pathfinding::RoomEntryState set) { roomEntryState = set; }
    void SetCollisionDataIsActive(bool set) { collisionData.isCollisionActive = set; }

private:
    /// <summary>
    /// ルートフレームのZ軸方向の移動パラメータを無効にする
    /// </summary>
    void DisableRootFrameZMove();

    /// <summary>
    /// 移動ベクトルの更新
    /// </summary>
    /// <param name="targetPosition">向かうべき座標</param>
    void UpdateMoveVector(VECTOR targetPosition);

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
    /// 弾丸と接触した時の処理
    /// </summary>
    /// <param name="bulletData">弾丸のデータ</param>
    void OnHitBullet(LineCollisionData bulletData);

    /// <summary>
    /// 自分と違うキャラクターと接触した時の処理(Player or Enemy)
    /// </summary>
    /// <param name="capsuleData">キャラクターのデータ</param>
    void OnHitCharacter(CapsuleCollisionData capsuleData);

    /// <summary>
    /// オブジェクトと接触した時の処理
    /// </summary>
    /// <param name="hitObjectData">オブジェクトのデータ</param>
    void OnHit(CollisionData hitObjectData);

    /// <summary>
    /// 攻撃がオブジェクトと接触した時の処理
    /// </summary>
    /// <param name="hitObjectData"></param>
    void OnHitAttack(CollisionData hitObjectData);

    /// <summary>
    /// 死んだかどうかチェックし、死んだ後の更新
    /// </summary>
    void UpdateDead();

    /// <summary>
    /// 攻撃の更新
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    void UpdateAttack(VECTOR targetPosition, ObjectTag targetTag);

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // ステータス
    static constexpr float  MoveSpeed               = 0.2f;                             // 移動速度
    static constexpr float  AngleSpeed              = 0.2f;                             // 角度変化速度
    static constexpr float  JumpPower               = 100.0f;                           // ジャンプ力
    static constexpr float  MoveLimitY              = 1.0f;                             // Y軸の移動制限
    static constexpr VECTOR InitializePosition      = { -48.0f,  MoveLimitY, -35.0f };  // 初期化座標
    static constexpr VECTOR ZeroVector              = { 0.0f,0.0f,0.0f };               // ゼロベクトル
    static constexpr VECTOR EnemyScale              = { 0.03f,0.03f,0.03f };            // プレイヤーのスケール
    static constexpr int    InitializeHitPoints     = 100;                              // 初期化時の体力
    static constexpr VECTOR InitializeDirection     = { 1.0f, 0.0f, 0.0f };             // 初期化時の移動方向
    static constexpr int    DeathInactiveFrame      = 150;                              // 死亡してからモデルを削除するまでのフレームカウント数
    static constexpr float  AttackRange             = 4.0f;                             // この範囲に入ったら攻撃を開始する
    // 当たり判定
    static constexpr float  CollisionRadius         = 1.0f;                             // 当たり判定用半径
    static constexpr VECTOR CapsulePositionOffset   = { 0.0f,4.0f,0.0f };               // カプセルの始点を作るためのずらし量
    static constexpr float  PolygonDetail           = 8.0f;                             // 描画するポリゴンの数
    // 攻撃
    static constexpr float  AttackCollisionRadius   = 2.0f;                             // 攻撃の球型の当たり判定半径
    static constexpr float  AttackPower             = 10.0f;                            // 攻撃力
    // 重力関係
    static constexpr float  Gravity                 = 3.0f;                             // 重力
    static constexpr float  FallUpPower             = 20.0f;                            // 足を踏み外した時のジャンプ力
    // アニメーション
    static constexpr float  PlayAnimationSpeed      = 0.5f;                             // アニメーション速度
    static constexpr float  AnimationBlendSpeed     = 0.1f;                             // アニメーションのブレンド率変化速度
    // エフェクト
    static constexpr VECTOR BloodEffectOffset       = { 0.0f, 4.5f, 0.0f };             // 血しぶきエフェクトのずらし量
    // デバッグ
    static constexpr int    DebugHitPointDrawX      = 0;                                // デバッグ時のHP表示X座標
    static constexpr int    DebugHitPointDrawY      = 100;                              // デバッグ時のHP表示Y座標

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ModelDataManager*   modelDataManager;
    CollisionManager*   collisionManager;
    SoundManager*       soundManager;
    EffectManager*      effectManager;

    // ステータス
    VECTOR      position;                   // 座標
    VECTOR      targetMoveDirection;        // モデルが向くべき方向のベクトル
    float       angle;                      // モデルが向いている方向の角度
    float       currentJumpPower;           // Ｙ軸方向の速度
    int         modelHandle;                // モデルハンドル
    int         shadowHandle;               // 影画像ハンドル
    bool        currentFrameMove;           // そのフレームで動いたかどうか
    State       currentState;               // 状態
    int         hitPoints;                  // 体力
    bool        isActive;                   // 使用中かどうか
    int         deathFrameCount;            // 死亡してから何フレーム経過するか

    // 線形探索用
    Pathfinding::Room   previousRoom;               // 以前いた部屋
    Pathfinding::Room   currentRoom;                // 現在いる部屋
    VECTOR              targetNextPosition;         // 線形探索を行った結果、次に移動したい座標
    bool                isTouchingRoomCenter;       // 今いる部屋の中心座標に接触したか
    Pathfinding::RoomEntryState roomEntryState;     // 部屋に対して何を行っている状態か

    // 当たり判定用
    CollisionData           collisionData;          // 当たり判定用情報
    CollisionData           attackCollisionData;    // 攻撃時の当たり判定情報


    // アニメーション情報
    int         currentPlayAnimation;       // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       currentAnimationCount;      // 再生しているアニメーションの再生時間
    int         previousPlayAnimation;      // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       previousAnimationCount;     // 前の再生アニメーションの再生時間
    float       animationBlendRate;         // 現在と過去のアニメーションのブレンド率

};

