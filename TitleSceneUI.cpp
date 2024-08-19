#include "TitleSceneUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleSceneUI::TitleSceneUI()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleSceneUI::~TitleSceneUI()
{
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
}
