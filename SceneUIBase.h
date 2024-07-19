#pragma once

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

};

