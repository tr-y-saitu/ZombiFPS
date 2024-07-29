#include "CollisionManager.h"

// 初期化
CollisionManager* CollisionManager::collisionManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// インスタンスの作成
/// </summary>
void CollisionManager::CreateInstance()
{
    if (collisionManager == NULL)
    {
        collisionManager = new CollisionManager();
    }
}

/// <summary>
/// コリジョンマネージャのインスタンスのポインタを渡す
/// </summary>
/// <returns></returns>
CollisionManager* CollisionManager::GetInstance()
{
    return collisionManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void CollisionManager::DeleteInstance()
{
    delete(collisionManager);
}

/// <summary>
/// 初期化
/// </summary>
void CollisionManager::Initialize()
{
    
}

/// <summary>
/// すべての当たり判定処理
/// </summary>
void CollisionManager::Update()
{

}

// 線と球との当たり判定
bool CollisionManager::IsCollisionLineSphere(VECTOR sphereCenter, float radius,
    VECTOR lineStart, VECTOR lineEnd)
{
    return 1;
}

/// <summary>
/// 球と球との当たり判定
/// </summary>
/// <param name="position1">対象１の座標</param>
/// <param name="radius1">対象１の当たり判定用半径</param>
/// <param name="position2">対象２の座標</param>
/// <param name="radius2">対象２の当たり判定用半径</param>
/// <returns>当たったかどうか</returns>
bool CollisionManager::IsCollisionSphere(VECTOR position1, float radius1,
    VECTOR position2, float radius2)
{
    // 球の中心点からの距離を計算
    VECTOR diff = VSub(position1, position2);
    float distance = VDot(diff, diff);                  // 2乗

    // 両方の半径の長さを計算
    float radiusSum = radius1 + radius2;
    float radiusSumSquared = radiusSum * radiusSum;     // 2乗

    // 中心点間の距離よりも半径の和の方が近いなら当たっている
    if (distance <= radiusSumSquared)
    {
        return true;        // 当たった
    }
    else
    {
        return false;       // 当たってない
    }

}
