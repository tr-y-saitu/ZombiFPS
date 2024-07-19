#include "SceneBase.h"
#include "TitleScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
{
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
