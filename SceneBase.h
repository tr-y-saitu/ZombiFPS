#pragma once

/// <summary>
/// シーンクラスのベース
/// </summary>
class SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase();

    /// <summary>
    /// 最初のシーンの初期化
    /// </summary>
    /// <returns>初めに登録させるシーンのポインタ</returns>
    static SceneBase* InitializeBase();

    /// <summary>
    /// 初期化
    /// </summary>
    virtual void Initialize() abstract;

    /// <summary>
    /// シーン内の更新
    /// </summary>
    /// <returns></returns>
    virtual SceneBase* UpdateScene() abstract;

    /// <summary>
    /// サウンドの更新
    /// </summary>
    virtual void UpdateSound() abstract;

    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() abstract;   // 純粋仮想関数

    /// <summary>
    /// UIの描画
    /// </summary>
    virtual void DrawUI() abstract;

protected:

};

