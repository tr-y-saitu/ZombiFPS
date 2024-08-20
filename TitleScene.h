#pragma once
#include "SceneBase.h"
#include "TitleSceneUI.h"

class Input;
class Stage;
class EnemyGroup;
class ShutterController;
class SoundManager;
class EffectManager;
class SceneCamera;
class CollisionManager;
class ImageDataManager;
class ModelDataManager;


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

private:
    /// <summary>
    /// エネミーの更新
    /// </summary>
    void UpdateEnemy();

    /// <summary>
    /// 入力更新
    /// </summary>
    void UpdateKeyState();
    

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr VECTOR InitializeCameraPosition        = { -1.0f,10.0f,8.0f };   // 初期化時のカメラ座標
    static constexpr VECTOR InitializeCameraTargetPosition  = { -10.0f,5.0f,-10.0f };   // 初期時のカメラの視点座標

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // リソース管理クラス
    ImageDataManager*   imageDataManager;   // 画像データ
    ModelDataManager*   modelDataManager;  // モデルデータ

    // 当たり判定
    // FIXME:Enemyの動作で強制的に使用するため、
    //       当たり判定をせずともクラスの参照は持つ必要がある
    CollisionManager*   collisionManager;   // 当たり判定クラス

    // 演出関連
    SoundManager*       soundManager;       // 音管理クラスのアドレス
    EffectManager*      effectManager;      // エフェクト管理クラス

    // オブジェクト関連
    Stage*              stage;                  // ステージ
    ShutterController*  shutterController;      // シャッター
    EnemyGroup*         enemy;                  // エネミー
    VECTOR              enemyTargetPosition;    // エネミーが目指す移動座標

    // カメラ
    SceneCamera*        sceneCamera;

    // UI
    TitleSceneUI*       titleSceneUI;       // タイトルシーン用のUI

    // 入力関係
    Input*              input;              // 入力判定処理
    bool                isKeyOn;            // キー入力されたか
    bool                isKeyRelease;       // キー入力が離れたか
    bool                isPreviousKeyOn;    // 前フレームでキー入力があったか
};

