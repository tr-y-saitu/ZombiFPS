#include "Common.h"
#include "GameScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
    gameSceneUI = GameSceneUI();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{

}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <returns>���̃V�[���̃|�C���^</returns>
SceneBase* GameScene::UpdateScene()
{
    // �e�X�g�`��
    DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene", true);


    // �I�u�W�F�N�g�X�V
    gameSceneUI.Update();       // UI�̍X�V

    // ����̃V�[����Ԃ�
    return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
    DrawUI();   // UI�̕`��
}

/// <summary>
/// UI�̕`��
/// </summary>
void GameScene::DrawUI()
{
    gameSceneUI.Draw();
}

/// <summary>
/// ���̍X�V
/// </summary>
void GameScene::UpdateSound()
{

}

/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void GameScene::UpdateEffect()
{

}