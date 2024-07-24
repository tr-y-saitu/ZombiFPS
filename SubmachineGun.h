#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;

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
    void Update() override;

private:
    // 変数
    VECTOR position;        // 座標
    vector<Shot*> shot;     // 銃弾
    GunStateBase* gunState; // 銃の状態
};

