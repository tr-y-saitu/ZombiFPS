#include "CollisionManager.h"
#include "Bullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
    : position          (VGet(0,0,0))
    , direction         (VGet(0,0,0))
    , power             (0)
    , speed             (0)
    , penetratingPower  (0)
    , isActive          (true)
    , getMoney          (0)
{
    // 当たり判定をするかどうか
    collisionData.isCollisionActive = true;

    // 当たり判定管理クラス
    collisionManager = CollisionManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{

}

/// <summary>
/// 弾丸情報の初期化
/// </summary>
/// <param name="initializeData">初期化する弾丸のデータ</param>
void Bullet::Initialize(BulletInitializeData initializeData)
{
    // 弾丸は初期化する時点で使用中になるのでtrue
    isActive            = true;
    lineStartPosition   = initializeData.lineStartPosition;
    lineEndPosition     = initializeData.lineEndPosition;
    position            = initializeData.position;
    direction           = initializeData.direction;
    power               = initializeData.power;
    speed               = initializeData.speed;
    penetratingPower    = initializeData.penetratingPower;
    getMoney            = 0;
    activeFrameCount    = ActiveFrameCount;

    // すでに接触したオブジェクトのリストを初期化
    hitterList.clear();
}

/// <summary>
/// 更新
/// </summary>
void Bullet::Update()
{
    // 移動量を計算
    VECTOR velocity = VScale(direction, speed);

    // 移動
    position = VAdd(position, velocity);

    // 自身のOnHit関数をもとに新しい関数を作成
    // コリジョンマネージャーに渡し、接触時に呼び出してもらう
    collisionData.onHit = std::bind(&Bullet::OnHit, this, std::placeholders::_1);

    // 当たり判定に必要なデータを更新する
    UpdateCollisionData();

    // 弾丸は１フレームのみ存在する
    isActive = false;       // 未使用のプールに戻す
}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{
    // デバッグ描画
    // カプセル型のラインを描画
    DrawCapsule3D(lineStartPosition, position, HitBoxRadius,PolygonDetail, DebugPolygonColorRed, DebugPolygonColorRed, false);
}

/// <summary>
/// 当たり判定に必要なデータを更新する
/// </summary>
void Bullet::UpdateCollisionData()
{
    collisionData.tag                   = ObjectTag::Bullet;
    collisionData.lineStartPosition     = lineStartPosition;
    collisionData.lineEndPosition       = position;
    collisionData.bulletPower           = power;
    collisionData.objectAddress         = this;                 // 自身のアドレスを初期化する

    // 当たり判定に必要なデータを渡す
    collisionManager->RegisterCollisionData(&collisionData);
}

/// <summary>
/// オブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData">オブジェクトのデータ</param>
void Bullet::OnHit(CollisionData hitObjectData)
{
    switch (hitObjectData.tag)
    {
    case ObjectTag::EnemyBoby:
        // 処理なし

        break;

    default:
        break;
    }
}

/// <summary>
/// 選択したオブジェクトをすでに接触しているかを確認する
/// </summary>
/// <param name="hitObjectAddress">接触済みか調べるオブジェクトのアドレス</param>
/// <returns>１度でも接触していたら:true  それ以外は:false</returns>
bool Bullet::IsObjectHit(HitObjectAddress* hitObjectAddress)
{
    //当たったオブジェクトのListに引数のHitObjectAddressが格納されてたらtrue
    for (int i = 0; i < hitterList.size(); i++)
    {
        if (hitterList[i].objectAddress == hitObjectAddress)
        {
            return true;
        }
    }
    return false;
}
