#pragma once
#include "Common.h"

class EnemyGroup;

/// <summary>
/// �W�������G�l�~�[����ɂ܂Ƃ߂�
/// </summary>
class EnemyGroupController
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyGroupController();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyGroupController();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

private:
    // �萔


    // �ϐ�
};


