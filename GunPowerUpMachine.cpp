#include "GunPowerUpMachine.h"
#include "CollisionManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
GunPowerUpMachine::GunPowerUpMachine()
    : position      (InitializePosition)
{
}

/// <summary>
/// デストラクタ
/// </summary>
GunPowerUpMachine::~GunPowerUpMachine()
{
}

/// <summary>
/// 初期化
/// </summary>
void GunPowerUpMachine::Initialize()
{
    // 座標設定
    position = InitializePosition;

    // 当たり判定用情報
    collisionData.tag               = ObjectTag::GunPowerUpMachine;
    collisionData.centerPosition    = InitializePosition;
    collisionData.radius            = CollisionRadius;
    collisionData.interactRadius    = CollisionInteractRadius;
    collisionData.interactionCost   = InteractCost;

    // 当たり判定クラスのアドレスをもらう
    collisionManager = CollisionManager::GetInstance();

    // 当たり判定管理クラスに当たった後の関数のアドレスを渡す
    collisionData.onHit = std::bind(&GunPowerUpMachine::OnHit, this, std::placeholders::_1);

    // 当たり判定を開始する
    collisionData.isCollisionActive = true;

    // 当たり判定に必要なデータを管理クラスに渡す
    collisionManager->RegisterCollisionData(&collisionData);
}

/// <summary>
/// 更新
/// </summary>
void GunPowerUpMachine::Update()
{
    // 処理なし
}

/// <summary>
/// 描画
/// </summary>
void GunPowerUpMachine::Draw()
{
    // デバッグ当たり判定の描画
    DrawSphere3D(collisionData.centerPosition, collisionData.radius,
        DebugSphereDivision, DebugPolygonColorBlue, DebugPolygonColorBlue, false);

    // インタラクトできる半径を描画
    DrawSphere3D(collisionData.centerPosition, collisionData.interactRadius,
        DebugSphereDivision, DebugPolygonColorRed, DebugPolygonColorRed, false);
}

/// <summary>
/// オブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData">接触したオブジェクトの情報</param>
void GunPowerUpMachine::OnHit(CollisionData hitObjectData)
{
    // 処理なし
}
