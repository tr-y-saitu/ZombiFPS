#pragma once
#include "Common.h"


/// <summary>
/// �V���b�^�[(��Q���̃h�A)
/// </summary>
class Shutter
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Shutter();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Shutter();

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

