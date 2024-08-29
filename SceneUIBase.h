#pragma once
#include "Common.h"


/// <summary>
/// シーンUIの基礎クラス
/// </summary>
class SceneUIBase
{
public:
    /// <summary>
    /// UIで使用する画像の情報
    /// </summary>
    struct ImageUIData
    {
        int     imageHandle;        // 画像ハンドル
        VECTOR  centerPosition;     // 画像を描画している中心座標
        float   width;              // 画像の幅
        float   height;             // 画像の高さ
        bool    isCollisionActive;  // 当たり判定をしてほしいかどうか
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneUIBase();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual~SceneUIBase();

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update();

    /// <summary>
    /// 描画
    /// </summary>
    /// MEMO:virtualにしていないのは各シーンで引数が異なるため
    void Draw();

    /// <summary>
    /// 文字を画面中央に描画する
    /// </summary>
    /// <param name="string">描画したい文字</param>
    /// <param name="drawPositionY">描画するY座標</param>
    /// <param name="uiColor">文字の色</param>
    /// <param name="fontHandle">自分で作成したフォントがあるなら、フォントハンドルを引数に追加</param>
    /// MEMO:数値も同時に描画したい場合はsnprintfを使い、
    ///      数値を代入後、第一引数に渡してください。
    void DrawStringCenterScreen(const char* string, int drawPositionY, int uiColor, int fontHandle = 0);

protected:
    /// <summary>
    /// ２次元四角形当たり判定
    /// </summary>
    /// <param name="data1">四角形１</param>
    /// <param name="data2">四角形２</param>
    bool IsCollision2Box(ImageUIData data1, ImageUIData data2);

    /// <summary>
    /// 現在時間の描画
    /// </summary>
    void DrawCurrentTime();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int OutlastFontSize        = 250;  // アウトラストフォントのサイズ
    static constexpr int OutlastFontThickness   = 2;    // アウトラストフォントの太さ
    const int            FontColorVHS           = GetColor(200, 200, 200);  // VHS風のフォントカラー
    const int            FontColorBlack         = GetColor(0, 0, 0);        // フォントカラー(黒)
    // 時刻
    static constexpr int VHSTimeDrawPositionX = 1400; // 時刻の描画X位置
    static constexpr int VHSTimeDrawPositionY = 50;   // 時刻の描画Y位置

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // ハンドル
    int outlastFontHandle;      // アウトラストに似たフォントハンドル
    int vhsLargeFontHandle;     // VHSフォントハンドル(大)
    int vhsSmallFontHandle;     // VHSフォントハンドル(小)
    int vhsJPLargeFontHandle;   // VHS日本語対応フォントハンドル(大)
    int vhsJPSmallFontHandle;   // VHS日本語対応フォントハンドル(小)
    int waveStateFontHandle;    // ウェーブの表示時に使用するフォントハンドル
};

