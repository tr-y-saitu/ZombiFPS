#include "Common.h"
#include "ImageDataManager.h"

// 初期化
ImageDataManager* ImageDataManager::imageDataManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
ImageDataManager::ImageDataManager()
{
    // 画像データの読み込み
    ImageDataLoad();
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
    // 部屋番号
    imageDataList[West1ImageData]       = LoadGraph("Data/UI/RoomNumber/West1.png");
    imageDataList[West2ImageData]       = LoadGraph("Data/UI/RoomNumber/West2.png");
    imageDataList[West3ImageData]       = LoadGraph("Data/UI/RoomNumber/West3.png");
    imageDataList[West4ImageData]       = LoadGraph("Data/UI/RoomNumber/West4.png");
    imageDataList[Center1ImageData]     = LoadGraph("Data/UI/RoomNumber/Center1.png");
    imageDataList[Center2ImageData]     = LoadGraph("Data/UI/RoomNumber/Center2.png");
    imageDataList[Center3ImageData]     = LoadGraph("Data/UI/RoomNumber/Center3.png");
    imageDataList[Center4ImageData]     = LoadGraph("Data/UI/RoomNumber/Center4.png");
    imageDataList[East1ImageData]       = LoadGraph("Data/UI/RoomNumber/East1.png");
    imageDataList[East2ImageData]       = LoadGraph("Data/UI/RoomNumber/East2.png");
    imageDataList[East3ImageData]       = LoadGraph("Data/UI/RoomNumber/East3.png");
    imageDataList[East4ImageData]       = LoadGraph("Data/UI/RoomNumber/East4.png");
    imageDataList[VHSFiltersImageData]  = LoadGraph("Data/UI/Filter/VHSFileters10%.png");
    imageDataList[CrosshairImageData]   = LoadGraph("Data/UI/GameScene/Crosshair.png");
    imageDataList[RECImageData]         = LoadGraph("Data/UI/GameScene/RECImg.png");
    imageDataList[TitleLogo]            = LoadGraph("Data/UI/TitleScene/TitleLogo.png");
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
