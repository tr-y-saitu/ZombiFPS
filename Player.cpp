#include "Player.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "Stage.h"
#include "PlayerIdleState.h"
#include "PlayerOnHitEnemyState.h"
#include "PlayerRunState.h"
#include "PlayerWalkState.h"
#include "ModelDataManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
    : position      (VGet(0,0,0))
{
    modelDataManager    = ModelDataManager::GetInstance();
    playerState         = new PlayerIdleState();
    Initialize();
    MV1SetRotationXYZ(modelHandle, VGet(0, 10 * DX_PI_F / 180.0f, 0));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
    delete(playerState);
    MV1DeleteModel(modelHandle);
    DeleteGraph(shadowHandle);
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
    // ���W�ݒ�
    position = VGet(0.0f, MoveLimitY, 0.0f);
    
    // �p�x��ݒ�
    angle = 0.0f;

    // ���f���n���h�����擾
    modelHandle = modelDataManager->GetModelHandle(ModelDataManager::ModelDataType::PlayerModelData);
    //modelHandle = MV1LoadModel("Data/Player/playerScaleMini.mv1");

    // ���f���T�C�Y���Đݒ�
    MV1SetScale(modelHandle, PlayerScale);
    
    // ��Ԃ�������
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
/// <param name="playerCamera">�v���C���[�̃J����</param>
void Player::Update(const Input& input, PlayerCamera& playerCamera, Stage& stage)
{
    // ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
    DisableRootFrameZMove();

    // �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
    VECTOR	UpMoveVec;		// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR	LeftMoveVec;	// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR	MoveVec;		// ���̃t���[���̈ړ��x�N�g��
    auto IsPressMoveButton = UpdateMoveParameterWithPad(input, playerCamera, UpMoveVec, LeftMoveVec, MoveVec);

    // �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
    if (IsPressMoveButton)
    {
        // �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
        targetMoveDirection = VNorm(MoveVec);

        // �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
        MoveVec = VScale(targetMoveDirection, MoveSpeed);

        // �������܂Łu�����~�܂�v��Ԃ�������
        if (state == State::None)
        {
            // ����A�j���[�V�������Đ�����
            PlayAnim(AnimationType::Run);

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
            PlayAnim(AnimationType::Stop);

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
        if (currentJumpPower < 0.0f && MV1GetAttachAnim(modelHandle, currentPlayAnim) == 2)
        {
            // �������悤�̃A�j���[�V�������Đ�����
            PlayAnim(AnimationType::Jump);
        }

        // �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
        MoveVec.y = currentJumpPower;
    }

    // �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
    UpdateAngle(playerCamera.GetAngleHorizon(),playerCamera.GetAngleVertical());

    // �ړ��x�N�g�������ɃR���W�������l�����v���C���[���ړ�
    Move(MoveVec, stage);

    // �A�j���[�V��������
    UpdateAnimation();
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(const Stage& stage)
{
    MV1DrawModel(modelHandle);
    DrawShadow(stage);

    // ���W�`��
    DrawFormatString(100,0,GetColor(255,255,255),"X:%f Y:%f Z:%f",position.x,position.y,position.z);
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
        if (isMove)
        {
            // �ړ����Ă���ꍇ�͑����Ԃ�
            PlayAnim(AnimationType::Run);
            state = State::Run;
        }
        else
        {
            // �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
            PlayAnim(AnimationType::Stop);
            state = State::None;
        }

        // ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
        animBlendRate = 1.0f;
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

    MATRIX LocalMatrix;

    // ���[�U�[�s�����������
    MV1ResetFrameUserLocalMatrix(modelHandle, 2);

    // ���݂̃��[�g�t���[���̍s����擾����
    LocalMatrix = MV1GetFrameLocalMatrix(modelHandle, 2);

    // �y�������̕��s�ړ������𖳌��ɂ���
    LocalMatrix.m[3][2] = 0.0f;

    // ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
    MV1SetFrameUserLocalMatrix(modelHandle, 2, LocalMatrix);
}

/// <summary>
/// �ړ��p�����[�^��ݒ肷��
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="playerCamera">�v���C���[��p�̃J����</param>
/// <param name="UpMoveVec">������x�N�g��</param>
/// <param name="LeftMoveVec">�������x�N�g��</param>
/// <param name="MoveVec">�ړ��x�N�g��</param>
/// <returns>�ړ����Ă��邩�ǂ���</returns>
bool Player::UpdateMoveParameterWithPad(const Input& input, const PlayerCamera& playerCamera,
    VECTOR& UpMoveVec, VECTOR& LeftMoveVec, VECTOR& MoveVec)
{
    // �v���C���[�̈ړ������̃x�N�g�����Z�o
    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
    UpMoveVec = VSub(playerCamera.GetTargetPosition(), playerCamera.GetCameraPosition());
    UpMoveVec.y = 0.0f;
    
    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
    LeftMoveVec = VCross(UpMoveVec, VGet(0.0f, 1.0f, 0.0f));
    
    // ��̃x�N�g���𐳋K��( �x�N�g���̒������P�D�O�ɂ��邱�� )
    UpMoveVec = VNorm(UpMoveVec);
    LeftMoveVec = VNorm(LeftMoveVec);
    
    // ���̃t���[���ł̈ړ��x�N�g����������
    MoveVec = VGet(0.0f, 0.0f, 0.0f);
    
    // �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\��FALSE�ɂ���
    bool IsPressMoveButton = false;
    
    // �p�b�h�̂R�{�^���ƍ��V�t�g���ǂ����������Ă��Ȃ�������v���C���[�̈ړ�����
    if (CheckHitKey(KEY_INPUT_LSHIFT) == 0 && (input.GetCurrentFrameInput() & PAD_INPUT_C) == 0)
    {
        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
        if (input.GetCurrentFrameInput() & PAD_INPUT_LEFT)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            MoveVec = VAdd(MoveVec, LeftMoveVec);

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            IsPressMoveButton = true;
        }
        else
        {
            // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�ĉE�����Ɉړ�����
            if (input.GetCurrentFrameInput() & PAD_INPUT_RIGHT)
            {
                // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
                MoveVec = VAdd(MoveVec, VScale(LeftMoveVec, -1.0f));

                // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
                IsPressMoveButton = true;
            }
        }

        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă�������Ɉړ�����
        if (input.GetCurrentFrameInput() & PAD_INPUT_UP)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            MoveVec = VAdd(MoveVec, UpMoveVec);

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            IsPressMoveButton = true;
        }
        else
        {
            // �����{�^���u���v�����͂��ꂽ��J�����̕����Ɉړ�����
            if (input.GetCurrentFrameInput() & PAD_INPUT_DOWN)
            {
                // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
                MoveVec = VAdd(MoveVec, VScale(UpMoveVec, -1.0f));

                // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
                IsPressMoveButton = true;
            }
        }

        // HACk:
        // �̂��ɃW�����v��ǉ�����\�������邽�߃R�����g�A�E�g���Ă��܂�
        // �v���C���[�̏�Ԃ��u�W�����v�v�ł͂Ȃ��A���{�^���P��������Ă�����W�����v����
        //if (state != State::Jump && (input.GetNowNewFrameInput() & PAD_INPUT_A))
        //{
        //    // ��Ԃ��u�W�����v�v�ɂ���
        //    state = State::Jump;

        //    // �x�������̑��x���Z�b�g
        //    currentJumpPower = JumpPower;

        //    // �W�����v�A�j���[�V�����̍Đ�
        //    PlayAnim(AnimationType::Jump);
        //}
    }
    return IsPressMoveButton;
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
        isMove = true;
    }
    else
    {
        isMove = false;
    }

    // �����蔻������āA�V�������W��ۑ�����
    VECTOR OldPos = position;                           // �ړ��O�̍��W
    VECTOR NextPos = VAdd(position, MoveVector);        // �ړ���̍��W

    // �X�e�[�W�Ƃ̓����蔻�菈��
    position = stage.IsHitCollision(*this, NextPos, MoveVector);

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
void Player::UpdateAngle(float angleHorizon, float angleVertical)
{
    // �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
    float TargetAngle;          // �ڕW�p�x
    float difference;           // �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

    // �ڕW�̕����x�N�g������p�x�l���Z�o����
    TargetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

    // �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
    // �ŏ��͒P���Ɉ����Z
    difference = TargetAngle - angle;

    // ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
    // ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }

    // �p�x�̍����O�ɋ߂Â���
    if (difference > 0.0f)
    {
        // �����v���X�̏ꍇ�͈���
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // �����}�C�i�X�̏ꍇ�͑���
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }
    
    //// �v���C���[�J�����Ɠ��l�̉�]���s��
    //MATRIX rotateY, rotateZ;

    //// ����������]�l�����߂�(���̃J�����ړ�)
    //rotateY = MGetRotY(angleHorizon);

    //// ����������]�l�����߂�(�c�̃J�����ړ�)
    //rotateZ = MGetRotZ(angleVertical);


    // ���f���̊p�x���X�V
    // ���̒i�K���Ɖ��������������Ȃ�
    angle = TargetAngle - difference;
    MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
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


/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
void Player::UpdateAnimation()
{
    float AnimTotalTime;		// �Đ����Ă���A�j���[�V�����̑�����

    // �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
    if (animBlendRate < 1.0f)
    {
        animBlendRate += AnimBlendSpeed;
        if (animBlendRate > 1.0f)
        {
            animBlendRate = 1.0f;
        }
    }

    // �Đ����Ă���A�j���[�V�����P�̏���
    if (currentPlayAnim != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnim);

        // �Đ����Ԃ�i�߂�
        currentAnimCount += PlayAnimSpeed;

        // �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
        if (currentAnimCount >= AnimTotalTime)
        {
            currentAnimCount = static_cast<float>(fmod(currentAnimCount, AnimTotalTime));
        }

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(modelHandle, currentPlayAnim, currentAnimCount);

        // �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnim, animBlendRate);
    }

    // �Đ����Ă���A�j���[�V�����Q�̏���
    if (prevPlayAnim != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevPlayAnim);

        // �Đ����Ԃ�i�߂�
        prevAnimCount += PlayAnimSpeed;

        // �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
        if (prevAnimCount > AnimTotalTime)
        {
            prevAnimCount = static_cast<float>(fmod(prevAnimCount, AnimTotalTime));
        }

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(modelHandle, prevPlayAnim, prevAnimCount);

        // �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(modelHandle, prevPlayAnim, 1.0f - animBlendRate);
    }
}

/// <summary>
/// �e��`��
/// </summary>
/// <param name="stage"></param>
void Player::DrawShadow(const Stage & stage)
{
}


