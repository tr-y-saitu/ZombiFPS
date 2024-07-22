#include "Common.h"
#include "ImageDataManager.h"

ImageDataManager* ImageDataManager::imageDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
ImageDataManager::ImageDataManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ImageDataManager::~ImageDataManager()
{
}

/// <summary>
/// インスタンスの作成
/// </summary>
void ImageDataManager::CreateInstance()
{
    if (imageDataManager == NULL)
    {
        imageDataManager = new ImageDataManager();
    }
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>画像データマネージャーのインスタンスのアドレス</returns>
ImageDataManager* ImageDataManager::GetInstance()
{
    return imageDataManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void ImageDataManager::DeleteInstance()
{
    delete(imageDataManager);
}