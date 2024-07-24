#include "Common.h"
#include "ImageDataManager.h"

// 初期化
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
    // 画像データの削除
    for (int i = 0; i < imageDataList.size(); i++)
    {
        if (imageDataList[(ImageDataType)i])
        {
            DeleteGraph(imageDataList[(ImageDataType)i]);
        }
    }
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

/// <summary>
/// 画像データの読み込み
/// </summary>
void ImageDataManager::ImageDataLoad()
{

}

/// <summary>
/// 使用したい画像データを取得する
/// </summary>
/// <param name="type">データの種類</param>
/// <returns>データハンドル</returns>
int ImageDataManager::GetImageHandle(ImageDataType type)
{
    return imageDataList[type];
}