#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;

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
    /// 更新
    /// </summary>
    void Update() override;

private:
    VECTOR position;        // 座標
    vector<Shot*> shot;     // 銃弾
    GunStateBase* gunState; // 銃の状態
};



