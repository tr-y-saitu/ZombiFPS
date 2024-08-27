#include "TutorialSceneUI.h"
#include "ImageDataManager.h"
#include "TutorialScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
TutorialSceneUI::TutorialSceneUI()
{
    imageDataManager = ImageDataManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialSceneUI::~TutorialSceneUI()
{
}

/// <summary>
/// 初期化
/// </summary>
void TutorialSceneUI::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void TutorialSceneUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void TutorialSceneUI::Draw(int currentTutorialState)
{
    // 現在のチュートリアルの進行状況を描画
    char text[256];
    snprintf(text, sizeof(text), "%d / %d", currentTutorialState, TutorialScene::TutorialState::TutorialEnd);
    DrawFormatStringToHandle(200, 50, FontColorVHS, vhsJPLargeFontHandle, text);
}
