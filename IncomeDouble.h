#pragma once
#include "Common.h"

/// <summary>
/// �擾���z��2�{�ɂȂ�A�C�e��
/// </summary>
class IncomeDouble
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    IncomeDouble();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~IncomeDouble();

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

