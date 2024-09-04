#include "EnemyObjectPools.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyObjectPools::EnemyObjectPools()
{
    // エネミーのインスタンスを作成
    for (int i = 0; i < EnemyTotalNumber; i++)
    {
        inactiveEnemy.push_back(new EnemyGroup());
    }
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyObjectPools::~EnemyObjectPools()
{
    // メモリ解放
    for (EnemyGroup* enemy : inactiveEnemy)
    {
        delete enemy;
    }
}

/// <summary>
/// 現在未使用のエネミーがあるかどうか調べる
/// </summary>
/// <returns>未使用のエネミーがある:true   ない:false</returns>
bool EnemyObjectPools::HasInactiveEnemyInstance()
{
    // 未使用があればtrue
    return inactiveEnemy.size();
}

/// <summary>
/// 未使用のエネミーのインスタンスを渡す
/// </summary>
/// <returns>未使用のエネミーがあればそのインスタンス　　無ければnullptr</returns>
EnemyGroup* EnemyObjectPools::GetInactiveEnemy()
{
    // プールに未使用が存在するかチェック
    if (HasInactiveEnemyInstance())
    {
        // 未使用のプールの先頭から要素を取得
        EnemyGroup* enemy = inactiveEnemy.front();

        // 移動させるので先頭要素は削除
        inactiveEnemy.pop_front();

        return enemy;
    }
    else
    {
        // 未使用がない場合はヌル
        return nullptr;
    }
}

/// <summary>
/// 使用中のリストから未使用リストにインスタンスを移動する
/// </summary>
/// <param name="activeEnemy">移動したい使用中のリストのアドレス</param>
bool EnemyObjectPools::ReturnActiveEnemyInstance(list<EnemyGroup*>& activeEnemy)
{
    bool hasReturned = false;

    // 使用中のエネミーを調べる
    for (auto it = activeEnemy.begin(); it != activeEnemy.end();)
    {
        EnemyGroup* enemy = *it;
        // エネミーが使用中出ない場合、未使用リストに移動する
        if (!enemy->GetIsActive())
        {
            // エネミーの当たり判定を非アクティブ化する
            enemy->SetCollisionDataActive(false);

            // エネミーを未使用リストに移動
            inactiveEnemy.splice(inactiveEnemy.end(), activeEnemy, it++);

            // 未使用リストに変換した
            hasReturned = true;
        }
        else
        {
            // イテレータを次に進める
            ++it;
        }
    }

    return hasReturned;
}
