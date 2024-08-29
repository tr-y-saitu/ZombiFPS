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
    imageDataList[West1ImageData]               = LoadGraph("Data/UI/RoomNumber/West1.png");
    imageDataList[West2ImageData]               = LoadGraph("Data/UI/RoomNumber/West2.png");
    imageDataList[West3ImageData]               = LoadGraph("Data/UI/RoomNumber/West3.png");
    imageDataList[West4ImageData]               = LoadGraph("Data/UI/RoomNumber/West4.png");
    imageDataList[Center1ImageData]             = LoadGraph("Data/UI/RoomNumber/Center1.png");
    imageDataList[Center2ImageData]             = LoadGraph("Data/UI/RoomNumber/Center2.png");
    imageDataList[Center3ImageData]             = LoadGraph("Data/UI/RoomNumber/Center3.png");
    imageDataList[Center4ImageData]             = LoadGraph("Data/UI/RoomNumber/Center4.png");
    imageDataList[East1ImageData]               = LoadGraph("Data/UI/RoomNumber/East1.png");
    imageDataList[East2ImageData]               = LoadGraph("Data/UI/RoomNumber/East2.png");
    imageDataList[East3ImageData]               = LoadGraph("Data/UI/RoomNumber/East3.png");
    imageDataList[East4ImageData]               = LoadGraph("Data/UI/RoomNumber/East4.png");

    // ウェーブ
    imageDataList[Wave1ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave1.png");
    imageDataList[Wave2ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave2.png");
    imageDataList[Wave3ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave3.png");
    imageDataList[Wave4ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave4.png");
    imageDataList[Wave5ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave5.png");
    imageDataList[Wave6ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave6.png");
    imageDataList[Wave7ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave7.png");
    imageDataList[Wave8ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave8.png");
    imageDataList[Wave9ImageData]               = LoadGraph("Data/UI/GameScene/Wave/Wave9.png");
    imageDataList[WaveLastImageData]            = LoadGraph("Data/UI/GameScene/Wave/LastMini.png");

    // VHS
    imageDataList[VHSFiltersImageData]          = LoadGraph("Data/UI/Filter/VHSFileters10%.png");
    imageDataList[RECImageData]                 = LoadGraph("Data/UI/GameScene/RECImg.png");
    imageDataList[VHSNoiseFilters150]           = LoadGraph("Data/UI/Filter/VHS_Noise150%.png");
    imageDataList[VHSNoiseFilters200]           = LoadGraph("Data/UI/Filter/VHS_Noise200%.png");

    // 銃
    imageDataList[MP5PowerUpTexture]            = LoadGraph("Data/Gun/MP5/MP5PowerUpTexture.png");

    // アイコン
    imageDataList[IconGunPowerUpMachine]        = LoadGraph("Data/UI/GameScene/IconGunPowerUpText.png");
    imageDataList[IconAmmoBox]                  = LoadGraph("Data/UI/GameScene/IconAmmoBoxText.png");

    // タイトルシーン
    imageDataList[TitleLogo]                    = LoadGraph("Data/UI/TitleScene/TitleLogoEdge.png");

    // チュートリアルシーン
    imageDataList[MoveTutorialImageData]        = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage1.png");
    imageDataList[ShotTutorialImageData]        = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage2.png");
    imageDataList[InteractTutorialImageData]    = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage3.png");
    imageDataList[EnemyTutorialImageData]       = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage4.png");
    imageDataList[AmmoShutterTutorialImageData] = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage5.png");
    imageDataList[GunPowerUpTutorialImageData]  = LoadGraph("Data/UI/TutorialScene/TutorialImage/TutorialImage6.png");

    // ゲームシーン
    imageDataList[CrosshairImageData]           = LoadGraph("Data/UI/GameScene/Crosshair.png");
    imageDataList[HitFilter]                    = LoadGraph("Data/UI/GameScene/HitFilter.png");

    // リザルトシーン
    imageDataList[WindowsScoreNoTextImageData]  = LoadGraph("Data/UI/ResultScene/RetroWindowsGUI/WindowsScoreNoTextBig.png");
    imageDataList[WindowsCloseButtonRed]        = LoadGraph("Data/UI/ResultScene/RetroWindowsGUI/WindowsCloseButtonRedBig.png");
    imageDataList[WindowsKeyBlack]              = LoadGraph("Data/UI/ResultScene/RetroWindowsGUI/WindowsKeyBlack.png");
    imageDataList[WindowsKeyDefaults]           = LoadGraph("Data/UI/ResultScene/RetroWindowsGUI/WindowsKeyDefaults.png");
    imageDataList[MouseCursorImageData]         = LoadGraph("Data/UI/ResultScene/RetroWindowsGUI/MouseCursor.png");

    // クリアシーン
    imageDataList[ClearSceneBackImageData]      = LoadGraph("Data/UI/ClearScene/GoodEndBackImage.png");
    imageDataList[ClearSceneTextImageData]      = LoadGraph("Data/UI/ClearScene/GoodEndTextImag.png");

    // バッドエンド
    imageDataList[BadEndImageData]              = LoadGraph("Data/UI/GameScene/BadEndImage.png");
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
