#include "Common.h"
#include "ResultSceneUI.h"
#include "ImageDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultSceneUI::ResultSceneUI()
    : isVisibleKeyInfomation        (false)
    , keyInfomationPreviousTime     (GetNowCount())
{
    // 画像管理クラス
    imageDataManager = ImageDataManager::GetInstance();

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
