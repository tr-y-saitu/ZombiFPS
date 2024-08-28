#pragma once
#include "Common.h"
#include "SceneBase.h"

class Input;
class SoundManager;
class ImageDataManager;
class ModelDataManager;
class ClearSceneUI;

/// <summary>
/// クリアシーン
/// </summary>
class ClearScene : public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ClearScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ClearScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// シーンの更新処理
    /// </summary>
    /// <returns>次のシーンのアドレス</returns>
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

private:
    /// <summary>
    /// 入力更新
    /// </summary>
    void UpdateKeyState();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // リソース管理クラス
    ImageDataManager*   imageDataManager;   // 画像データ

    // 演出関連
    SoundManager*       soundManager;       // 音管理クラスのアドレス

    // 入力関係
    Input*              input;              // 入力判定処理
    bool                isKeyOn;            // キー入力されたか
    bool                isKeyRelease;       // キー入力が離れたか
    bool                isPreviousKeyOn;    // 前フレームでキー入力があったか

    // UI
    ClearSceneUI*       clearSceneUI;       // UI
};


