#pragma once
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
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    SoundManager*       soundManager;       // サウンド管理クラス
    EffectManager*      effectManager;      // エフェクト管理クラス
    ImageDataManager*   imageDataManager;   // 画像管理クラス
    ModelDataManager*   modelDataManager;   // モデル管理クラス

    // 入力情報
    Input*              input;              // 入力判定

    // オブジェクト
    Stage*              stage;              // ステージ
    ShutterController*  shutterController;  // シャッター

    // カメラ
    SceneCamera*        sceneCamera;        // シーンカメラ

    // UI
    ResultSceneUI*      resultSceneUI;      // リザルトシーン用のUI

};



