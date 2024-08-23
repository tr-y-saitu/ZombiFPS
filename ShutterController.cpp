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
/// FIXME:定数をデータクラスにまとめて内容処理をforで回せるようにする
void ShutterController::CreateInitializeData()
{
    // シャッター１
    MATRIX shutter1Matrix = MGetRotY(90.0f * DX_PI_F / 180.0f);
    shutterInitializeDataList[0] = { Shutter1,VGet(32,0,10),shutter1Matrix,VGet(3.0f, 5.0f, 3.5f),
        modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ShutterModelData),
    500};

    // シャッター２
    MATRIX shutter2Matrix = MGetIdent();
    shutterInitializeDataList[1] = { Shutter2,VGet(-21,0,-5),shutter2Matrix,VGet(3.0f, 5.0f, 3.5f),
        modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ShutterModelData),
    750};

    // シャッター３
    MATRIX shutter3Matrix = MGetRotY(-90.0f * DX_PI_F / 180.f);
    shutterInitializeDataList[2] = { Shutter3,VGet(49,0,-19),shutter3Matrix,VGet(3.0f, 5.0f, 2.8f),
        modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ShutterModelData)
    ,1000};
}

/// <summary>
/// 更新
/// </summary>
void ShutterController::Update()
{
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
