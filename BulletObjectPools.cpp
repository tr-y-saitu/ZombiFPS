#include "BulletObjectPools.h"
#include "Bullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
BulletObjectPools::BulletObjectPools()
{
    // 弾丸のインスタンスを作成
    inactiveBullet.resize(BulletInstanceNumber);
}

/// <summary>
/// デストラクタ
/// </summary>
BulletObjectPools::~BulletObjectPools()
{
    // 要素をすべて削除
    inactiveBullet.clear();
    activeBullet.clear();
}
