#include "ShutterController.h"
#include "Shutter.h"
#include "CollisionManager.h"
#include "ModelDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ShutterController::ShutterController()
{
    // 当たり判定クラスの参照をもらう
    collisionManager = CollisionManager::GetInstance();

    // モデルデータクラスの参照をもらう
    modelDataManager = ModelDataManager::GetInstance();

    // シャッターのメモリ確保
    CreateShutter();
}

/// <summary>
/// デストラクタ
/// </summary>
ShutterController::~ShutterController()
{
    // メモリ開放
    for (int i = 0; i < shutterList.size(); i++)
    {
        delete(shutterList[i]);
    }
}

/// <summary>
/// 初期化
/// </summary>
void ShutterController::Initialize()
{
    // 初期化用データの作成
    CreateInitializeData();

    // シャッターの初期化
    for (int i = 0; i < shutterList.size(); i++)
    {
        shutterList[i]->Initialize(shutterInitializeDataList[i]);
    }
}

/// <summary>
/// シャッターの作成
/// </summary>
void ShutterController::CreateShutter()
{
    // シャッターのメモリ確保
    for (int i = 0; i < ShutterNumber; i++)
    {
        shutterList.push_back(new Shutter());
    }
}

/// <summary>
/// シャッターの初期化用データの作成
/// </summary>
void ShutterController::CreateInitializeData()
{
    shutterInitializeDataList[ShutterTag::Center1] = {Center1,VGet(-22,0,-4),MGetIdent(),VGet(0.003,0.011,0.01),modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ShutterModelData)};
}

/// <summary>
/// 更新
/// </summary>
void ShutterController::Update()
{
    // デバッグ用初期化
    Initialize();

    // シャッターの更新
    for (int i = 0; i < shutterList.size(); i++)
    {
        shutterList[i]->Update();
    }
}

/// <summary>
/// 描画
/// </summary>
void ShutterController::Draw()
{
    // シャッターの描画
    for (int i = 0; i < shutterList.size(); i++)
    {
        shutterList[i]->Draw();
    }
}
