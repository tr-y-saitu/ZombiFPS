#pragma once
#include "SceneUIBase.h"

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
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:

};

