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
{
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
    shutterTag      = initializeData.tag;                       // シャッターの固有名称
    position        = initializeData.initializePosition;        // 座標
    rotationMatrix  = initializeData.initializeRotationMatrix;  // 回転率
    modelHandle     = initializeData.modelHandle;               // モデルハンドル

    // モデルのサイズを設定
    MV1SetScale(modelHandle, initializeData.initializeScale);

    // 座標を回転させる
    position = VTransform(position, rotationMatrix);
}

/// <summary>
/// 更新
/// </summary>
void Shutter::Update()
{
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
}
