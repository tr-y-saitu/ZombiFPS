#pragma once
#include "Common.h"
#include "CollisionData.h"

class CollisionManager;

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
        VECTOR lineStartPosition;   // 線の始まり
        VECTOR lineEndPosiion;      // 線の終わり
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

    /// <summary>
    /// 当たり判定に必要なデータを更新する
    /// </summary>
    void UpdataCollisionData();

    // ゲッター、セッター
    const bool GetIsActive()const { return isActive; }

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // デバッグ処理
    static constexpr float  HitBoxRadius            = 0.05f;                // デバッグ時の当たり判定を描画するための半径
    static constexpr float  PolygonDetail           = 8.0f;                 // 描画するポリゴンの数
    const int               DebugPolygonColorRed    = GetColor(255, 0, 0);  // デバッグ時の当たり判定ポリゴンの色

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理
    CollisionManager*   collisionManager;   // 当たり判定管理

    // ステータス
    CollisionData       collisionData;      // 当たり判定情報
    VECTOR              position;           // 座標
    VECTOR              direction;          // 移動方向
    VECTOR              lineStartPosition;  // 線の始まり
    VECTOR              lineEndPosition;    // 線の終わり
    int                 power;              // 威力
    float               speed;              // 速度
    int                 penetratingPower;   // 貫通力
    bool                isActive;           // 使用中かどうか
};



