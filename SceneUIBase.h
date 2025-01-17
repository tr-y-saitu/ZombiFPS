﻿#pragma once
#include "Common.h"


/// <summary>
/// シーンUIの基礎クラス
/// </summary>
class SceneUIBase
{
public:
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
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int OutlastFontSize        = 250;  // アウトラストフォントのサイズ
    static constexpr int OutlastFontThickness   = 2;    // アウトラストフォントの太さ

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // ハンドル
    int outlastFontHandle;      // アウトラストに似たフォントハンドル
    int vhsLargeFontHandle;     // VHSフォントハンドル(大)
    int vhsSmallFontHandle;     // VHSフォントハンドル(小)
    int vhsJPLargeFontHandle;   // VHS日本語対応フォントハンドル(大)
    int vhsJPSmallFontHandle;   // VHS日本語対応フォントハンドル(小)

};

