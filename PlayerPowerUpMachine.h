#pragma once
#include "Common.h"


/// <summary>
/// �v���C���[�����}�V��
/// </summary>
class PlayerPowerUpMachine
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerPowerUpMachine();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayerPowerUpMachine();

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

