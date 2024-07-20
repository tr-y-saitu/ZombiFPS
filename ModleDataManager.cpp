#include "Common.h"
#include "ModleDataManager.h"

// 初期化
ModleDataManager* ModleDataManager::modleDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
ModleDataManager::ModleDataManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ModleDataManager::~ModleDataManager()
{
}

/// <summary>
/// インスタンスの作成
/// </summary>
void ModleDataManager::CreateInstance()
{
    if (modleDataManager == NULL)
    {
        modleDataManager = new ModleDataManager();
    }
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>画像データマネージャーのインスタンスのアドレス</returns>
ModleDataManager* ModleDataManager::GetInstance()
{
    return modleDataManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void ModleDataManager::DeleteInstance()
{
    delete(modleDataManager);
}