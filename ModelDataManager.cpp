#include "ModelDataManager.h"

// 初期化
ModelDataManager* ModelDataManager::modelDataManager = NULL;
map<ModelDataManager::ModelDataType, int> ModelDataManager::modelDataList;

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
    modelDataList[StageModelData] = MV1LoadModel("Data/Stage/backroomsScaleMini.mv1");
    modelDataList[PlayerModelData] = MV1LoadModel("Data/Player/playerScaleMini.mv1");
}

/// <summary>
/// 使用したいモデルデータを取得する
/// </summary>
/// <param name="type">データの種類</param>
/// <returns>データハンドル</returns>
int ModelDataManager::GetModelHandle(ModelDataType type)
{
    // 複製データを渡す
    return MV1DuplicateModel(modelDataList[type]);
}