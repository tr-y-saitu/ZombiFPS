#pragma once
#include "SceneUIBase.h"

class ImageDataManager;
class Input;

/// <summary>
/// リザルトシーンのUI
/// </summary>
class ResultSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultSceneUI();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ResultSceneUI();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    /// <summary>
    /// キー入力文字を点滅描画させる
    /// </summary>
    void DrawBlinkingTextKeyInfomation();

    /// <summary>
    /// スコアボードの描画
    /// </summary>
    void DrawScoreBoard();


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // テキスト「ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ」
    static constexpr int KeyInformationTextBlinkInterval    = 800;      // 文字の点滅間隔
    static constexpr int KeyInformationTextPositionY        = 800;      // 「ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ」の描画Y位置


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス　
    ImageDataManager*   imageDataManager;               // 画像データ

    // 入力
    Input*              input;                          // 入力処理

    // キー入力文字
    bool                isVisibleKeyInfomation;         // キー入力文字が表示されているかどうか
    int                 keyInfomationPreviousTime;      // キー入力文字が前回表示された時間

    // 画像ハンドル
    int                 scoreBoardImageHandel;          // スコアボードの画像ハンドル
    int                 scoreBoardCloseButtonRed;       // スコアボードを閉じるボタン(赤色)
    int                 checkKeyFrameBlack;             // キーの入力画像(赤色)
    int                 checkKeyFrameDefaults;          // キーの入力画像(デフォルト)
    int                 mouseCursorImageHandel;         // マウスカーソルの画像ハンドル
};


