#pragma once
#include "Common.h"
#include "CollisionData.h"

class CollisionManager;

/// <summary>
/// 銃の強化マシン
/// </summary>
class GunPowerUpMachine
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GunPowerUpMachine();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GunPowerUpMachine();

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
    /// <summary>
    /// オブジェクトと接触した時の処理
    /// </summary>
    /// <param name="hitObjectData">接触したオブジェクトの情報</param>
    void OnHit(CollisionData hitObjectData);

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr VECTOR InitializePosition          = { -46.0f,4.5f,62.0f };    // 初期座標
    static constexpr float  CollisionRadius             = 2;                        // 当たり判定半径
    static constexpr float  CollisionInteractRadius     = 10;                       // インタラクトできる半径
    static constexpr VECTOR CollisionInitializePosition = InitializePosition;       // 当たり判定座標
    static constexpr float  InteractCost                = 5000;                     // インタラクトできる費用

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    CollisionManager*   collisionManager;       // 当たり判定管理クラス

    // ステータス
    CollisionData       collisionData;          // 当たり判定用情報
    VECTOR              position;               // 座標
};

