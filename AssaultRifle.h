#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;

/// <summary>
/// �A�T���g���C�t��
/// </summary>
class AssaultRifle : public GunBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AssaultRifle();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~AssaultRifle();

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



