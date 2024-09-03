#include "AssaultRifle.h"
#include "Bullet.h"
#include "GunStateBase.h"
#include "ModelDataManager.h"
#include "ImageDataManager.h"
#include "EffectManager.h"
#include "GunIdleState.h"
#include "GunReloadState.h"
#include "GunRunState.h"
#include "GunShotState.h"

/// <summary>
/// コンストラクタ
/// </summary>
AssaultRifle::AssaultRifle()
    : runAnimationFactor(0.0f)
    , reloadAnimationFactor(0.0f)
    , isEmissiveIncreasing(false)
    , emissiveIntensity(MinimumEmissive)
{
    modelDataManager    = ModelDataManager::GetInstance();
    imageDataManager    = ImageDataManager::GetInstance();
    effectManager       = EffectManager::GetInstance();
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
AssaultRifle::~AssaultRifle()
{
    // 要素の削除
    activeBullet.clear();

    // メモリ解放
    for (Bullet* bullet : activeBullet)
    {
        delete(bullet);
    }
}

/// <summary>
/// 初期化
/// </summary>
void AssaultRifle::Initialize()
{
    // モデルハンドルの読み込み
    modelHandle = modelDataManager->GetOriginalModelHandle(
        ModelDataManager::ModelDataType::AssaultRifleModelData);

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
void AssaultRifle::InitializeBulletData(VECTOR cameraPosition, VECTOR targetPosition)
{

}

/// <summary>
/// 更新
/// </summary>
void AssaultRifle::Update(VECTOR setPosition, VECTOR cameraVector, VECTOR cameraTargetVector,
    VECTOR cameraPosition, float cameraPitch, Player::State playerState, Player::AimState currentAimState)
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
void AssaultRifle::Draw()
{
    // モデルの描画
    MV1DrawModel(modelHandle);
}

