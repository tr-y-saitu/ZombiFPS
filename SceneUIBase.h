#pragma once

/// <summary>
/// �V�[��UI�̊�b�N���X
/// </summary>
class SceneUIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneUIBase();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual~SceneUIBase();

    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update();

    /// <summary>
    /// �`��
    /// </summary>
    /// MEMO:virtual�ɂ��Ă��Ȃ��̂͊e�V�[���ň������قȂ邽��
    void Draw();

protected:

};

