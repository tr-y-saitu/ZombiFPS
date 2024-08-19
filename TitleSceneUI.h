#pragma once
#include "SceneUIBase.h"

class ImageDataManager;

/// <summary>
/// タイトルシーンのUI
/// </summary>
class TitleSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TitleSceneUI();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TitleSceneUI();

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
    /// ビデオ風の情報を描画
    /// </summary>
    void DrawVHSInformation();

    /// <summary>
    /// 現在時間の描画
    /// </summary>
    void DrawCurrentTime();

    /// <summary>
    /// キー入力文字を点滅描画させる
    /// </summary>
    void DrawBlinkingTextKeyInfomation();


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int KeyInformationTextBlinkInterval    = 500;  // 文字の点滅間隔
    static constexpr int KeyInformationTextPositionY        = 800;  // 「ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ」の描画Y位置

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ImageDataManager* imageDataManager;     // 画像データ

    // ハンドル
    int vhsFilterImageHandle;       // VHS風のフィルター画像
    int recImageHandle;             // 録画風REC画像
    int vhsTitleFontHandle;         // VHS風のタイトル用フォントハンドル
    int titleLogo;                  // タイトルロゴ画像

    // ステータス
    bool isVisibleKeyInfomation;    // キー入力文字が表示されているかどうか
    int  keyInfomationPreviousTime; // キー入力文字が前回表示された時間
};

