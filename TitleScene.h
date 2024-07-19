#pragma once
#include "SceneBase.h"
#include "TitleSceneUI.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TitleScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleScene();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// �V�[���̍X�V����
    /// </summary>
    /// <returns>���̃V�[���̃|�C���^</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// ���̍X�V
    /// </summary>
    void UpdateSound() override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UI�̕`��
    /// </summary>
    void DrawUI();

    /// <summary>
    /// ���͍X�V
    /// </summary>
    void UpdateKeyState();

private:
    // �萔

    // �ϐ�
    TitleSceneUI titleSceneUI;          // �^�C�g���V�[���p��UI


    // ���͊֌W
    bool    isKeyOn;                    // �L�[���͂��ꂽ��
    bool    isKeyRelease;               // �L�[���͂����ꂽ��
    bool    isPreviousKeyOn;            // �O�t���[���ŃL�[���͂���������
};

