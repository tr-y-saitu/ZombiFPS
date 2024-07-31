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
{
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
    lineEndPosition     = initializeData.lineEndPosiion;
    position            = initializeData.position;
    direction           = initializeData.direction;
    power               = initializeData.power;
    speed               = initializeData.speed;
    penetratingPower    = initializeData.penetratingPower;

    // 当たり判定に必要なデータを渡す
    collisionManager->CollisionDataRegister(&collisionData);
}

/// <summary>
/// 更新
/// </summary>
void Bullet::Update()
{
    // 方向を設定


    // 移動量を計算
    VECTOR velocity = VScale(direction, speed);

    // 移動
    position = VAdd(position, velocity);

    // 当たっていたら
    // TODO:当たっていたらの処理をコリジョンマネージャー経由で追加する
    // 一旦未使用に戻したいので規定値になったら非アクティブ化させる
    if (position.z <= 100)
    {
        //isActive = false;   // 非アクティブ化
    }

    // 当たり判定に必要なデータを更新する
    UpdataCollisionData();

}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{
    // カプセル型のラインを描画
    DrawCapsule3D(lineStartPosition, position, HitBoxRadius,
        PolygonDetail, GetColor(255, 255, 0), GetColor(255, 255, 0), false);
}

/// <summary>
/// 当たり判定に必要なデータを更新する
/// </summary>
void Bullet::UpdataCollisionData()
{
    collisionData.tag                   = ObjectTag::Bullet;
    collisionData.lineStartPosition     = lineStartPosition;
    collisionData.lineEndPosition       = lineEndPosition;
    collisionData.bulletPower           = power;
}
