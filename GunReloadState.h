#pragma once
#include "GunStateBase.h"


/// <summary>
/// �e�������[�h���Ă�����
/// </summary>
class GunReloadState : public GunStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GunReloadState();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GunReloadState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};



