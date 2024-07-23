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