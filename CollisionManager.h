#pragma once
#include "Common.h"


/// <summary>
/// 値り判定処理クラス
/// </summary>
class CollisionManager  final
{
public:
    /// <summary>
    /// 球形当たり判定用構造体
    /// </summary>
    struct SphureCollider
    {
        VECTOR  position;   // 自身の座標
        float   radius;     // 自身球型当たり判定の半径
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

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionManager();

    // 管理用
    static CollisionManager* collisionManager;      // コリジョンマネージャーのインスタンス

    // 当たり判定用データ

};

