#pragma once
#include "GunBase.h"

class GunStateBase;
class Bullet;
class ModelDataManager;
class ImageDataManager;
class BulletObjectPools;
class EffectManager;

/// <summary>
/// サブマシンガン
/// </summary>
class SubmachineGun : public GunBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SubmachineGun();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SubmachineGun();

    /// <summary>
    /// 初期化 
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// 弾丸情報の初期化
    /// </summary>
    void InitializeBulletData(VECTOR cameraPosition, VECTOR targetPosition) override;

    /// <summary>
    /// 銃の更新
    /// </summary>
    /// <param name="setPosition">設定座標</param>
    /// <param name="cameraVector">カメラの前ベクトル</param>
    /// <param name="cameraPitch">カメラの水平からの角度</param>
    void Update(VECTOR setPosition,VECTOR cameraVector, VECTOR cameraTargetVector,
        VECTOR cameraPosition,float cameraPitch, Player::State, Player::AimState currentAimState);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

private:
    /// <summary>
    /// 移動の更新
    /// </summary>
    /// <param name="setPosition">設定したい座標</param>
    /// <param name="playerState">プレイヤーの状態</param>
    void UpdateMove(VECTOR setPosition, Player::State playerState) override;

    /// <summary>
    /// 銃を発砲する
    /// </summary>
    void UpdateShooting(VECTOR cameraPosition,VECTOR targetPosition);

    /// <summary>
    /// 走り時の座標調整
    /// </summary>
    /// <param name="playerState">プレイヤーの状態</param>
    /// <returns>調整された自身のポジション</returns>
    VECTOR FixedRunPosition(Player::State playerState);

    /// <summary>
    /// リロード時の座標調整
    /// </summary>
    /// <param name="playerState">プレイヤーの状態</param>
    /// <returns>調整された自身のポジション</returns>
    VECTOR FixedReloadPosition(Player::State playerState);

    /// <summary>
    /// 武器強化時の初期化
    /// </summary>
    void InitializePowerUpWeapon();

    /// <summary>
    /// 武器強化時のモデルマテリアルの更新
    /// </summary>
    void UpdatePowerUpGunMaterial();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // ステータス
    // 弾丸
    static constexpr float  BulletDamagePower       = 35.0f;        // 弾丸の威力
    static constexpr float  BulletPenetrationPower  = 1.0f;         // 弾丸の貫通力
    static constexpr float  BulletSpeed             = 100.0f;       // 弾丸の速度
    static constexpr VECTOR BulletDirection         = { 0,0,1 };    // 弾丸の移動方向
    // 銃
    static constexpr int    GunMaxAmmo              = 30;           // 銃の総弾数
    static constexpr int    GunFireRate             = 5;            // 銃の連射力(このフレームに１回発射する)
    static constexpr float  GunRecoil               = 1.0f;         // 銃の反動
    static constexpr float  GunAccuracy             = 4.0f;         // 銃の精度(拡散度合い)
    static constexpr VECTOR InitializeScale         = { 0.07f,0.07f,0.07f };    // 初期化時のスケール
    static constexpr int    MaxBackUpAmmo           = 210;          // 銃の最大予備弾薬数
    // 強化時
    static constexpr float  MaximumEmissive         = 0.9f;         // 最大発光量
    static constexpr float  MinimumEmissive         = 0.4f;         // 最小発光量
    static constexpr float  EmissiveSpeed           = 0.005f;       // 発光量の変化スピード
    // ずらし量
    static constexpr VECTOR GunOffset = { 0.0f,0.5f,0.0f };         // 銃のプレイヤーの腕からのずらし量

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    ModelDataManager*       modelDataManager;       // モデルデータ読み込み用クラスのアドレス
    ImageDataManager*       imageDataManager;       // 画像データ読み込み用クラスのアドレス
    EffectManager*          effectManager;          // エフェクト管理クラス
    float                   runAnimationFactor;     // 走りアニメーション再生時の適応率
    float                   reloadAnimationFactor;  // リロードアニメーションの再生時の適応率

    // 強化時
    bool    isEmissiveIncreasing;   // 発光量上昇中であるかどうか
    float     emissiveIntensity;    // 現在の発光量

};

