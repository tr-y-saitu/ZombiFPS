#include "Common.h"
#include "TitleSceneUI.h"
#include "ImageDataManager.h"
#include <ctime>
#include <iomanip>
#include <sstream>


/// <summary>
/// コンストラクタ
/// </summary>
TitleSceneUI::TitleSceneUI()
{
    imageDataManager = ImageDataManager::GetInstance();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleSceneUI::~TitleSceneUI()
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleSceneUI::Initialize()
{
    vhsFilterImageHandle = imageDataManager->GetImageHandle(ImageDataManager::VHSFiltersImageData);
    recImageHandle = imageDataManager->GetImageHandle(ImageDataManager::RECImageData);
}

/// <summary>
/// 更新
/// </summary>
void TitleSceneUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void TitleSceneUI::Draw()
{
    // テスト描画
    DrawString(0, 0, "Title", GetColor(255, 255, 255), true);

    // ビデオ風の情報描画
    DrawVHSInformation();
}

/// <summary>
/// ビデオ風の情報を描画
/// </summary>
void TitleSceneUI::DrawVHSInformation()
{
    // VHS風のフィルターを描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, 1, 0, vhsFilterImageHandle, true);

    // 録画文字を描画
    DrawRotaGraph(150, 100, 1, 0, recImageHandle, true);

    // 現在時刻を描画
    DrawCurrentTime();

}

/// <summary>
/// 現在時間の描画
/// </summary>
void TitleSceneUI::DrawCurrentTime()
{
    // 日付時刻
    // 現在時刻を取得
    time_t now = time(NULL);
    tm localTime;
    localtime_s(&localTime, &now);

    // 時刻を文字列に変換
    char timeString[256];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &localTime);

    // 時刻を描画
    DrawFormatStringToHandle(1400, 50, GetColor(200, 200, 200), vhsSmallFontHandle, "%s", timeString);


}
