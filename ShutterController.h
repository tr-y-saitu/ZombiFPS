#pragma once
#include "Common.h"
#include "CollisionData.h"

class Shutter;
class CollisionManager;
class ModelDataManager;

/// <summary>
/// シャッター管理クラス
/// </summary>
class ShutterController
{
public:
    /// <summary>
    /// シャッターの固有名称
    /// </summary>
    enum ShutterTag
    {
        Shutter1,
        Shutter2,
        Shutter3,
        Shutter4
    };

    /// <summary>
    /// シャッターの初期化情報
    /// </summary>
    struct ShutterInitializeData
    {
        ShutterTag  tag;                        // シャッターの固有名称
        VECTOR      initializePosition;         // 初期化座標
        MATRIX      initializeRotationMatrix;   // 初期化回転率
        VECTOR      initializeScale;            // 初期化拡大率
        int         modelHandle;                // モデルハンドル
        int         interactionCost;            // そのオブジェクトのインタラクトにかかるコスト
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShutterController();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShutterController();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// シャッターの作成
    /// </summary>
    void CreateShutter();

    /// <summary>
    /// シャッターの初期化用データの作成
    /// </summary>
    void CreateInitializeData();

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
    static constexpr int ShutterNumber = 3;     // シャッターの数


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    ModelDataManager*               modelDataManager;           // モデルデータマネージャー
    CollisionManager*               collisionManager;           // 当たり判定管理クラス
    vector<Shutter*>                shutterList;                // シャッターリスト
    ShutterInitializeData  shutterInitializeDataList[ShutterNumber];  // シャッターの初期化用データ
};


