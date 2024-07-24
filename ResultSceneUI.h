#pragma once
#include "SceneUIBase.h"

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
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:

};


