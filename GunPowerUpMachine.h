#pragma once
#include "Common.h"

/// <summary>
/// �e�̋����}�V��
/// </summary>
class GunPowerUpMachine
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunPowerUpMachine();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GunPowerUpMachine();

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
    VECTOR position;        // ���W
};

