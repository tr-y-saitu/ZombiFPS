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
    position            = initializeData.position;
    direction           = initializeData.direction;
    power               = initializeData.power;
    speed               = initializeData.speed;
    penetratingPower    = initializeData.penetratingPower;
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

    // 当たっていたら
    // TODO:当たっていたらの処理をコリジョンマネージャー経由で追加する
    // 一旦未使用に戻したいので規定値になったら非アクティブ化させる
    if (position.x <= 100)
    {
        isActive = false;   // 非アクティブ化
    }

}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{

}
