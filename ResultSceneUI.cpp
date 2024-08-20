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
    // マウスの更新処理
    UpdateMouse();
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

    // 文字を描画
    DrawStringCenterScreen("Score", 190, FontColorVHS, vhsSmallFontHandle);

    // ハイスコア描画

    // スコア基準を描画
    DrawStringCenterScreen("Score  /  Kills  /  Round", 300, FontColorBlack, vhsSmallFontHandle);

    // 現在のスコアを描画
    DrawStringCenterScreen("2000  /  200  /  10", 500, FontColorBlack, vhsSmallFontHandle);

    // キーフレームの描画
    DrawKeyFrame();

    //「再挑戦しますか？」
    DrawStringCenterScreen("[ｻｲﾁｮｳｾﾝｼﾏｽｶ?]", 720, FontColorBlack, vhsJPLargeFontHandle);

    // マウスカーソルの描画
    DrawMouse();
}

/// <summary>
/// キーフレームの描画
/// </summary>
void ResultSceneUI::DrawKeyFrame()
{
    // 閉じるボタン描画
    DrawRotaGraph(1555, 215, DefaultExpansion, DefaultAngle, scoreBoardCloseButtonRed, true);

    // 入力キー描画「yes」
    DrawRotaGraph(750, 850, DefaultExpansion, DefaultAngle, checkKeyFrameDefaults, true);
    DrawStringToHandle(700, 820, "yes", FontColorBlack,vhsJPLargeFontHandle,true);

    // 入力キー描画「no」
    DrawRotaGraph(1200, 850, DefaultExpansion, DefaultAngle, checkKeyFrameDefaults, true);
    DrawStringToHandle(1170, 820, "no", FontColorBlack, vhsJPLargeFontHandle, true);

}

/// <summary>
/// マウスの更新処理
/// </summary>
void ResultSceneUI::UpdateMouse()
{
    input->UpdateMouseWithScreen();
}

/// <summary>
/// マウスカーソルの描画
/// </summary>
void ResultSceneUI::DrawMouse()
{
    // マウスの位置にマウスカーソルを描画
    Input::MousePosition mousePosition = input->GetMousePosition();
    DrawRotaGraph(mousePosition.x, mousePosition.y, DefaultExpansion, DefaultAngle, mouseCursorImageHandel, true);
}

/// <summary>
/// ２次元四角形当たり判定
/// </summary>
/// <param name="data1">四角形１</param>
/// <param name="data2">四角形２</param>
void ResultSceneUI::IsCollision2Box(ImageUIData data1, ImageUIData data2)
{
    
}
