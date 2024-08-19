#include "Common.h"
#include "TitleSceneUI.h"
#include "ImageDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleSceneUI::TitleSceneUI()
    : isVisibleKeyInfomation        (false)
    , keyInfomationPreviousTime     (GetNowCount())
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
    // フォントを作成
    vhsTitleFontHandle = CreateFontToHandle("VCR OSD Mono", 300, 2, DX_FONTTYPE_EDGE,true);

    // モデルハンドルを取得
    vhsFilterImageHandle    = imageDataManager->GetImageHandle(ImageDataManager::VHSFiltersImageData);
    recImageHandle          = imageDataManager->GetImageHandle(ImageDataManager::RECImageData);
    titleLogo               = imageDataManager->GetImageHandle(ImageDataManager::TitleLogo);
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
    // ビデオ風の情報描画
    DrawVHSInformation();

    // キー入力指示を描画
    DrawBlinkingTextKeyInfomation();
}

/// <summary>
/// ビデオ風の情報を描画
/// </summary>
void TitleSceneUI::DrawVHSInformation()
{
    // タイトルロゴを描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle, titleLogo, true);

    // VHS風のフィルターを描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle , vhsFilterImageHandle, true);

    // 録画文字を描画
    DrawRotaGraph(RECDrawPositionX, RECDrawPositionY, DefaultExpansion, DefaultAngle, recImageHandle, true);

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
    DrawFormatStringToHandle(VHSTimeDrawPositionX, VHSTimeDrawPositionY, FontColorVHS,
        vhsSmallFontHandle, "%s", timeString);
}

/// <summary>
/// キー入力文字を点滅描画させる
/// </summary>
void TitleSceneUI::DrawBlinkingTextKeyInfomation()
{
    int currentTime = GetNowCount();

    if (currentTime - keyInfomationPreviousTime >= KeyInformationTextBlinkInterval)
    {
        isVisibleKeyInfomation = !isVisibleKeyInfomation;   // 表示フラグを反転
        keyInfomationPreviousTime = currentTime;            // 前回表示した時間を更新
    }

    // 文字を描画
    if (isVisibleKeyInfomation)
    {
        DrawStringCenterScreen("ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ", KeyInformationTextPositionY, FontColorVHS, vhsJPLargeFontHandle);
    }
}
