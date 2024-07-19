#pragma once
#include "SceneUIBase.h"

/// <summary>
/// ゲームシーンのUI
/// </summary>
class GameSceneUI : public SceneUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSceneUI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameSceneUI();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

};


