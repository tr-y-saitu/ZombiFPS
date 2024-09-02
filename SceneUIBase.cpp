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

    // VHS風フォント(大)
    vhsLargeFontHandle = CreateFontToHandle("VCR OSD Mono", 100, 2, DX_FONTTYPE_NORMAL);

    // VHS風フォント(小)
    vhsSmallFontHandle = CreateFontToHandle("VCR OSD Mono", 50, 2, DX_FONTTYPE_NORMAL);

    // VHS風日本語対応フォント(大)
    vhsJPLargeFontHandle = CreateFontToHandle("VCR-JP Regular", 50, 2, DX_FONTTYPE_NORMAL);

    // VHS風日本語対応フォント(小)
    vhsJPSmallFontHandle = CreateFontToHandle("VCR-JP Regular", 25, 2, DX_FONTTYPE_NORMAL);
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

/// <summary>
/// 文字を画面中央に描画する
/// </summary>
/// <param name="string">描画したい文字</param>
/// <param name="drawPositionY">描画するY座標</param>
/// <param name="uiColor">文字の色</param>
/// <param name="fontHandle">自分で作成したフォントがあるなら、フォントハンドルを引数に追加</param>
/// MEMO:数値も同時に描画したい場合はsnprintfを使い、
///      数値を代入後、第一引数に渡してください。
void SceneUIBase::DrawStringCenterScreen(const char* string, int drawPositionY, int uiColor, int fontHandle)
{
    // 文字列の長さを取得
    int stringLength = strlen(string);

    // 文字列の描画幅を取得
    int stringWidth = GetDrawStringWidth(string, stringLength);

    // 描画する座標を設定
    int drawPositionX = ScreenWidthHalf - (stringWidth / 2);

    // フォントハンドルがあるかどうか
    if (fontHandle)
    {
        // 指定フォントで描画
        DrawStringToHandle(drawPositionX, drawPositionY, string, uiColor, fontHandle);
    }
    else
    {
        // デフォルトフォントで描画
        DrawFormatString(drawPositionX, drawPositionY, uiColor, string);
    }
}
