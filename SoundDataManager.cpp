#include "Common.h"
#include "SoundDataManager.h"

// 初期化
SoundDataManager* SoundDataManager::soundDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
SoundDataManager::SoundDataManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
SoundDataManager::~SoundDataManager()
{
}

/// <summary>
/// インスタンスの作成
/// </summary>
void SoundDataManager::CreateInstance()
{
    if (soundDataManager == NULL)
    {
        soundDataManager = new SoundDataManager();
    }
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>画像データマネージャーのインスタンスのアドレス</returns>
SoundDataManager* SoundDataManager::GetInstance()
{
    return soundDataManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void SoundDataManager::DeleteInstance()
{
    delete(soundDataManager);
}