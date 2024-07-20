#include "Common.h"
#include "EffectDataManager.h"

// 初期化
EffectDataManager* EffectDataManager::effectDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
EffectDataManager::EffectDataManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
EffectDataManager::~EffectDataManager()
{
}

/// <summary>
/// インスタンスの作成
/// </summary>
void EffectDataManager::CreateInstance()
{
    if (effectDataManager == NULL)
    {
        effectDataManager = new EffectDataManager();
    }
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>エフェクトデータマネージャーのインスタンスのアドレス</returns>
EffectDataManager* EffectDataManager::GetInstance()
{
    return effectDataManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void EffectDataManager::DeleteInstance()
{
    delete(effectDataManager);
}