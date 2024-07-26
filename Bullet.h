#pragma once
#include "Common.h"

/// <summary>
/// 銃弾
/// </summary>
class Bullet
{
public:
    /// <summary>
    /// 弾丸の初期化用データ
    /// </summary>
    struct BulletInitializeData
    {
        VECTOR  position;           // 座標
        VECTOR  direction;          // 移動方向
        int     power;              // 威力
        float   speed;              // 速度
        int     penetratingPower;   // 貫通力
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bullet();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Bullet();

    /// <summary>
    /// 弾丸情報の初期化
    /// </summary>
    /// <param name="initializeData">初期化する弾丸のデータ</param>
    void Initialize(BulletInitializeData initializeData);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    const bool GetIsActive()const { return isActive; }

private:
    VECTOR  position;           // 座標
    VECTOR  direction;          // 移動方向
    int     power;              // 威力
    float   speed;              // 速度
    int     penetratingPower;   // 貫通力
    bool    isActive;           // 使用中かどうか
};



