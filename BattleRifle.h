#pragma once
#include "GunBase.h"

class GunStateBase;
class Bullet;
class ModelDataManager;

/// <summary>
/// バトルライフル(単発式の高火力ライフル)
/// </summary>
class BattleRifle : public GunBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BattleRifle();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BattleRifle();

    /// <summary>
    /// 初期化 
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// 更新
    /// </summary>
    void Update(VECTOR setPosition, VECTOR cameraVector, float cameraPitch) override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // ステータス
    static constexpr float  ShotDamagePower         = 1.0f;     // 弾丸の威力
    static constexpr float  ShotPenetrationPower    = 1.0f;     // 弾丸の貫通力
    static constexpr float  GunFireRate             = 1.0f;     // 銃の連射力
    static constexpr float  GunRecoil               = 1.0f;     // 銃の反動
    static constexpr float  GunAccuracy             = 1.0f;     // 銃の精度(拡散度合い)
    static constexpr VECTOR InitializeScale = { 0.1f,0.1f,0.1f };   // 初期化時のスケール
    // ずらし量
    static constexpr VECTOR GunOffset = { 0.0f,0.1f,0.0f };   // 銃のプレイヤーの腕からのずらし量

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    ModelDataManager* modelDataManager;       // モデルデータ読み込み用クラスのアドレス

};



