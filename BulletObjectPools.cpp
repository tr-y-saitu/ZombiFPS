#include "BulletObjectPools.h"
#include "Bullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
BulletObjectPools::BulletObjectPools()
{
    // 弾丸のインスタンスを作成
    for (int i = 0; i < BulletInstanceNumber; i++)
    {
        inactiveBullet.push_back(new Bullet());
    }
}

/// <summary>
/// デストラクタ
/// </summary>
BulletObjectPools::~BulletObjectPools()
{
    // メモリ解放
    // NOTE:下記と同様の意味
    //for (list<Bullet*>::iterator it = inactiveBullet.begin(); it != inactiveBullet.end(); ++it)
    for (Bullet* bullet : inactiveBullet)
    {
        delete bullet;
    }
}

/// <summary>
/// 現在未使用の弾丸があるかどうか調べる
/// </summary>
/// <returns>未使用のものがある:true   未使用のものがない:false</returns>
bool BulletObjectPools::hasInactiveBulletInstance()
{
    // 未使用があればture
    return inactiveBullet.size();
}

/// <summary>
/// 未使用の弾丸のインスタンスを渡す
/// </summary>
/// <param name="bullet">渡したい使用中リストのアドレス</param>
void BulletObjectPools::AcquireInactiveBulletInstance(list<Bullet*>& activeBullet)
{
    // 未使用のプールが存在するかチェック
    if (hasInactiveBulletInstance())
    {
        // 未使用のプールの最初の要素を、使用中リストの最後にインスタンスを移動する
        activeBullet.splice(activeBullet.end(), inactiveBullet, inactiveBullet.begin());
    }
}

/// <summary>
/// 使用中リストから未使用リストにインスタンスを移動する
/// </summary>
/// <param name="activeBullet">移動したい使用中のリストのアドレス</param>
void BulletObjectPools::ReturnActiveBulletInstance(list<Bullet*> activeBullet)
{
    // 使用中リストの最初の要素を、未使用リストの最後にインスタンスを移動する
    inactiveBullet.splice(inactiveBullet.end(), activeBullet, activeBullet.begin());
}
