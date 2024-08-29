#include "ClearSceneUI.h"
#include "ImageDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ClearSceneUI::ClearSceneUI()
    : frameCount            (0)
{
    // 画像ハンドルクラスのアドレスをもらう
    imageDataManager = ImageDataManager::GetInstance();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ClearSceneUI::~ClearSceneUI()
{
    // 処理なし
}

/// <summary>
/// 初期化
/// </summary>
void ClearSceneUI::Initialize()
{
    // 画像ハンドルの取得
    goodEndBackImageHandle  = imageDataManager->GetImageHandle(ImageDataManager::ClearSceneBackImageData);
    goodEndTextImageHandle  = imageDataManager->GetImageHandle(ImageDataManager::ClearSceneTextImageData);

    // 画像のハンドルの座標初期化
    goodEndTextPosition = VGet(ScreenWidthHalf, ScreenHeight, 0);
}

/// <summary>
/// 更新
/// </summary>
void ClearSceneUI::Update()
{
    // フレームカウントの更新
    frameCount++;

    // 文字画像を徐々に上に上げる
    int textPositionY = frameCount;
    if (textPositionY >= ScreenHeightHalf)
    {
        textPositionY = ScreenHeightHalf;
    }
    goodEndTextPosition.y = ScreenHeight - textPositionY;
}

/// <summary>
/// 描画
/// </summary>
void ClearSceneUI::Draw()
{
    // 背景画像描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf,
        DefaultExpansion, DefaultAngle, goodEndBackImageHandle, true);

    // 文字画像を描画
    DrawRotaGraph(goodEndTextPosition.x, goodEndTextPosition.y,
        DefaultExpansion, DefaultAngle, goodEndTextImageHandle, true);
}
