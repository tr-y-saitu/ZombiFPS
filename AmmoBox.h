#pragma once
#include "Common.h"
#include "CollisionData.h"

class ModelDataManager;
class CollisionManager;

/// <summary>
/// 弾薬補充箱
/// </summary>
class AmmoBox
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AmmoBox();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AmmoBox();

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

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr VECTOR InitializePosition = { 2,1.3f,6 };         // 初期座標

private:
    /// <summary>
    /// オブジェクトと接触した時の処理
    /// </summary>
    /// <param name="hitObjectData">接触したオブジェクトの情報</param>
    void OnHit(CollisionData hitObjectData);


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr VECTOR InitializeScale             = { 0.3f,0.3f,0.3f };   // 初期スケール
    static constexpr float  CollisionRadius             = 1;                    // 当たり判定半径
    static constexpr float  CollisionInteractRadius     = 10;                   // インタラクトできる判定半径
    static constexpr VECTOR CollisionInitializePosition = { 2.0f,4.5f,6.0f };   // 当たり判定の初期座標
    static constexpr float  InteractCost                = 500;                  // 弾薬を補充するための費用

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ModelDataManager*   modelDataManager;   // モデルデータ管理クラス
    CollisionManager*   collisionManager;   // 当たり判定管理クラス

    // ステータス
    CollisionData       collisionData;      // 当たり判定用情報
    VECTOR              position;           // 座標
    int                 modelHandle;        // モデルハンドル
};


