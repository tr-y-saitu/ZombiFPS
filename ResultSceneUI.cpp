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
    , nextState                     (SceneBase::SceneState::Same)
    , vhsNoiseCounter               (0)
{
    // 画像管理クラス
    imageDataManager = ImageDataManager::GetInstance();

    // 入力処理
    input = new Input();

    // 初期化
    Initialize();
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="score">スコア</param>
/// <param name="killCount">エネミーを殺した数</param>
/// <param name="waveCount">終了した時点でのウェーブ数</param>
ResultSceneUI::ResultSceneUI(int setScore, int setKillCount, int setWaveCount)
    : isVisibleKeyInfomation        (false)
    , keyInfomationPreviousTime     (GetNowCount())
    , nextState                     (SceneBase::SceneState::Same)
    , vhsNoiseCounter               (0)
    , score                         (setScore)
    , killCount                     (setKillCount)
    , waveCount                     (setWaveCount)
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
    vhsNoiseCounter = 0;

    // 画像ハンドルの読み込み
    scoreBoardImageHandel       = imageDataManager->GetImageHandle(ImageDataManager::WindowsScoreNoTextImageData);
    scoreBoardCloseButtonRed    = imageDataManager->GetImageHandle(ImageDataManager::WindowsCloseButtonRed);
    checkKeyFrameBlack          = imageDataManager->GetImageHandle(ImageDataManager::WindowsKeyBlack);
    checkKeyFrameDefaults       = imageDataManager->GetImageHandle(ImageDataManager::WindowsKeyDefaults);
    mouseCursorImageHandel      = imageDataManager->GetImageHandle(ImageDataManager::MouseCursorImageData);
    vhsNoiseFilters150          = imageDataManager->GetImageHandle(ImageDataManager::VHSNoiseFilters150);
    vhsNoiseFilters200          = imageDataManager->GetImageHandle(ImageDataManager::VHSNoiseFilters200);

    // 画像データを取得
    // マウスカーソル
    mouseCursorData.imageHandle                 = imageDataManager->GetImageHandle(ImageDataManager::MouseCursorImageData);
    GetGraphSizeF(mouseCursorData.imageHandle, &mouseCursorData.width, &mouseCursorData.height);
    mouseCursorData.centerPosition.x = MouseCursorInitializePositionX;
    mouseCursorData.centerPosition.y = MouseCursorInitializePositionY;

    // キーフレームブラック
    yesKeyFrameData.imageHandle = checkKeyFrameDefaults;
    GetGraphSizeF(yesKeyFrameData.imageHandle, &yesKeyFrameData.width, &yesKeyFrameData.height);
    yesKeyFrameData.centerPosition.x = YesKeyFrameDrawPositionX;
    yesKeyFrameData.centerPosition.y = YesKeyFrameDrawPositionY;

    // キーフレームデフォルト
    noKeyFrameData.imageHandle = checkKeyFrameDefaults;
    GetGraphSizeF(noKeyFrameData.imageHandle, &noKeyFrameData.width, &noKeyFrameData.height);
    noKeyFrameData.centerPosition.x = NoKeyFrameDrawPositionX;
    noKeyFrameData.centerPosition.y = NoKeyFrameDrawPositionY;

    // 閉じるボタン
    scoreBoardCloseButtonRedData.imageHandle    = imageDataManager->GetImageHandle(ImageDataManager::WindowsCloseButtonRed);
    GetGraphSizeF(scoreBoardCloseButtonRedData.imageHandle, &scoreBoardCloseButtonRedData.width, &scoreBoardCloseButtonRedData.height);
    scoreBoardCloseButtonRedData.centerPosition.x = ScoreBoardCloseButtonRedDrawPositionX;
    scoreBoardCloseButtonRedData.centerPosition.y = ScoreBoardCloseButtonRedDrawPositionY;
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
    // VHS風のノイズを描画
    DrawVHSNoise();

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
        DrawStringCenterScreen("[ｻｲﾁｮｳｾﾝｼﾏｽｶ?]", KeyInformationTextPositionY, FontColorBlack, vhsJPLargeFontHandle);
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
    DrawStringCenterScreen("Score", ScoreDrawPositionY, FontColorVHS, vhsSmallFontHandle);

    // ハイスコア描画

    // スコア基準を描画
    DrawStringCenterScreen("Score  /  Kills  /  Round", ScoreBaseDrawPositionY, FontColorBlack, vhsSmallFontHandle);

    // 現在のスコアを描画
    char scoreText[256];
    snprintf(scoreText, sizeof(scoreText), "  %d  /  %d  /  %d  ", score, killCount, waveCount);
    DrawStringCenterScreen(scoreText, NowScoreDrawPositionY, FontColorBlack, vhsSmallFontHandle);

    // キーフレームの描画
    DrawKeyFrame();

    //「再挑戦しますか？」
    // キー入力指示を描画
    DrawBlinkingTextKeyInfomation();

    // マウスカーソルの描画
    DrawMouse();
}

