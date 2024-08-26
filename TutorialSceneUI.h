#pragma once
#include "SceneUIBase.h"

class ImageDataManager;

/// <summary>
/// チュートリアルシーンのUI
/// </summary>
class TutorialSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TutorialSceneUI();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TutorialSceneUI();

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
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//



    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    ImageDataManager* imageDataManager; // 画像管理クラス

};


