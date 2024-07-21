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
    Initialize();
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
    position = VGet(0.0f, 0.0f, 0.0f);
    angle = 0.0f;
    modelHandle = MV1LoadModel("DxChara.x");
    state = State::None;
    
    // �W�����v�͂͏�����Ԃł͂O
    currentJumpPower = 0.0f;
    
    // �e�`��p�̉摜�̓ǂݍ���
    shadowHandle = LoadGraph("Shadow.tga");
    
    // ������ԂŃv���C���[�������ׂ������͂w������
    targetMoveDirection = VGet(1.0f, 0.0f, 0.0f);
    
    // �A�j���[�V�����̃u�����h����������
    animBlendRate = 1.0f;
    
    // ������Ԃł̓A�j���[�V�����̓A�^�b�`����Ă��Ȃ��ɂ���
    currentPlayAnim = -1;
    prevPlayAnim = -1;
    
    // ���������Ă���A�j���[�V�������Đ�
    // TODO: �}�W�b�N�i���o�[��4�����Ȃ̂���͂��Ē萔��
    PlayAnim(AnimationType::None);           // HACK: ���ł̓A�^�b�`�ƃJ�E���^�̏����������Ă��邾��
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="palyerCamera">�v���C���[�̃J����</param>
void Player::Update(const Input& input, PlayerCamera& palyerCamera, Stage& stage)
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


// �v���C���[�̃A�j���[�V�������Đ�����
void Player::PlayAnim(AnimationType PlayAnim)
{
    // HACK: �w�肵���ԍ��̃A�j���[�V�������A�^�b�`���A���O�ɍĐ����Ă����A�j���[�V�����̏���prev�Ɉڍs���Ă���
    // ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
    if (prevPlayAnim != -1)
    {
        MV1DetachAnim(modelHandle, prevPlayAnim);
        prevPlayAnim = -1;
    }

    // ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
    prevPlayAnim = currentPlayAnim;
    prevAnimCount = currentAnimCount;

    // �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
    currentPlayAnim = MV1AttachAnim(modelHandle, static_cast<int>(PlayAnim));
    currentAnimCount = 0.0f;

    // �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
    animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}
