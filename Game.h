#pragma once
#include "SceneBase.h"
#include "TitleScene.h"

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
    SceneBase* nowScene;            // 現在のシーン
    SceneBase* nextScene;           // 次のシーン


    // キー入力
    bool    keyOn;                  // キー入力されているか
    bool    keyRelease;             // キー入力が離れたか
    bool    prevKeyOn;              // 前フレームでキー入力があったか
};

