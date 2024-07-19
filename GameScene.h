#pragma once
#include "SceneBase.h"
#include "GameSceneUI.h"

/// <summary>
///  ゲームシーン
/// </summary>
class GameScene : public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameScene();

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
    // 定数

    // 変数
    GameSceneUI gameSceneUI;        // ゲームシーン用のUI

};


