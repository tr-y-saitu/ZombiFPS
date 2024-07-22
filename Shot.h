#pragma once
#include "Common.h"

/// <summary>
/// �e�e
/// </summary>
class Shot
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Shot();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Shot();

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
    VECTOR  position;           // ���W
    VECTOR  direction;          // �ړ�����
    int     power;              // �З�
    float   speed;              // ���x
    int     penetratingPower;   // �ђʗ�
};



