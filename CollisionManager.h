#pragma once
#include "Common.h"


/// <summary>
/// 値り判定処理クラス
/// </summary>
class CollisionManager  final
{
public:
    /// <summary>
    /// 当たり判定用情報
    /// </summary>
    struct CollisionData
    {
        VECTOR centerPosition;  // 中央座標
        VECTOR topPosition;     // カプセル上の座標
        VECTOR bottomPosition;  // カプセル下の座標
        float radius;           // 当たり判定半径
    };

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CollisionManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectPlayManagerのポインタ</returns>
    static CollisionManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// すべての当たり判定処理
    /// </summary>
    void Update();

    /// <summary>
    /// 球と線の当たり判定
    /// </summary>
    bool IsCollisionLineSphere(VECTOR sphereCenter, float radius,
        VECTOR lineStart, VECTOR lineEnd);

    /// <summary>
    /// 球と球との当たり判定
    /// </summary>
    /// <param name="position1">対象１の座標</param>
    /// <param name="radius1">対象１の当たり判定用半径</param>
    /// <param name="position2">対象２の座標</param>
    /// <param name="radius2">対象２の当たり判定用半径</param>
    /// <returns>当たったかどうか</returns>
    bool IsCollisionSphere(VECTOR position1, float radius1,
        VECTOR position2, float radius2);


private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionManager();

    // 管理用
    static CollisionManager* collisionManager;      // コリジョンマネージャーのインスタンス

    // 当たり判定用データ

};

