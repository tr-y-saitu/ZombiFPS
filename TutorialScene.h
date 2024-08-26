#pragma once
#include "Common.h"
#include "SceneBase.h"


class Input;
class SoundManager;
class EffectManager;
class SceneCamera;
class CollisionManager;
class ImageDataManager;
class ModelDataManager;
class TutorialSceneUI;

/// <summary>
/// チュートリアルシーン
/// </summary>
class TutorialScene : public SceneBase
{
public:
    /// <summary>
    /// チュートリアルの進行状態
    /// </summary>
    enum TutorialState
    {
        MoveTutorial,       // 移動チュートリアル
        ShotTutorial,       // 射撃チュートリアル
        InteractTutorial,   // インタラクトチュートリアル
        EnemyTutorial,      // エネミーチュートリアル
        TutorialEnd,        // チュートリアル終了
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    TutorialScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TutorialScene();

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
    ImageDataManager* imageDataManager;   // 画像データ
    ModelDataManager* modelDataManager;  // モデルデータ

    // 当たり判定
    // FIXME:Enemyの動作で強制的に使用するため、
    //       当たり判定をせずともクラスの参照は持つ必要がある
    CollisionManager* collisionManager;   // 当たり判定クラス

    // 演出関連
    SoundManager* soundManager;       // 音管理クラスのアドレス
    EffectManager* effectManager;      // エフェクト管理クラス

    // カメラ
    SceneCamera* sceneCamera;

    // UI
    TutorialSceneUI* tutorialSceneUI;

    // 入力関係
    Input* input;              // 入力判定処理
    bool                isKeyOn;            // キー入力されたか
    bool                isKeyRelease;       // キー入力が離れたか
    bool                isPreviousKeyOn;    // 前フレームでキー入力があったか

    // ステータス
    TutorialState       currentTutorialState;

    // 画像ハンドル
    map<TutorialState, int> tutorialImageHandleList;
};



