#include "CollisionManager.h"
#include "AmmoBox.h"
#include "ModelDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
AmmoBox::AmmoBox()
    : position      (InitializePosition)
{
}

/// <summary>
/// デストラクタ
/// </summary>
AmmoBox::~AmmoBox()
{
}

/// <summary>
/// 初期化
/// </summary>
void AmmoBox::Initialize()
{
    // 座標設定
    position = InitializePosition;

    // 当たり判定用情報
    collisionData.tag               = ObjectTag::AmmoBox;
    collisionData.centerPosition    = CollisionInitializePosition;
    collisionData.radius            = CollisionRadius;
    collisionData.interactRadius    = CollisionInteractRadius;
    collisionData.interactionCost   = InteractCost;

    // モデルデータマネージャーのアドレスをもらう
    modelDataManager = ModelDataManager::GetInstance();

    // モデルデータをもらう
    modelHandle = modelDataManager->GetDuplicatesModelHandle(ModelDataManager::AmmoBox);

    // スケールを設定
    MV1SetScale(modelHandle, InitializeScale);

    // 当たり判定クラスのアドレスをもらう
    collisionManager = CollisionManager::GetInstance();

    // 当たり判定管理クラスに当たった後の関数のアドレスを渡す
    collisionData.onHit = std::bind(&AmmoBox::OnHit, this, std::placeholders::_1);

    // 当たり判定を開始する
    collisionData.isCollisionActive = true;

    // 当たり判定に必要なデータを管理クラスに渡す
    collisionManager->RegisterCollisionData(&collisionData);
}

/// <summary>
/// 更新
/// </summary>
void AmmoBox::Update()
{
    // モデルの座標設定
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void AmmoBox::Draw()
{
    // モデルの描画
    MV1DrawModel(modelHandle);

    //// デバッグ当たり判定の描画
    //DrawSphere3D(collisionData.centerPosition, collisionData.radius,
    //    DebugSphereDivision, DebugPolygonColorBlue, DebugPolygonColorBlue, false);

    //// デバッグシャッターにアクセルできる半径を描画
    //DrawSphere3D(collisionData.centerPosition, collisionData.interactRadius,
    //    DebugSphereDivision, DebugPolygonColorRed, DebugPolygonColorRed, false);
}

/// <summary>
/// オブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData">接触したオブジェクトの情報</param>
void AmmoBox::OnHit(CollisionData hitObjectData)
{
    // 処理なし
}
