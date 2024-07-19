#include "ResultScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
{
    resultSceneUI = ResultSceneUI();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
}

/// <summary>
/// ������
/// </summary>
void ResultScene::Initialize()
{

}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <returns>���̃V�[���̃|�C���^</returns>
SceneBase* ResultScene::UpdateScene()
{

    // �I�u�W�F�N�g�X�V
    resultSceneUI.Update();     // UI�̍X�V

    // ����̃V�[����Ԃ�
    return this;
}

/// <summary>
/// �`��
/// </summary>
void ResultScene::Draw()
{
    DrawUI();       // UI�̕`��
}

/// <summary>
/// UI�̕`��
/// </summary>
void ResultScene::DrawUI()
{
    resultSceneUI.Draw();
}

/// <summary>
/// ���̍X�V
/// </summary>
void ResultScene::UpdateSound()
{

}

/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void ResultScene::UpdateEffect()
{

}