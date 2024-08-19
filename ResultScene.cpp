#include "ResultScene.h"
#include "ResultSceneUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
    resultSceneUI = new ResultSceneUI();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
}

/// <summary>
/// 初期化
/// </summary>
void ResultScene::Initialize()
{

}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* ResultScene::UpdateScene()
{

    // オブジェクト更新
    resultSceneUI->Update();     // UIの更新

    // 現状のシーンを返す
    return this;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
    DrawUI();       // UIの描画
}

/// <summary>
/// UIの描画
/// </summary>
void ResultScene::DrawUI()
{
    resultSceneUI->Draw();
}

/// <summary>
/// 音の更新
/// </summary>
void ResultScene::UpdateSound()
{

}

/// <summary>
/// エフェクトの更新
/// </summary>
void ResultScene::UpdateEffect()
{

}
