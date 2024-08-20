#pragma once
#include "Common.h"
#include "CollisionData.h"

/// <summary>
/// 値り判定処理クラス
/// </summary>
class CollisionManager  final
{
public:
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
    /// 当たり判定データの読み込み
    /// </summary>
    /// <param name="data"></param>
    static void RegisterCollisionData(CollisionData* data);

    /// <summary>
    /// 当たり判定データをすべて削除する
    /// </summary>
    static void ClearAllCollisionDataList();

    /// <summary>
    /// すべての当たり判定処理
    /// </summary>
    void Update();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionManager();

    /// <summary>
    /// 球と線の当たり判定
    /// </summary>
    bool IsCollisionLineSphere(VECTOR sphereCenter, float radius,
        VECTOR lineStart, VECTOR lineEnd);

    /// <summary>
    /// カプセルと線分の当たり判定
    /// </summary>
    /// <param name="capsuleTopPosition">カプセルを形成する開始座標</param>
    /// <param name="capuseleBottomPosition">カプセルを形成する終了座標</param>
    /// <param name="capuseleRadius">カプセルの半径</param>
    /// <param name="lineStartPosition">線の始まり</param>
    /// <param name="lineEndPosition">線の終わり</param>
    /// <returns>当たったかどうか</returns>
    bool IsCollisionCapsuleLine(VECTOR capsuleStartPosition, VECTOR capuseleEndPosition, float capuseleRadius,
        VECTOR lineStartPosition, VECTOR lineEndPosition);

    /// <summary>
    /// 球とカプセルの当たり判定
    /// </summary>
    /// <param name="sphereCenter"></param>
    /// <param name="sphereRadius"></param>
    /// <param name="capsuleStart"></param>
    /// <param name="capsuleEnd"></param>
    /// <param name="capuleRadius"></param>
    /// <returns></returns>
    bool IsCollisionSphereCapsule(VECTOR sphereCenter, float sphereRadius,
        VECTOR capsuleStart, VECTOR capsuleEnd, float capuleRadius);

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

    /// <summary>
    /// カプセルとカプセルの当たり判定
    /// </summary>
    /// <param name="capsule1Start"></param>
    /// <param name="capsule1End"></param>
    /// <param name="capsule1Radius"></param>
    /// <param name="capsule2Start"></param>
    /// <param name="capsule2End"></param>
    /// <param name="capsule2Radius"></param>
    /// <returns></returns>
    bool IsCollisionCapsuleCapsule(VECTOR capsule1Start, VECTOR capsule1End, float capsule1Radius,
        VECTOR capsule2Start, VECTOR capsule2End, float capsule2Radius);

    // 管理用
    static CollisionManager*        collisionManager;           // コリジョンマネージャーのインスタンス

    // 当たり判定用データ
    vector<SphereCollisionData*>    sphereCollisionData;        // 球型の当たり判定を行うリスト
    vector<CapsuleCollisionData*>   capsuleCollisionData;       // カプセル型の当たり判定を行うリスト
    vector<LineCollisionData*>      lineCollisionData;          // 線分の当たり判定を行うリスト

    static vector<CollisionData*>   collisionDataList;          // 当たり判定情報リスト
};

