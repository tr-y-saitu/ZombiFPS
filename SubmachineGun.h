#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;

/// <summary>
/// �T�u�}�V���K��
/// </summary>
class SubmachineGun : public GunBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SubmachineGun();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SubmachineGun();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:
    // �ϐ�
    VECTOR position;        // ���W
    vector<Shot*> shot;     // �e�e
    GunStateBase* gunState; // �e�̏��
};

