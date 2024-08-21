#include "ModelDataManager.h"

// 初期化
ModelDataManager* ModelDataManager::modelDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
ModelDataManager::ModelDataManager()
{
    // モデルデータの読み込み
    ModelDataLoad();
}

/// <summary>
/// デストラクタ
/// </summary>
ModelDataManager::~ModelDataManager()
{
    // モデルデータの削除
    for (int i = 0; i < modelDataList.size(); i++)
    {
        // リストにデータが入っていれば
        if (modelDataList[(ModelDataType)i])
        {
            MV1DeleteModel(modelDataList[(ModelDataType)i]);
        }
    }
}

/// <summary>
/// インスタンスの作成
/// </summary>
void ModelDataManager::CreateInstance()
{
    if (modelDataManager == NULL)
    {
        modelDataManager = new ModelDataManager();
    }
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>画像データマネージャーのインスタンスのアドレス</returns>
ModelDataManager* ModelDataManager::GetInstance()
{
    return modelDataManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void ModelDataManager::DeleteInstance()
{
    delete(modelDataManager);
}

/// <summary>
/// モデルデータの読み込み
/// </summary>
void ModelDataManager::ModelDataLoad()
{
    // ステージ
    modelDataList[StageModelData]           = MV1LoadModel("Data/Stage/BackroomsScaleMini.mv1");

    // シャッター
    modelDataList[ShutterModelData]         = MV1LoadModel("Data/Object/ShutterMini.mv1");

    // 弾薬補充箱
    modelDataList[AmmoBox]                  = MV1LoadModel("Data/Stage/AmmoBox/AmmoBox.mv1");

    // キャラクター
    modelDataList[PlayerModelData]          = MV1LoadModel("Data/Player/playerAnimationFixed.mv1");
    modelDataList[EnemyModelData]           = MV1LoadModel("Data/Enemy/EenmyModelZombie.mv1");

    // 銃
    modelDataList[SubmachineGunModelData]   = MV1LoadModel("Data/Gun/MP5/MP5.mv1");
    modelDataList[BattleRifleModelData]     = MV1LoadModel("Data/Gun/M14/M14.mv1");
    modelDataList[AssaultRifleModelData]    = MV1LoadModel("Data/Gun/AR15/AR15.mv1");
}

/// <summary>
/// 一つしか使用しないモデルデータを取得する
/// </summary>
/// <param name="type">モデルの種類</param>
/// <returns>データハンドル</returns>
int ModelDataManager::GetOriginalModelHandle(ModelDataType type)
{
    // オリジナルデータを渡す
    return modelDataList[type];
}

/// <summary>
/// 複製し使用するモデルデータを取得する
/// </summary>
/// <param name="type">データの種類</param>
/// <returns>データハンドル</returns>
int ModelDataManager::GetDuplicatesModelHandle(ModelDataType type)
{
    // 複製データを渡す
    return MV1DuplicateModel(modelDataList[type]);
}
