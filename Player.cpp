#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerOnHitEnemyState.h"
#include "PlayerRunState.h"
#include "PlayerWalkState.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
    : position      (VGet(0,0,0))
{
    playerState = new PlayerIdleState();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
    delete(playerState);
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="palyerCamera">�v���C���[�̃J����</param>
void Player::Update(Input& input, PlayerCamera& palyerCamera)
{

}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{

}

/// <summary>
/// �V��ɐڐG�������̏���
/// </summary>
void Player::OnHitRoof()
{

}

/// <summary>
/// ���ɓ����������̏���
/// </summary>
void Player::OnHitFloor()
{

}

/// <summary>
/// �������m�肵�����̏���
/// </summary>
void Player::OnFall()
{

}



