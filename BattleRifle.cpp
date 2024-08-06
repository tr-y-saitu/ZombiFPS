#include "BattleRifle.h"
#include "Bullet.h"
#include "GunStateBase.h"
#include "ModelDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
BattleRifle::BattleRifle()
{
    modelDataManager = ModelDataManager::GetInstance();
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
BattleRifle::~BattleRifle()
{
}

/// <summary>
/// 初期化
/// </summary>
void BattleRifle::Initialize()
{
    // モデルハンドルの読み込み
    modelHandle = modelDataManager->GetOriginalModelHandle(
        ModelDataManager::ModelDataType::BattleRifleModelData);

    // ステータスの初期化
    state = GunBase::GunState::IdleState;
    bulletDamagePower = BulletDamagePower;
    bulletPenetrationPower = BulletPenetrationPower;
    fireRate = GunFireRate;
    recoil = GunRecoil;
    accuracy = GunAccuracy;

    // スケールを調整
    MV1SetScale(modelHandle, InitializeScale);
}

/// <summary>
/// 弾丸情報の初期化
/// </summary>
void BattleRifle::InitializeBulletData(VECTOR cameraPosition, VECTOR targetPosition)
{

}

/// <summary>
/// 更新
/// </summary>
void BattleRifle:: Update(VECTOR setPosition, VECTOR cameraVector, VECTOR cameraTargetVector,
    VECTOR cameraPosition, float cameraPitch, Player::State playerState)
{
    // 座標を更新
    position = setPosition;

    // 角度を更新

    // 座標の設定
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void BattleRifle::Draw()
{
    // モデルの描画
    MV1DrawModel(modelHandle);
}

