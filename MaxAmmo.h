#pragma once
#include "Common.h"

/// <summary>
/// �����e�򂪍ő�܂ŕ�[�����A�C�e��
/// </summary>
class MaxAmmo
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MaxAmmo();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~MaxAmmo();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

private:
    VECTOR position;            // ���W
};

