#include "SceneBase.h"
#include "TitleScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
{
    // 霧の初期化
    InitializeFog();
}

/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
}

/// <summary>
/// ベースの初期化
/// </summary>
/// <returns>最初に始めるシーンのポインタ</returns>
SceneBase* SceneBase::InitializeBase()
{
    return new TitleScene();
}

/// <summary>
/// 初期化
/// </summary>
void SceneBase::Initialize()
{

}

/// <summary>
/// 霧の初期化
/// </summary>
void SceneBase::InitializeFog()
{
    // 霧を有効化する
    SetFogEnable(true);

    // 霧の色を指定
    SetFogColor(50, 50, 50);

    // 霧の開始距離、終了距離を設定
    SetFogStartEnd(0.0f, 50.0f);
}
