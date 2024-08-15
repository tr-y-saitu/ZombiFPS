#pragma once
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

protected:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int OutlastFontSize        = 100;  // アウトラストフォントのサイズ
    static constexpr int OutlastFontThickness   = 2;    // アウトラストフォントの太さ

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    int outlastFontHandle;      // アウトラストに似たフォントハンドル

};