/// <summary>
/// キーフレームの描画
/// </summary>
void ResultSceneUI::DrawKeyFrame()
{
    // 閉じるボタン描画
    if (IsCollision2Box(mouseCursorData, scoreBoardCloseButtonRedData))
    {
        DrawRotaGraph(scoreBoardCloseButtonRedData.centerPosition.x, scoreBoardCloseButtonRedData.centerPosition.y,
            DefaultExpansion, DefaultAngle, scoreBoardCloseButtonRed, true);

        // 左クリックされたら
        if (input->GetMouseCurrentFrameInput() & MOUSE_INPUT_LEFT)
        {
            // シーン切り替え指示を出す
            nextState = SceneBase::SceneState::Title;
        }
    }

    // 入力キー描画「yes」
    if (IsCollision2Box(mouseCursorData, yesKeyFrameData))
    {
        DrawRotaGraph(yesKeyFrameData.centerPosition.x,yesKeyFrameData.centerPosition.y,
            DefaultExpansion, DefaultAngle, checkKeyFrameBlack, true);

        // 左クリックされたら
        if (input->GetMouseCurrentFrameInput() & MOUSE_INPUT_LEFT)
        {
            // シーン切り替え指示を出す
            nextState = SceneBase::SceneState::Game;
        }
    }
    else
    {
        DrawRotaGraph(yesKeyFrameData.centerPosition.x, yesKeyFrameData.centerPosition.y,
            DefaultExpansion, DefaultAngle, checkKeyFrameDefaults, true);
    }
    DrawStringToHandle(YesTextDrawPositionX, YesTextDrawPositionY,
        "yes", FontColorBlack,vhsJPLargeFontHandle,true);


    // 入力キー描画「no」
    if (IsCollision2Box(mouseCursorData, noKeyFrameData))
    {
        DrawRotaGraph(noKeyFrameData.centerPosition.x, noKeyFrameData.centerPosition.y,
            DefaultExpansion, DefaultAngle, checkKeyFrameBlack, true);

        // 左クリックされたら
        if (input->GetMouseCurrentFrameInput() & MOUSE_INPUT_LEFT)
        {
            // シーン切り替え指示を出す
            nextState = SceneBase::SceneState::Title;
        }
    }
    else
    {
        DrawRotaGraph(noKeyFrameData.centerPosition.x, noKeyFrameData.centerPosition.y,
            DefaultExpansion, DefaultAngle, checkKeyFrameDefaults, true);
    }
    DrawStringToHandle(NoTextDrawPositionX, NoTextDrawPositionY,
        "no", FontColorBlack, vhsJPLargeFontHandle, true);
}

/// <summary>
/// マウスの更新処理
/// </summary>
void ResultSceneUI::UpdateMouse()
{
    // マウスの更新
    input->UpdateMouseWithScreen();

    // 当たり判定処理
    UpdateCollision();
}

/// <summary>
/// マウスカーソルの描画
/// </summary>
void ResultSceneUI::DrawMouse()
{
    // マウス位置を取得
    Input::MousePosition mousePosition = input->GetMousePosition();
    mouseCursorData.centerPosition.x = mousePosition.x;
    mouseCursorData.centerPosition.y = mousePosition.y;

    // マウスの位置にマウスカーソルを描画
    DrawRotaGraph(mouseCursorData.centerPosition.x, mouseCursorData.centerPosition.y,
        DefaultExpansion, DefaultAngle, mouseCursorData.imageHandle, true);
}

/// <summary>
/// VHS風のノイズを描画
/// </summary>
void ResultSceneUI::DrawVHSNoise()
{
    // 交互にノイズ画像を描画
    if (vhsNoiseCounter % VHSNoiseFilterResponseRate == 0)
    {
        DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle, vhsNoiseFilters150, true);
    }
    else
    {
        DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle, vhsNoiseFilters200, true);
    }

    // カウントを進める
    vhsNoiseCounter++;
}

/// <summary>
/// 当たり判定の更新
/// </summary>
void ResultSceneUI::UpdateCollision()
{
    // マウスとオブジェクトの当たり判定を行う

    // マウスとウィンドウ閉じるボタン
    if (IsCollision2Box(mouseCursorData, scoreBoardCloseButtonRedData))
    {
        int i = 0;
    }
}
