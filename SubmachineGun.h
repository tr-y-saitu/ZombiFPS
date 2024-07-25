#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;
class ModelDataManager;

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
    /// 更新
    /// </summary>
    void Update(VECTOR setPosition,VECTOR cameraVector,float cameraPitch);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

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
    static constexpr VECTOR InitializeScale         = { 0.07f,0.07f,0.07f };   // 初期化時のスケール
    // ずらし量
    static constexpr VECTOR GunOffset = { 0.0f,0.5f,0.0f };   // 銃のプレイヤーの腕からのずらし量


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    ModelDataManager*       modelDataManager;       // モデルデータ読み込み用クラスのアドレス

};

