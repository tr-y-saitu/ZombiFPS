#include "Player.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "Stage.h"
#include "PlayerIdleState.h"
#include "PlayerOnHitEnemyState.h"
#include "PlayerRunState.h"
#include "PlayerWalkState.h"
#include "ModelDataManager.h"
#include "AssaultRifle.h"
#include "BattleRifle.h"
#include "SubmachineGun.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
    : position              (VGet(0,0,0))
    , pressMoveButton       (false)
{
    modelDataManager        = ModelDataManager::GetInstance();
    playerCamera            = new PlayerCamera();
    playerState             = new PlayerIdleState();
    Initialize();
    MV1SetRotationXYZ(modelHandle, VGet(0, 0.0f * DX_PI_F / 180.0f, 0));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
    delete(playerState);
    delete(playerCamera);
    MV1DeleteModel(modelHandle);
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
    // ���W�ݒ�
    position = VGet(0.0f, MoveLimitY, 0.0f);
    
    // ���f���n���h�����擾
    modelHandle = modelDataManager->GetOriginalModelHandle(ModelDataManager::ModelDataType::PlayerModelData);

    // ���f���T�C�Y���Đݒ�
    MV1SetScale(modelHandle, PlayerScale);
    
    // ��Ԃ�������
    state = State::None;
    
    // �W�����v�͂͏�����Ԃł͂O
    currentJumpPower = 0.0f;
    
    // ������ԂŃv���C���[�������ׂ������͂w������
    targetMoveDirection = VGet(1.0f, 0.0f, 0.0f);
    
    // �A�j���[�V�����̃u�����h����������
    animationBlendRate = 1.0f;
    
    // ������Ԃł̓A�j���[�V�����̓A�^�b�`����Ă��Ȃ��ɂ���
    currentPlayAnimation = -1;
    previousPlayAnimation = -1;
    
    // �A�j���[�V�����ݒ�
    PlayAnimation(AnimationType::None);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="stage">�X�e�[�W</param>
void Player::Update(const Input& input, Stage& stage)
{
    // ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
    DisableRootFrameZMove();

    // �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
    VECTOR  upModveVector;          // �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR  leftMoveVector;         // �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR  currentFrameMoveVector; // ���̃t���[���̈ړ��x�N�g��

    // �ړ��x�N�g���̍X�V
    UpdateMoveVector(input, upModveVector, leftMoveVector, currentFrameMoveVector);

    // �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
    if (pressMoveButton)
    {
        // �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
        targetMoveDirection = VNorm(currentFrameMoveVector);

        // �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
        currentFrameMoveVector = VScale(targetMoveDirection, MoveSpeed);

        // �������܂Łu�����~�܂�v��Ԃ�������
        if (state == State::None)
        {
            // ����A�j���[�V�������Đ�����
            PlayAnimation(AnimationType::Run);

            // ��Ԃ��u����v�ɂ���
            state = State::Run;
        }
    }
    else
    {
        // ���̃t���[���ňړ����Ă��Ȃ��āA����Ԃ��u����v��������
        if (state == State::Run)
        {
            // �����~��A�j���[�V�������Đ�����
            PlayAnimation(AnimationType::Stop);

            // ��Ԃ��u�����~��v�ɂ���
            state = State::None;
        }
    }

    // ��Ԃ��u�W�����v�v�̏ꍇ��
    if (state == State::Jump)
    {
        // �x�������̑��x���d�͕����Z����
        currentJumpPower -= Gravity;

        // �����������Ă��Ċ��Đ�����Ă���A�j���[�V�������㏸���p�̂��̂������ꍇ��
        if (currentJumpPower < 0.0f && MV1GetAttachAnim(modelHandle, currentPlayAnimation) == 2)
        {
            // �������悤�̃A�j���[�V�������Đ�����
            PlayAnimation(AnimationType::Jump);
        }

        // �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
        currentFrameMoveVector.y = currentJumpPower;
    }

    // �v���C���[���f���ƃv���C���[�J�����̉�]���𓯊�������
    UpdateAngle();

    // �ړ��x�N�g�������ɃR���W�������l�����v���C���[���ړ�
    Move(currentFrameMoveVector, stage);

    // �A�j���[�V��������
    UpdateAnimation();

    // �v���C���[�J�����̍X�V
    UpdatePlayerCamera(input, stage);
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(const Stage& stage)
{
    MV1DrawModel(modelHandle);

    // ���W�`��
    DrawFormatString(100,0,GetColor(255,255,255),"X:%f Y:%f Z:%f",position.x,position.y,position.z);
}

/// <summary>
/// �v���C���[�J�����̍X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="stage">�X�e�[�W</param>
void Player::UpdatePlayerCamera(const Input& input, Stage& stage)
{
    playerCamera->Update(input, position,stage);
}

/// <summary>
/// �V��ɐڐG�������̏���
/// </summary>
void Player::OnHitRoof()
{
    // �x�������̑��x�͔��]
    currentJumpPower = -currentJumpPower;
}

/// <summary>
/// ���ɓ����������̏���
/// </summary>
void Player::OnHitFloor()
{
    // �x�������̈ړ����x�͂O��
    currentJumpPower = 0.0f;

    // �����W�����v���������ꍇ�͒��n��Ԃɂ���
    if (state == State::Jump)
    {
        // �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
        if (currentFrameMove)
        {
            // �ړ����Ă���ꍇ�͑����Ԃ�
            PlayAnimation(AnimationType::Run);
            state = State::Run;
        }
        else
        {
            // �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
            PlayAnimation(AnimationType::Stop);
            state = State::None;
        }

        // ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
        animationBlendRate = 1.0f;
    }
}

/// <summary>
/// ���[�g�t���[����Z�������̈ړ��p�����[�^�𖳌��ɂ���
/// </summary>
void Player::DisableRootFrameZMove()
{
    // HACK:
    // �EDX���C�u�����̃��f���t�@�C�����ɂ́A�����̃��b�V���i�|���S���̏W���j��J�����A���C�g�����邱�Ƃ��ł���
    // �E�u���������̃t�@�C���́A�e�q�֌W��������AUnity�̃q�G�����L�[�݂����ɁA�K�w�\��������
    // �E���̊K�w���ꂼ��ɂ͖��O���t������ Root-Meshes-Model1
    //                                                   |-Model2
    // �E���̖��O�̕t�����K�w�̂��Ƃ�DX���C�u�����ł̓t���[���Ƃ���
    // �E��Ԑe�̊K�w���u���[�g�t���[���v�ƌĂԁB���[�g�t���[���͈��
    // 
    // HACK: ���̂��߂ɁH���f���̈�Ԑe�t���[���i�e�K�w�j��Z�������̈ړ��p�����[�^���[���ɂ��Ă���

    MATRIX localMatrix;

    // ���[�U�[�s�����������
    MV1ResetFrameUserLocalMatrix(modelHandle, 2);

    // ���݂̃��[�g�t���[���̍s����擾����
    localMatrix = MV1GetFrameLocalMatrix(modelHandle, 2);

    // �y�������̕��s�ړ������𖳌��ɂ���
    localMatrix.m[3][2] = 0.0f;

    // ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
    MV1SetFrameUserLocalMatrix(modelHandle, 2, localMatrix);
}

/// <summary>
/// �ړ��x�N�g���̍X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="upModveVector">������x�N�g��</param>
/// <param name="leftMoveVector">�������x�N�g��</param>
/// <param name="currentFrameMoveVector">�ړ��x�N�g��</param>
void Player::UpdateMoveVector(const Input& input, VECTOR& upModveVector,
    VECTOR& leftMoveVector, VECTOR& currentFrameMoveVector)
{
    // �v���C���[�̈ړ������̃x�N�g�����Z�o
// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
    upModveVector = VSub(playerCamera->GetTargetPosition(), playerCamera->GetCameraPosition());
    upModveVector.y = 0.0f;

    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
    leftMoveVector = VCross(upModveVector, VGet(0.0f, 1.0f, 0.0f));

    // �x�N�g���̐��K��
    upModveVector = VNorm(upModveVector);
    leftMoveVector = VNorm(leftMoveVector);

    // ���̃t���[���ł̈ړ��x�N�g����������
    currentFrameMoveVector = ZeroVector;

    // �ړ��p�̃{�^�������͂��ꂽ���ǂ���
    pressMoveButton = false;

    // �p�b�h�̂R�{�^���ƍ��V�t�g���ǂ����������Ă��Ȃ�������v���C���[�̈ړ�����
    if (CheckHitKey(KEY_INPUT_LSHIFT) == 0 && (input.GetCurrentFrameInput() & PAD_INPUT_C) == 0)
    {
        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
        if (input.GetCurrentFrameInput() & PAD_INPUT_LEFT || CheckHitKey(KEY_INPUT_A))
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            currentFrameMoveVector = VAdd(currentFrameMoveVector, leftMoveVector);

            // �ړ��p�{�^���������ꂽ
            pressMoveButton = true;
        }
        else
        {
            // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�ĉE�����Ɉړ�����
            if (input.GetCurrentFrameInput() & PAD_INPUT_RIGHT || CheckHitKey(KEY_INPUT_D))
            {
                // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
                currentFrameMoveVector = VAdd(currentFrameMoveVector, VScale(leftMoveVector, -1.0f));

                // �ړ��p�{�^���������ꂽ
                pressMoveButton = true;
            }
        }

        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă�������Ɉړ�����
        if (input.GetCurrentFrameInput() & PAD_INPUT_UP || CheckHitKey(KEY_INPUT_W))
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            currentFrameMoveVector = VAdd(currentFrameMoveVector, upModveVector);

            // �ړ��p�{�^���������ꂽ
            pressMoveButton = true;
        }
        else
        {
            // �����{�^���u���v�����͂��ꂽ��J�����̕����Ɉړ�����
            if (input.GetCurrentFrameInput() & PAD_INPUT_DOWN || CheckHitKey(KEY_INPUT_S))
            {
                // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
                currentFrameMoveVector = VAdd(currentFrameMoveVector, VScale(upModveVector, -1.0f));

                // �ړ��p�{�^���������ꂽ
                pressMoveButton = true;
            }
        }

        // MEMO:
        // �̂��ɃW�����v��ǉ�����\�������邽�߃R�����g�A�E�g���Ă��܂�
        // �v���C���[�̏�Ԃ��u�W�����v�v�ł͂Ȃ��A���{�^���P��������Ă�����W�����v����
        //if (state != State::Jump && (input.GetNowNewFrameInput() & PAD_INPUT_A))
        //{
        //    // ��Ԃ��u�W�����v�v�ɂ���
        //    state = State::Jump;

        //    // �x�������̑��x���Z�b�g
        //    currentJumpPower = JumpPower;

        //    // �W�����v�A�j���[�V�����̍Đ�
        //    PlayAnimation(AnimationType::Jump);
        //}
    }
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="MoveVector">�ړ��x�N�g��</param>
/// <param name="stage">�X�e�[�W</param>
void Player::Move(const VECTOR& MoveVector, Stage& stage)
{
    // HACK: �ړ�������0.01�����Ŕ����Ɉړ����Ă����ꍇ�͂�����ړ����ăo�O��
    // x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
    if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
    {
        currentFrameMove = true;
    }
    else
    {
        currentFrameMove = false;
    }

    // �����蔻������āA�V�������W��ۑ�����
    VECTOR oldPosition = position;                      // �ړ��O�̍��W
    VECTOR nextPosition = VAdd(position, MoveVector);   // �ړ���̍��W

    // �X�e�[�W�Ƃ̓����蔻�菈��
    position = stage.IsHitCollision(*this, nextPosition, MoveVector);

    // ����菭����������
    if (position.y <= MoveLimitY)
    {
        position.y = MoveLimitY;
    }

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(modelHandle, position);
}

/// <summary>
/// ��]����
/// </summary>
void Player::UpdateAngle()
{
    // �v���C���[���f�����v���C���[�J�����̉�]���Ɠ��l�ɉ�]������

    // �v���C���[��p�J�����̕������擾
    VECTOR cameraForward = playerCamera->GetCameraForwardVector();
    float cameraPitch = playerCamera->GetCameraPitch();

    // ���f���̐���������]�l���v�Z
    float playerAngleY = atan2f(cameraForward.x, cameraForward.z);

    // �v���C���[���f����ǉ���180�x��]
    playerAngleY += DX_PI_F;

    // ���f���̉�]
    MV1SetRotationXYZ(modelHandle, VGet(cameraPitch, playerAngleY, 0.0f));
}

/// <summary>
/// �v���C���[�̃A�j���[�V������V�����ǉ�����
/// </summary>
/// <param name="PlayAnimation">�Đ��������A�j���[�V�����ԍ�</param>
void Player::PlayAnimation(AnimationType PlayAnimation)
{
    // HACK: �w�肵���ԍ��̃A�j���[�V�������A�^�b�`���A���O�ɍĐ����Ă����A�j���[�V�����̏���prev�Ɉڍs���Ă���
    // ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
    if (previousPlayAnimation != -1)
    {
        MV1DetachAnim(modelHandle, previousPlayAnimation);
        previousPlayAnimation = -1;
    }

    // ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
    previousPlayAnimation = currentPlayAnimation;
    previousAnimationCount = currentAnimationCount;

    // �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
    currentPlayAnimation = MV1AttachAnim(modelHandle, static_cast<int>(PlayAnimation));
    currentAnimationCount = 0.0f;

    // �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
    animationBlendRate = previousPlayAnimation == -1 ? 1.0f : 0.0f;
}


/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
void Player::UpdateAnimation()
{
    float animationTotalTime;       // �Đ����Ă���A�j���[�V�����̑�����

    // �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
    if (animationBlendRate < 1.0f)
    {
        animationBlendRate += AnimationBlendSpeed;
        if (animationBlendRate > 1.0f)
        {
            animationBlendRate = 1.0f;
        }
    }

    // �Đ����Ă���A�j���[�V�����P�̏���
    if (currentPlayAnimation != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnimation);

        // �Đ����Ԃ�i�߂�
        currentAnimationCount += PlayAnimationSpeed;

        // �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
        if (currentAnimationCount >= animationTotalTime)
        {
            currentAnimationCount = static_cast<float>(fmod(currentAnimationCount, animationTotalTime));
        }

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(modelHandle, currentPlayAnimation, currentAnimationCount);

        // �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnimation, animationBlendRate);
    }

    // �Đ����Ă���A�j���[�V�����Q�̏���
    if (previousPlayAnimation != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, previousPlayAnimation);

        // �Đ����Ԃ�i�߂�
        previousAnimationCount += PlayAnimationSpeed;

        // �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
        if (previousAnimationCount > animationTotalTime)
        {
            previousAnimationCount = static_cast<float>(fmod(previousAnimationCount, animationTotalTime));
        }

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(modelHandle, previousPlayAnimation, previousAnimationCount);

        // �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(modelHandle, previousPlayAnimation, 1.0f - animationBlendRate);
    }
}
