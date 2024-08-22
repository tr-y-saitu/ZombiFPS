#include "CollisionManager.h"


// 初期化
CollisionManager* CollisionManager::collisionManager = NULL;
std::vector<CollisionData*> CollisionManager::collisionDataList;

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
    // メモリ解放 //

    // 当たり判定情報リスト
    collisionDataList.clear();

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

// 当たり判定データの読み込み
void CollisionManager::RegisterCollisionData(CollisionData* data)
{
    // 当たり判定用情報追加
    collisionDataList.push_back(data);
}

/// <summary>
/// すべての当たり判定処理
/// </summary>
void CollisionManager::Update()
{
    for (int i = 0; i < collisionDataList.size(); i++)
    {
        for (int j = 0; j < collisionDataList.size(); j++)
        {
            // どのタイプの当たり判定を行うか調べる
            CollisionData data1 = *collisionDataList[i];
            CollisionData data2 = *collisionDataList[j];

            // エネミーと弾丸の当たり判定(カプセル対線分の当たり判定)
            if (data1.tag == ObjectTag::EnemyBoby && data2.tag == ObjectTag::Bullet)
            {
                if (IsCollisionCapsuleLine(data1.startPosition,data1.endPosition,data1.radius,
                                            data2.lineStartPosition,data2.lineEndPosition))
                {
                    // 当たった時の関数を呼び出す
                   data1.onHit(data2);
                   data2.onHit(data1);
                }
            }

            // エネミーとエネミーの当たり判定(カプセルとカプセル)
            if (data1.tag == ObjectTag::EnemyBoby && data2.tag == ObjectTag::EnemyBoby)
            {
                // カプセル同士の当たり判定処理
                if (IsCollisionCapsuleCapsule(data1.startPosition,data1.endPosition,data1.radius,
                    data2.startPosition,data2.endPosition,data2.radius))
                {
                    // 当たった時の関数を呼び出す
                    data1.onHit(data2);
                    data2.onHit(data1);
                }

            }

            // 球体とカプセル

            // カプセルとライン


            // 当たり判定を消してほしい場合
            if (!collisionDataList[i]->isCollisionActive)
            {
                collisionDataList.erase(collisionDataList.begin() + i);

                // 削除後の要素が次にチェックされるため、インデックスを調整
                i--;
            }
        }
    }
}

// 線と球との当たり判定
bool CollisionManager::IsCollisionLineSphere(VECTOR sphereCenter, float radius,
    VECTOR lineStart, VECTOR lineEnd)
{
    return 1;
}

/// <summary>
/// カプセルと線分の当たり判定
/// </summary>
/// <param name="capsuleTopPosition">カプセルを形成する開始座標</param>
/// <param name="capuseleBottomPosition">カプセルを形成する終了座標</param>
/// <param name="capuseleRadius">カプセルの半径</param>
/// <param name="lineStartPosition">線の始まり</param>
/// <param name="lineEndPosition">線の終わり</param>
/// <returns>当たったかどうか</returns>
bool CollisionManager::IsCollisionCapsuleLine(VECTOR capsuleStartPosition, VECTOR capuseleEndPosition, float capuseleRadius,
    VECTOR lineStartPosition, VECTOR lineEndPosition)
{
    bool isHit = false;

    // 二つの線分の最短距離を計算
    float distance = Segment_Segment_MinLength(capsuleStartPosition, capuseleEndPosition, lineStartPosition, lineEndPosition);

    // 最短距離よりも半径の方が短ければ当たっている
    if (distance <= capuseleRadius)
    {
        isHit = true;
    }

    return isHit;
}

// カプセルと線分の当たり判定
bool CollisionManager::IsCollisionSphereCapsule(VECTOR sphereCenter, float sphereRadius,
    VECTOR capsuleStart, VECTOR capsuleEnd, float capuleRadius)
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
bool CollisionManager::IsCollisionCapsuleCapsule(VECTOR capsule1Start, VECTOR capsule1End, float capsule1Radius,
    VECTOR capsule2Start, VECTOR capsule2End, float capsule2Radius)
{
    // 当たったかどうか
    bool isHit = false;

    // カプセル間の最短距離を計算
    float distance = Segment_Segment_MinLength(capsule1Start, capsule1End, capsule2Start, capsule2End);

    // 最短距離が両カプセルの半径の和以下であれば衝突している
    float combinedRadius = capsule1Radius + capsule2Radius;

    if (distance <= combinedRadius * combinedRadius)
    {
        return true; // 当たっている
    }

    return isHit;
}
