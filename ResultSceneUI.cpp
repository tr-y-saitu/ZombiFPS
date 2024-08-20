#include "Common.h"
#include "ResultSceneUI.h"
#include "ImageDataManager.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultSceneUI::ResultSceneUI()
    : isVisibleKeyInfomation        (false)
    , keyInfomationPreviousTime     (GetNowCount())
{
    // 画像管理クラス
    imageDataManager = ImageDataManager::GetInstance();

    // 入力処理
    input = new Input();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultSceneUI::~ResultSceneUI()
{
}

/// <summary>
/// 初期化
/// </summary>
void ResultSceneUI::Initialize()
{
    // 初期化
    isVisibleKeyInfomation = false;
    keyInfomationPreviousTime = GetNowCount();

    // 画像ハンドルの読み込み
    scoreBoardImageHandel       = imageDataManager->GetImageHandle(ImageDataManager::WindowsScoreNoTextImageData);
    scoreBoardCloseButtonRed    = imageDataManager->GetImageHandle(ImageDataManager::WindowsCloseButtonRed);
    checkKeyFrameBlack          = imageDataManager->GetImageHandle(ImageDataManager::WindowsKeyBlack);
    checkKeyFrameDefaults       = imageDataManager->GetImageHandle(ImageDataManager::WindowsKeyDefaults);
    mouseCursorImageHandel      = imageDataManager->GetImageHandle(ImageDataManager::MouseCursorImageData);
}

/// <summary>
/// 更新
/// </summary>
void ResultSceneUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void ResultSceneUI::Draw()
{
    // キー入力指示を描画
    DrawBlinkingTextKeyInfomation();

    // スコアボードの描画
    DrawScoreBoard();
}

/// <summary>
/// キー入力文字を点滅描画させる
/// </summary>
void ResultSceneUI::DrawBlinkingTextKeyInfomation()
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
        DrawStringCenterScreen("[Space]ｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ", KeyInformationTextPositionY, FontColorVHS, vhsJPLargeFontHandle);
    }
}

/// <summary>
/// スコアボードの描画
/// </summary>
void ResultSceneUI::DrawScoreBoard()
{
    // スコアボードの描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle, scoreBoardImageHandel, true);
}
