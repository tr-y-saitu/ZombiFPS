#pragma once
#include "PlayerStateBase.h"


/// <summary>
/// �v���C���[���������Ă��Ȃ����
/// </summary>
class PlayerIdleState : public PlayerStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerIdleState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerIdleState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};

