#pragma once
#include "SceneUIBase.h"

/// <summary>
/// �Q�[���V�[����UI
/// </summary>
class GameSceneUI : public SceneUIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSceneUI();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~GameSceneUI();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

};


