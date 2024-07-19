#include "Common.h"
#include "GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
    gameSceneUI = GameSceneUI();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize()
{

}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* GameScene::UpdateScene()
{
    // テスト描画
    DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene", true);


    // オブジェクト更新
    gameSceneUI.Update();       // UIの更新

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
    DrawUI();   // UIの描画
}

/// <summary>
/// UIの描画
/// </summary>
void GameScene::DrawUI()
{
    gameSceneUI.Draw();
}

/// <summary>
/// 音の更新
/// </summary>
void GameScene::UpdateSound()
{

}

/// <summary>
/// エフェクトの更新
/// </summary>
void GameScene::UpdateEffect()
{

}