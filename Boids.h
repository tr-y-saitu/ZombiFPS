#pragma once
#include "Common.h"

/// <summary>
/// �W���v�Z�����N���X
/// </summary>
class Boids
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Boids();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Boids();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

private:

};

