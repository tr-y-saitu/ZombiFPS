#pragma once
#include "SceneBase.h"
#include "TitleSceneUI.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TitleScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TitleScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// シーンの更新処理
    /// </summary>
    /// <returns>次のシーンのポインタ</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// 音の更新
    /// </summary>
    void UpdateSound() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UIの描画
    /// </summary>
    void DrawUI();

    /// <summary>
    /// 入力更新
    /// </summary>
    void UpdateKeyState();

private:
    // 定数

    // 変数
    TitleSceneUI titleSceneUI;          // タイトルシーン用のUI


    // 入力関係
    bool    isKeyOn;                    // キー入力されたか
    bool    isKeyRelease;               // キー入力が離れたか
    bool    isPreviousKeyOn;            // 前フレームでキー入力があったか
};

