#pragma once
#include "GunStateBase.h"

/// <summary>
/// �e�������Ă�����
/// </summary>
class GunShotState : public GunStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunShotState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunShotState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};

