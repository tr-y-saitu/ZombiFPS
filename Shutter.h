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
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 当たり判定
    CollisionData       collisionData;      // 当たり判定用データ

    // 基本情報
    VECTOR      position;           // 座標
    MATRIX      rotationMatrix;     // プレイヤー回転率
    int         modelHandle;        // モデルハンドル
    ShutterController::ShutterTag  shutterTag;         // シャッターの固有名称
};

