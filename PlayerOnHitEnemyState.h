#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// �v���C���[���G�l�~�[�̍U�����󂯂����
/// </summary>
class PlayerOnHitEnemyState : public PlayerStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerOnHitEnemyState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerOnHitEnemyState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};


