#pragma once
#include "GunStateBase.h"

/// <summary>
/// �e���������Ă��Ȃ����
/// </summary>
class GunIdleState : public GunStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunIdleState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunIdleState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};

