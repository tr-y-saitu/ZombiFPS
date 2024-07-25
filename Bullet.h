#pragma once
#include "Common.h"

/// <summary>
/// 銃弾
/// </summary>
class Bullet
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bullet();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Bullet();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    VECTOR  position;           // 座標
    VECTOR  direction;          // 移動方向
    int     power;              // 威力
    float   speed;              // 速度
    int     penetratingPower;   // 貫通力
};



