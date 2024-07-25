#include "BattleRifle.h"
#include "Shot.h"
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
    shotDamagePower = ShotDamagePower;
    shotPenetrationPower = ShotPenetrationPower;
    fireRate = GunFireRate;
    recoil = GunRecoil;
    accuracy = GunAccuracy;

    // スケールを調整
    MV1SetScale(modelHandle, InitializeScale);
}

/// <summary>
/// 更新
/// </summary>
void BattleRifle:: Update(VECTOR setPosition, VECTOR cameraVector, float cameraPitch)
{
    // 座標を更新
    position = setPosition;

    // 角度を更新
    UpdateAngle(cameraVector, cameraPitch);

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

