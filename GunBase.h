#pragma once
#include "Common.h"
#include "Bullet.h"
#include "Player.h"

class   GunStateBase;
enum    GunState;
class   Bullet;

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
    /// 銃の強化状態
    /// </summary>
    enum class GunPowerUpState : int
    {
        None,               // 強化されていない
        FirstUpGraeded,     // １回目の強化
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
    /// 弾丸情報の初期化
    /// </summary>
    virtual void InitializeBulletData(VECTOR cameraPosition, VECTOR targetPosition) abstract;

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update(VECTOR setPosition, VECTOR cameraVector,VECTOR cameraTargetVector,
        VECTOR cameraPosition, float cameraPitch,Player::State,Player::AimState currentAimState) abstract;

    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() abstract;

    // ゲッター
    const VECTOR GetPosition()const { return position; }
    const int GetFireRate()const { return fireRate; }
    const float GetAccuracy()const { return accuracy; }
    list<Bullet*>& GetActiveBullet() { return activeBullet; }
    const  int GetActiveBulletSize() const { return activeBullet.size(); }
    const Bullet::BulletInitializeData GetBulletInitializeData()const { return bulletData; }
    const int GetGunAmmo()const { return gunAmmo; }
    const int GetGunMaxAmmo()const { return gunMaxAmmo; }
    const int GetRewardMoney()const { return rewardMoney; }
    const int GetBackUpAmmo()const { return backUpAmmo; }
    const int GetBackUpMaxAmmo()const { return backUpMaxAmmo; }
    const bool GetPowerUpWeapon()const { return powerUpWeapon; }
    const GunPowerUpState GetGunPowerUpState()const { return gunPowerUpState; }

    // セッター
    void SetGunAmmo(int set) { gunAmmo = set; }
    void SetBackUpAmmo(int set) { backUpAmmo = set; }
    void SetPowerUpWeapon(bool set) { powerUpWeapon = set; }

protected:

    /// <summary>
    /// 銃の座標更新
    /// </summary>
    /// <param name="setPosition">設定する座標</param>
    /// <param name="cameraForwardVector">カメラの前方向ベクトル</param>
    /// <param name="cameraPitch">設定する上下角度</param>
    void UpdateGunPosition(VECTOR setPosition, VECTOR cameraForwardVector, float cameraPitch,
        Player::State playerState,Player::AimState playerAimState);

    /// <summary>
    /// 移動の更新
    /// </summary>
    /// <param name="setPosition">設定したい座標</param>
    /// <param name="playerState">プレイヤーの状態</param>
    virtual void UpdateMove(VECTOR setPosition, Player::State playerState);

    /// <summary>
    /// 回転の更新
    /// </summary>
    /// <param name="cameraForwardVector">カメラの前ベクトル</param>
    /// <param name="pitch">上下角度</param>
    void UpdateAngle(VECTOR cameraForwardVector, float pitch,
        Player::State playerState,Player::AimState playerAimState);

    /// <summary>
    /// 銃の位置調整
    /// </summary>
    /// <param name="setPosition">設定したい座標</param>
    /// <param name="cameraForwardVector">カメラの前方向ベクトル</param>
    void FixedGunPosition(VECTOR setPosition,VECTOR cameraForwardVector);

    /// <summary>
    /// 走るアニメーションの再生
    /// </summary>
    void PlayRunAnimation();

    /// <summary>
    /// 撃つアニメーションの再生
    /// </summary>
    void PlayShotAnimation(VECTOR cameraForwardVector);

    /// <summary>
    /// リロードアニメーションの再生
    /// </summary>
    void PlayReloadAnimation();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // 腰だめ
    static constexpr float  HipShootHorizontalAngle     = 3.0f * DX_PI_F / 180.0f;      // 水平回転用：腰だめの位置に調整するために回転させるY軸回転度(ラジアン)
    static constexpr float  HipShootVerticalAngle       = 30.0f * DX_PI_F / 180.0f;     // 垂直回転用：腰だめの位置に調整するために回転させる水平方向からの角度(ラジアン)
    static constexpr float  HipShootOffsetScale         = -0.7f;                        // 腰だめのずらし量の拡大率
    // アニメーション
    static constexpr float  RunAnimationAngle           = 15.0f * DX_PI_F / 180.0f;     // 走りアニメーション再生時の銃の修正角度
    static constexpr float  RecoilDistance              = 0.05f;                        // 銃を撃った時の反動の大きさ
    static constexpr float  RecoilDistanceLimit         = 1.0f;                         // 銃を撃った時の反動の大きさの最大値
    static constexpr int    RecoilCycle                 = 5;                            // 反動のサイクル
    // 強化時
    static constexpr int    PowerUpDamage               = 100;                          // 武器強化時の威力増加

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // ステータス
    int             modelHandle;                // モデルハンドル
    VECTOR          position;                   // 座標
    VECTOR          positionOffsetAmount;       // 座標をずらす量
    MATRIX          rotationMatrix;             // モデルの回転行列
    GunState        state;                      // 銃の状態
    GunStateBase*   currentState;               // 現在の銃の更新を行う状態
    int             fireRate;                   // 銃の連射力
    float           recoil;                     // 銃の反動
    float           accuracy;                   // 銃の精度(拡散度合い)
    int             gunAmmo;                    // 銃の総弾数
    int             gunMaxAmmo;                 // 銃の最大総弾数
    int             rewardMoney;                // 獲得した金額
    int             backUpAmmo;                 // 予備弾薬
    int             backUpMaxAmmo;              // 予備弾薬の最大数

    // 強化時
    bool            powerUpWeapon;              // 武器を強化するかどうかのフラグ
    GunPowerUpState gunPowerUpState;            // 武器が強化されているかの状態
    int             powerUpTextureHandle;       // 武器強化時のテクスチャハンドル


    // 弾丸
    Bullet::BulletInitializeData bulletData;    // 弾丸のデータ
    list<Bullet*>   activeBullet;               // 使用中の弾丸
    float           bulletDamagePower;          // 弾丸の威力
    float           bulletPenetrationPower;     // 弾丸の貫通力

    // アニメーション
    int             runAnimationCount;          // 走るアニメーションカウント
    int             shotAnimationCount;         // 撃つアニメーションカウント
    int             reloadAnimationCount;       // リロードアニメーションカウント
};


