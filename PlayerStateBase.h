#pragma once

/// <summary>
/// �v���C���[�X�e�[�g��b�N���X
/// </summary>
class PlayerStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerStateBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerStateBase();

    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() abstract;

private:

};

