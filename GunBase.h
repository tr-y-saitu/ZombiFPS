#pragma once
#include "Common.h"

/// <summary>
/// �e�̊�b�N���X
/// </summary>
class GunBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunBase();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunBase();

    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() abstract;

private:
    // �ϐ�
    VECTOR position;        // ���W
};


