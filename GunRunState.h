#pragma once
#include "GunStateBase.h"

/// <summary>
/// �e�������đ����Ă�����
/// </summary>
class GunRunState : public GunStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunRunState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunRunState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};


