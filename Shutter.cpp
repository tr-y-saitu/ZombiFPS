#include "Shutter.h"
#include "CollisionManager.h"
#include "ShutterController.h"


/// <summary>
/// コンストラクタ
/// </summary>
Shutter::Shutter()
    : position          (VGet(0,0,0))
    , rotationMatrix    (MGetIdent())
    , modelHandle       (-1)
    , isOpen            (false)
{
    // 当たり判定管理クラスの参照をもらう
    collisionManager = CollisionManager::GetInstance();

    // 当たった後の関数ポインタを渡す
    collisionData.onHit = std::bind(&Shutter::OnHit, this, std::placeholders::_1);

    // 生成時に当たり判定を開始してほしいので当たり判定をアクティブ化する
    collisionData.isCollisionActive = true;

    // 当たり判定に必要なデータを渡す
    collisionManager->RegisterCollisionData(&collisionData);
}

/// <summary>
/// デストラクタ
/// </summary>
Shutter::~Shutter()
{
}

/// <summary>
/// 初期化
/// </summary>
void Shutter::Initialize(ShutterController::ShutterInitializeData initializeData)
{
    shutterTag      = initializeData.tag;                           // シャッターの固有名称
    position        = initializeData.initializePosition;            // 座標
    rotationMatrix  = initializeData.initializeRotationMatrix;      // 回転率
    modelHandle     = initializeData.modelHandle;                   // モデルハンドル
    interactionCost = initializeData.interactionCost;               // インタラクトにかかるコスト

    // モデルのサイズを設定
    MV1SetScale(modelHandle, initializeData.initializeScale);

    // モデルを回転させる
    MV1SetRotationMatrix(modelHandle, rotationMatrix);
}

/// <summary>
/// 更新
/// </summary>
void Shutter::Update()
{
    // 当たり判定情報の更新
    UpdateCollisionData();

    // 開ける処理を行う
    UpdateOpen();

    // モデルの座標を設定
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void Shutter::Draw()
{
    // モデルを描画
    MV1DrawModel(modelHandle);

    // デバッグ当たり判定の描画
    DrawSphere3D(collisionData.centerPosition, collisionData.radius,
        DebugSphereDivision, DebugPolygonColorBlue, DebugPolygonColorBlue,false);

    // デバッグシャッターにアクセルできる半径を描画
    DrawSphere3D(collisionData.centerPosition, collisionData.interactRadius,
        DebugSphereDivision, DebugPolygonColorRed, DebugPolygonColorRed, false);
}

/// <summary>
/// 当たり判定情報を更新する
/// </summary>
void Shutter::UpdateCollisionData()
{
    collisionData.tag               = ObjectTag::Shutter;   // タグ
    collisionData.radius            = HitBoxRadius;         // 半径
    collisionData.interactRadius    = HItBoxInteractRadius; // シャッターにアクセルできる当たり判定
    collisionData.centerPosition    = position;             // 座標
    collisionData.centerPosition.y  = position.y + 4.5f;    // 高さを合わせる
    collisionData.interactionCost   = interactionCost;      // インタラクトするコスト
}

/// <summary>
/// オブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData">接触したオブジェクト</param>
void Shutter::OnHit(CollisionData hitObjectData)
{
    switch (hitObjectData.tag)
    {
    case ObjectTag::Player:
        // プレイヤーからインタラクトする指示が出れば
        if (hitObjectData.isInteracted)
        {
            isOpen = true;      // 扉を開ける
        }

        break;

    default:
        break;
    }
}

/// <summary>
/// シャッターを開ける
/// </summary>
void Shutter::UpdateOpen()
{
    // 開ける指示が出たら
    if (isOpen)
    {
        // 上昇上限でなければ
        if (position.y <= RiseUpperLimit)
        {
            // 少しづつ上に上げる
            position.y += OpenSpeed;
        }
    }
}
