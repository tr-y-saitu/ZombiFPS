#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// �v���C���[�������Ă���
/// </summary>
class PlayerRunState : public PlayerStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerRunState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerRunState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};



