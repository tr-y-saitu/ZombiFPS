#pragma once

/// <summary>
/// �V�[���N���X�̃x�[�X
/// </summary>
class SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase();

    /// <summary>
    /// �ŏ��̃V�[���̏�����
    /// </summary>
    /// <returns>���߂ɓo�^������V�[���̃|�C���^</returns>
    static SceneBase* InitializeBase();

    /// <summary>
    /// ������
    /// </summary>
    virtual void Initialize() abstract;

    /// <summary>
    /// �V�[�����̍X�V
    /// </summary>
    /// <returns></returns>
    virtual SceneBase* UpdateScene() abstract;

    /// <summary>
    /// �T�E���h�̍X�V
    /// </summary>
    virtual void UpdateSound() abstract;

    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() abstract;   // �������z�֐�

    /// <summary>
    /// UI�̕`��
    /// </summary>
    virtual void DrawUI() abstract;

protected:

};

