#pragma once
#include "Common.h"

/// <summary>
/// �e�̏�Ԋ�b�N���X
/// </summary>
class GunStateBase
{
public:
    /// <summary>
    /// �e�̏��
    /// </summary>
    enum GunState
    {
        IdleState,      // �������Ă��Ȃ����
        RunState,       // ������
        ShotState,      // ���C���
        ReloadState,    // �����[�h���
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunStateBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunStateBase();

    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() abstract;

private:

};

