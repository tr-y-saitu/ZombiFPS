#include "Bullet.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{

}

/// <summary>
/// 初期化
/// </summary>
void Bullet::Initialize(BulletInitializeData initializeData)
{
    position = initializeData.position;
    direction = initializeData.direction;
    power = initializeData.power;
    speed = initializeData.speed;
    penetratingPower = initializeData.penetratingPower;
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
}

/// <summary>
/// 描画
/// </summary>
void Bullet::Draw()
{

}
