#pragma once
#include "Common.h"


/// <summary>
/// 値り判定処理クラス
/// </summary>
class CollisionManager
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

};

