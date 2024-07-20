#pragma once
#include "SceneBase.h"
#include "TitleScene.h"

class FrameRateManager;
class EffectPlayManager;
class SoundPlayManager;
class Input;

/// <summary>
/// ゲーム全体の管理
/// </summary>
class Game final
{
public:
    enum SceneState
    {
        SceneTitle,     // タイトル
        SceneGame,      // ゲーム
        SceneResult     // リザルト
    };
    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Game();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Game();

    /// <summary>
    /// 実際のゲームループ
    /// </summary>
    void Update();

    /// <summary>
    /// シーンの切り替え
    /// </summary>
    void ChangeScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 入力処理
    /// </summary>
    void UpdateKeyState();

private:
    // 実行用シーン
    SceneBase* nowScene;                    // 現在のシーン
    SceneBase* nextScene;                   // 次のシーン

    // 管理クラス
    FrameRateManager* frameRateManager;     // フレームレート制御
    EffectPlayManager* effectPlayManager;   // エフェクト管理
    SoundPlayManager* soundPlayManager;     // サウンド管理
    Input* input;                           // 入力処理

    // キー入力
    bool    keyOn;                          // キー入力されているか
    bool    keyRelease;                     // キー入力が離れたか
    bool    prevKeyOn;                      // 前フレームでキー入力があったか
};

