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

    // ウェーブの表示時に使用するフォント
    waveStateFontHandle = CreateFontToHandle("VCR OSD Mono", 100, 2, DX_FONTTYPE_NORMAL);
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
    int stringWidth;

    // フォントハンドルがある場合
    if (fontHandle)
    {
        // 指定フォントの文字の描画幅を得る
        stringWidth = GetDrawFormatStringWidthToHandle(fontHandle, string);
    }
    else
    {
        // デフォルトフォントの文字描画幅を得る
        stringWidth = GetDrawStringWidth(string, stringLength);
    }

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

/// <summary>
/// ２次元四角形当たり判定
/// </summary>
/// <param name="data1">四角形１</param>
/// <param name="data2">四角形２</param>
bool SceneUIBase::IsCollision2Box(ImageUIData data1, ImageUIData data2)
{
    // どちらかの四角形が当たり判定を持たない場合は衝突しない
    /*if (!data1.isCollisionActive || !data2.isCollisionActive)
    {
        return false;
    }*/

    // 四角形1の左、右、上、下の座標を計算
    float data1Left = data1.centerPosition.x - data1.width / 2.0f;
    float data1Right = data1.centerPosition.x + data1.width / 2.0f;
    float data1Top = data1.centerPosition.y - data1.height / 2.0f;
    float data1Bottom = data1.centerPosition.y + data1.height / 2.0f;

    // 四角形2の左、右、上、下の座標を計算
    float data2Left = data2.centerPosition.x - data2.width / 2.0f;
    float data2Right = data2.centerPosition.x + data2.width / 2.0f;
    float data2Top = data2.centerPosition.y - data2.height / 2.0f;
    float data2Bottom = data2.centerPosition.y + data2.height / 2.0f;

    // 軸平行境界ボックス(AABB)での衝突判定
    // どれかの軸で完全に分離していれば衝突していない
    if (data1Left > data2Right || data1Right < data2Left ||
        data1Top > data2Bottom || data1Bottom < data2Top)
    {
        return false;
    }

    // どの軸でも分離していなければ衝突している
    return true;
}

/// <summary>
/// 現在時間の描画
/// </summary>
void SceneUIBase::DrawCurrentTime()
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
