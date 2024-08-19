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


    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ImageDataManager* imageDataManager;     // 画像データ

    // ハンドル
    int vhsFilterImageHandle;       // VHS風のフィルター画像
    int recImageHandle;             // 録画風REC画像

    // ステータス
};

