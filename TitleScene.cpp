#include "Common.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
    : isKeyOn           (false)
    , isKeyRelease      (false)
    , isPreviousKeyOn   (false)
{
    titleSceneUI = TitleSceneUI();

    // ������
    Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{

}

/// <summary>
/// �V�[���̍X�V����
/// </summary>
/// <returns>���̃V�[���̃|�C���^</returns>
SceneBase* TitleScene::UpdateScene()
{
    // �e�X�g�`��
    DrawString(0, 0, "Title", GetColor(255, 255, 255), true);

    // �L�[���͂̍X�V
    UpdateKeyState();

    // �I�u�W�F�N�g�X�V
    titleSceneUI.Update();      // UI�̍X�V

    // �X�y�[�X�L�[�����͂��ꂽ��V�[������
    if (isKeyRelease)
    {
        // �L�[�͗���Ă��܂���
        isKeyRelease = false;

        // �Q�[���V�[���ɐ���
        return new GameScene();
    }

    // ����̃V�[��
    return this;
}

/// <summary>
/// ���̍X�V
/// </summary>
void TitleScene::UpdateSound()
{

}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
    // UI�̕`��
    DrawUI();
}

/// <summary>
/// UI�̕`��
/// </summary>
void TitleScene::DrawUI()
{
    titleSceneUI.Draw();
}

/// <summary>
/// ���͍X�V
/// </summary>
void TitleScene::UpdateKeyState()
{
    // �L�[���͂��łɂ���Ă���ꍇ
    if (isKeyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            isKeyOn = false;          // �L�[�����͂���Ă��Ȃ�
            isKeyRelease = true;      // �L�[�����ꂽ
        }
    }
    else if (isPreviousKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        // �L�[�͒���������Ă��Ȃ� && �O�t���[���œ��͂Ȃ� && �L�[�������ꂽ
        isKeyRelease = false;   // �L�[�͗���Ă��Ȃ�
        isKeyOn = true;         // �L�[�������ꂽ
    }

    // �L�[���͂��ꂽ��
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        isPreviousKeyOn = true;   // ���̃t���[���ł̓L�[�������ꂽ
    }
    else
    {
        isPreviousKeyOn = false;  // ���̃t���[���ŃL�[�͉�����Ȃ�����
    }
}