#include "PlayerCamera.h"
#include "Input.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerCamera::PlayerCamera()
    : angleHorizon          (DX_PI_F)
    , angleVertical         (0.0f)
    , targetPosition        (VGet(0,0,0))
    , cameraPosition        (VGet(0,0,0))
{
    // �`��͈͂̐ݒ�
    SetCameraNearFar(0.1f, 600.0f);

    // �J������ݒ�
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerCamera::~PlayerCamera()
{
    // �����Ȃ�
}

/// <summary>
/// ������
/// </summary>
void PlayerCamera::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void PlayerCamera::Update(const Input& input, const Player& player, const Stage& stage)
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();

    // �J�����̊p�x���X�V
    UpdateCameraAngle(input);

    // �J�����̒����_���v���C���[������ɐݒ�
    targetPosition = VAdd(player.GetPosition(), CameraPlayerTargetPosition);

    // �J�����̍��W��␳����
    FixCameraPosition(stage);

    // �J�����̍X�V
    SetCameraPositionAndTarget_UpVecY(cameraPosition, targetPosition);
}

/// <summary>
/// �J�����̊p�x���X�V����
/// </summary>
/// <param name="input">���͏���</param>
void PlayerCamera::UpdateCameraAngle(const Input& input)
{
    // �p�b�h�̂R�{�^�����A�V�t�g�L�[��������Ă���ꍇ�̂݊p�x�ύX������s��
    if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.GetCurrentFrameInput() & PAD_INPUT_C))
    {
        // �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
        if (input.GetCurrentFrameInput() & PAD_INPUT_LEFT)
        {
            angleHorizon -= AngleSpeed;
        
            // �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
            if (angleHorizon < -DX_PI_F)
            {
                angleHorizon += DX_TWO_PI_F;
            }
        }
        
        // �u���v�{�^����������Ă����琅���p�x���v���X����
        if (input.GetCurrentFrameInput() & PAD_INPUT_RIGHT)
        {
            angleHorizon += AngleSpeed;
    
            // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
            if (angleHorizon > DX_PI_F)
            {
                angleHorizon -= DX_TWO_PI_F;
            }
        }
        
        // �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
        if (input.GetCurrentFrameInput() & PAD_INPUT_UP)
        {
            angleVertical -= AngleSpeed;
    
            // ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
            if (angleVertical < -DX_PI_F / AngleVerticalOffset)
            {
                angleVertical = -DX_PI_F / AngleVerticalOffset;
            }
        }
        
        // �u���v�{�^����������Ă����琂���p�x���v���X����
        if (input.GetCurrentFrameInput() & PAD_INPUT_DOWN)
        {
            angleVertical += AngleSpeed;
    
            // ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
            if (angleVertical > DX_PI_F / 2.0f - 0.6f)
            {
                angleVertical = DX_PI_F / 2.0f - 0.6f;
            }
        }
    }
}

/// <summary>
/// �J�������W�̏C��
/// </summary>
/// <param name="stage">�X�e�[�W</param>
void PlayerCamera::FixCameraPosition(const Stage& stage)
{
    MATRIX RotZ, RotY;
    float CameraPlayerLength;
    MV1_COLL_RESULT_POLY_DIM HitResult;
    int HitNum;

    // ���������̉�]�͂x����]
    RotY = MGetRotY(angleHorizon);

    // ���������̉�]�͂y����] )
    RotZ = MGetRotZ(angleVertical);

    // �J��������v���C���[�܂ł̏����������Z�b�g
    CameraPlayerLength = ToPlayerLength;

    // �J�����̍��W���Z�o
    // �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
    // ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
    // �����_�̍��W�𑫂������̂��J�����̍��W
    cameraPosition = VAdd(VTransform(VTransform(VGet(-CameraPlayerLength, 0.0f, 0.0f), RotZ), RotY), targetPosition);

    // �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
    HitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, cameraPosition, CollisionSize);
    HitNum = HitResult.HitNum;
    MV1CollResultPolyDimTerminate(HitResult);
    if (HitNum != 0)
    {
        float NotHitLength;
        float HitLength;
        float TestLength;
        VECTOR TestPosition;

        // �������疳���ʒu�܂Ńv���C���[�ɋ߂Â�

        // �|���S���ɓ�����Ȃ��������Z�b�g
        NotHitLength = 0.0f;

        // �|���S���ɓ����鋗�����Z�b�g
        HitLength = CameraPlayerLength;
        do
        {
            // �����邩�ǂ����e�X�g���鋗�����Z�b�g( ������Ȃ������Ɠ����鋗���̒��� )
            TestLength = NotHitLength + (HitLength - NotHitLength) / 2.0f;

            // �e�X�g�p�̃J�������W���Z�o
            TestPosition = VAdd(VTransform(VTransform(VGet(-TestLength, 0.0f, 0.0f), RotZ), RotY), targetPosition);

            // �V�������W�ŕǂɓ����邩�e�X�g
            HitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, TestPosition, CollisionSize);
            HitNum = HitResult.HitNum;
            MV1CollResultPolyDimTerminate(HitResult);
            if (HitNum != 0)
            {
                // ���������瓖���鋗���� TestLength �ɕύX����
                HitLength = TestLength;
            }
            else
            {
                // ������Ȃ������瓖����Ȃ������� TestLength �ɕύX����
                NotHitLength = TestLength;
            }

            // HitLength �� NoHitLength ���\���ɋ߂Â��Ă��Ȃ������烋�[�v
        } while (HitLength - NotHitLength > 0.1f);

        // �J�����̍��W���Z�b�g
        cameraPosition = TestPosition;
    }
}