#include "SceneUIBase.h"
#include "ImageDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneUIBase::SceneUIBase()
{
    // フォントを作成
    // アウトラスト風フォント
    outlastFontHandle = CreateFontToHandle("Outlast 2 Game Font", OutlastFontSize,
        OutlastFontThickness, DX_FONTTYPE_EDGE);

    // VHS風フォント
    vhsFontHandle = CreateFontToHandle("VCR OSD Mono", 100, 2, DX_FONTTYPE_NORMAL);
}

/// <summary>
/// デストラクタ
/// </summary>
SceneUIBase::~SceneUIBase()
{
}

/// <summary>
/// 更新
/// </summary>
void SceneUIBase::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void SceneUIBase::Draw()
{

}
