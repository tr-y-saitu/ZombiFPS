#pragma once
#include "PlayerStateBase.h"


/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class PlayerWalkState : public PlayerStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerWalkState();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerWalkState();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

private:

};

