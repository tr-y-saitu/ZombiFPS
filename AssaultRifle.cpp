#include "AssaultRifle.h"
#include "Shot.h"
#include "GunStateBase.h"
#include "ModelDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
AssaultRifle::AssaultRifle()
{
    modelDataManager = ModelDataManager::GetInstance();
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
AssaultRifle::~AssaultRifle()
{
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
    shotDamagePower = ShotDamagePower;
    shotPenetrationPower = ShotPenetrationPower;
    fireRate = GunFireRate;
    recoil = GunRecoil;
    accuracy = GunAccuracy;
}

/// <summary>
/// 更新
/// </summary>
void AssaultRifle::Update()
{
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
