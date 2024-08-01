#include "SubmachineGun.h"
#include "Bullet.h"
#include "GunStateBase.h"
#include "ModelDataManager.h"
#include "GunIdleState.h"
#include "GunReloadState.h"
#include "GunRunState.h"
#include "GunShotState.h"

/// <summary>　　　　　　
/// コンストラクタ
/// </summary>
SubmachineGun::SubmachineGun()
{
    modelDataManager = ModelDataManager::GetInstance();
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
SubmachineGun::~SubmachineGun()
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
void SubmachineGun::Initialize()
{
    // モデルハンドルの読み込み
    modelHandle = modelDataManager->GetOriginalModelHandle(
        ModelDataManager::ModelDataType::SubmachineGunModelData);

    // ステータスの初期化
    state                   = GunBase::GunState::IdleState;

    // TODO:
    // 状態クラスを未作成のため未実装
    //currentState            = new GunIdleState();

    // 弾丸情報の初期化
    bulletDamagePower       = BulletDamagePower;
    bulletPenetrationPower  = BulletPenetrationPower;
    fireRate                = GunFireRate;
    recoil                  = GunRecoil;
    accuracy                = GunAccuracy;
    positionOffsetAmount = VGet(0, 0.5, -1);

    // スケールを調整
    MV1SetScale(modelHandle, InitializeScale);
}

/// <summary>
/// 更新
/// </summary>
void SubmachineGun::Update(VECTOR setPosition, VECTOR cameraVector, VECTOR cameraTargetVector,
     VECTOR cameraPosition, float cameraPitch)
{
    // 座標を更新
    position = VAdd(setPosition, GunOffset);

    // 座標を少しずらす
    FixedGunPosition(setPosition, cameraVector);

    // 角度を更新
    UpdateAngle(cameraVector, cameraPitch);

    // 弾丸の更新
    UpdateShooting(cameraPosition,cameraTargetVector);


    // 座標の設定
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 弾丸情報の初期化
/// </summary>
void SubmachineGun::InitializeBulletData(VECTOR cameraPosition, VECTOR targetPosition)
{
    bulletData.lineStartPosition    = cameraPosition;           // カメラの座標
    bulletData.lineEndPosiion       = targetPosition;           // カメラの向いている座標
    bulletData.direction            = VNorm(VSub(targetPosition, cameraPosition));  // 弾丸の移動方向
    bulletData.position             = position;                 // 座標
    bulletData.power                = BulletDamagePower;        // 威力
    bulletData.speed                = BulletSpeed;              // 速度
    bulletData.penetratingPower     = BulletPenetrationPower;   // 貫通力
}

/// <summary>
/// 描画
/// </summary>
void SubmachineGun::Draw()
{
    // モデルの描画
    MV1DrawModel(modelHandle);

    // 現在使用中の弾丸を描画
    for (auto it = activeBullet.begin(); it != activeBullet.end(); ++it)
    {
        (*it)->Draw();
    }
}

/// <summary>
/// 銃を発砲する
/// </summary>
void SubmachineGun::UpdateShooting(VECTOR cameraPosition, VECTOR targetPosition)
{
    // 弾丸の初期化用データの更新
    InitializeBulletData(cameraPosition,targetPosition);

    // 現在使用中の弾丸の更新
    for (auto it = activeBullet.begin(); it != activeBullet.end(); ++it)
    {
        (*it)->Update();
    }
}


