#pragma once
#include "GunBase.h"

class GunStateBase;
class Shot;

/// <summary>
/// �o�g�����C�t��(�P�����̍��Ἠ��C�t��)
/// </summary>
class BattleRifle : public GunBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BattleRifle();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BattleRifle();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:
    VECTOR position;        // ���W
    vector<Shot*> shot;     // �e�e
    GunStateBase* gunState; // �e�̏��
};



