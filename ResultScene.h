#pragma once
#include "Common.h"
#include "SceneBase.h"

class ResultSceneUI;
class Input;
class Stage;
class ShutterController;
class SoundManager;
class EffectManager;
class SceneCamera;
class ImageDataManager;
class ModelDataManager;

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene : public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ResultScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// シーンのアップデート
    /// </summary>
    /// <returns>次のシーンのポインタ</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UIの描画
    /// </summary>
    void DrawUI() override;

    /// <summary>
    /// サウンドの更新
    /// </summary>
    void UpdateSound();

    /// <summary>
    /// エフェクトの更新
    /// </summary>
    void UpdateEffect();

private:
    /// <summary>
    /// 入力更新
    /// </summary>
    void UpdateKeyState();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr VECTOR CameraInitializePosition        = { -1.0f,10.0f,8.0f };     // 初期化時のカメラ座標
    static constexpr VECTOR CameraTargetInitializePosition  = { -10.0f,5.0f,-10.0f };   // 初期化時のカメラ視点座標

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    SoundManager*       soundManager;       // サウンド管理クラス
    EffectManager*      effectManager;      // エフェクト管理クラス
    ImageDataManager*   imageDataManager;   // 画像管理クラス
    ModelDataManager*   modelDataManager;   // モデル管理クラス

    // オブジェクト
    Stage*              stage;              // ステージ
    ShutterController*  shutterController;  // シャッター

    // カメラ
    SceneCamera*        sceneCamera;        // シーンカメラ

    // UI
    ResultSceneUI*      resultSceneUI;      // リザルトシーン用のUI

    // 入力情報
    Input*              input;              // 入力判定
    bool                isKeyOn;            // キー入力されたか
    bool                isKeyRelease;       // キー入力が離れたか
    bool                isPreviousKeyOn;    // 前フレームでキー入力があったか
};



