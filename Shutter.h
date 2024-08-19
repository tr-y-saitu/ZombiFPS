#pragma once
#include "Common.h"
#include "CollisionData.h"
#include "ShutterController.h"

class CollisionManager;
class ShutterController;
enum ShutterTag;

/// <summary>
/// シャッター(障害物のドア)
/// </summary>
class Shutter
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Shutter();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Shutter();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(ShutterController::ShutterInitializeData initializeData);

    /// <summary>
    /// タイトルシーンでの初期化
    /// </summary>
    /// <param name="initializeData"></param>
    void InitializeTitleScene(ShutterController::ShutterInitializeData initializeData);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 当たり判定情報を更新する
    /// </summary>
    void UpdateCollisionData();

    /// <summary>
    /// オブジェクトと接触した時の処理
    /// </summary>
    /// <param name="hitObjectData">接触したオブジェクト</param>
    void OnHit(CollisionData hitObjectData);

private:
    /// <summary>
    /// シャッターを開ける
    /// </summary>
    void UpdateOpen();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  HitBoxRadius            = 1.5f;     // 当たり判定の半径
    static constexpr float  HItBoxInteractRadius    = 10.0f;    // シャッターにアクセスできる当たり判定
    static constexpr float  OpenSpeed               = 0.1f;     // シャッターが開く速度
    static constexpr float  RiseUpperLimit          = 15.0f;     // 上昇上限

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 当たり判定
    CollisionManager*   collisionManager;   // 当たり判定管理クラス
    CollisionData       collisionData;      // 当たり判定用データ

    // 基本情報
    VECTOR      position;           // 座標
    MATRIX      rotationMatrix;     // プレイヤー回転率
    int         modelHandle;        // モデルハンドル
    bool        isOpen;             // 開くかどうか
    int         interactionCost;    // インタラクトするコスト
    ShutterController::ShutterTag  shutterTag;         // シャッターの固有名称
};

