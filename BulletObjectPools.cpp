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
bool BulletObjectPools::HasInactiveBulletInstance()
{
    // 未使用があればture
    return inactiveBullet.size();
}

/// <summary>
/// 未使用の弾丸のインスタンスを返す
/// </summary>
/// <returns>未使用弾丸があればそのアドレス   無ければnullptr</returns>
Bullet* BulletObjectPools::GetInactiveBullet()
{
    // プールから未使用が存在するかチェック
    if (HasInactiveBulletInstance())
    {
        // 未使用のプールの先頭から要素を取得
        Bullet* bullet = inactiveBullet.front();

        // 移動させるので先頭要素は削除
        inactiveBullet.pop_front();

        return bullet;
    }
    else
    {
        return nullptr;
    }
}

/// <summary>
/// 使用中リストから未使用リストにインスタンスを移動する
/// </summary>
/// <param name="activeBullet">移動したい使用中のリストのアドレス</param>
void BulletObjectPools::ReturnActiveBulletInstance(list<Bullet*>& activeBullet)
{
    // 使用中弾丸を調べる
    for (auto it = activeBullet.begin(); it != activeBullet.end();)
    {
        Bullet* bullet = *it;

        // 弾丸が使用中でない場合、未使用リストに移動する
        if (!bullet->GetIsActive())
        {
            // 弾丸を未使用リストに移動
            inactiveBullet.splice(inactiveBullet.end(), activeBullet, it++);
        }
        else
        {
            // イテレータを次に進める
            ++it;
        }
    }

}
