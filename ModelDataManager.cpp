#include "Common.h"
#include "ModelDataManager.h"

// 初期化
ModelDataManager* ModelDataManager::modelDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
ModelDataManager::ModelDataManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ModelDataManager::~ModelDataManager()
{
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