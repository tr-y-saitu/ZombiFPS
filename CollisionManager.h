#pragma once
#include "Common.h"

/// <summary>
/// 値り判定処理クラス
/// </summary>
class CollisionManager  final
{
public:
    /// <summary>
    /// オブジェクトの種別
    /// </summary>
    enum class ObjectTag : int
    {
        Player,     // プレイヤー
        Enemy,      // エネミー
        Bullet,     // 弾丸
    };

    /// <summary>
    /// 当たり判定用情報
    /// </summary>
    struct CollisionData
    {
        ObjectTag   tag;                    // そのオブジェクトが何なのか(Player,Enemy,Bullet)
        VECTOR      centerPosition;         // 中央座標
        VECTOR      capsuleStartPosition;   // カプセル上の座標
        VECTOR      capsuleEndPosition;     // カプセル下の座標
        float       radius;                 // 当たり判定半径
        VECTOR      lineStartPosition;      // 線の始点
        VECTOR      lineEndPosition;        // 線の終点
        std::function<void(CollisionManager::CollisionData, CollisionManager::ObjectTag)> onHit;    // 当たった後の処理の関数ポインタ
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

    // 当たり判定データの読み込み
    static void CollisionDataRegister(CollisionData data,ObjectTag tag);

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


private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionManager();

    // 管理用
    static CollisionManager* collisionManager;      // コリジョンマネージャーのインスタンス

    // 当たり判定用データ
    map<int, CollisionData> dataList;               // 当たり判定を行うリスト

};

