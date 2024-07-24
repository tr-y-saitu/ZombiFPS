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
    , cameraPitch           (0.0f)
    , targetPosition        (VGet(0,0,0))
    , cameraPosition        (VGet(0,0,0))
{
    // �`��͈͂̐ݒ�
    SetCameraNearFar(CameraNearClip, CameraFarClip);

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
/// <param name="input">���͏��</param>
/// <param name="setPostion">�ݒ肷����W</param>
/// <param name="stage">�X�e�[�W</param>
void PlayerCamera::Update(const Input& input, VECTOR setPostion, const Stage& stage)
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();


#ifdef USE_MOUSE
    // �}�E�X���g���ăJ�����̊p�x���X�V
    UpdateCameraAngleMouse(input);
#else
    // �p�b�h�A�L�[�{�[�h���͂ŃJ�����̊p�x���X�V
    UpdateCameraAngle(input);
#endif

    // �J�����̒����_���v���C���[������ɐݒ�
    targetPosition = VAdd(setPostion, CameraPlayerTargetPosition);

    // �J�����̍��W��␳����
    FixCameraPosition(stage);

    // �J�����̑O�����x�N�g���̍X�V
    UpdateCameraForwardVector();

    // �J�����̃s�b�`�p�x�v�Z
    UpdateCameraPitch();

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
/// �}�E�X�ł̃J�����p�x�X�V
/// </summary>
/// <param name="input">���͍X�V���</param>
void PlayerCamera::UpdateCameraAngleMouse(const Input& input)
{
    // �}�E�X�J�[�\���ʒu�̎擾
    Input::MousePosition mousePosition = input.GetMousePosition();

    // ��ʂ̒��S����ǂ̂��炢����Ă��邩
    int deltaX = mousePosition.x - ScreenWidthHalf;
    int deltaY = mousePosition.y - ScreenHeightHalf;

    // �}�E�X���x��ݒ�
    float mouseSensitivity = input.MouseSensitivity;

    // �����p�x���X�V
    if (fabs(deltaX) * mouseSensitivity >= MouseInputDeadZoneMin)
    {
        angleHorizon += deltaX * mouseSensitivity;
    }

    // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
    if (angleHorizon > DX_PI_F)
    {
        angleHorizon -= DX_TWO_PI_F;
    }
    else if (angleHorizon < -DX_PI_F)
    {
        angleHorizon += DX_TWO_PI_F;
    }

    // �����p�x���X�V
    if (fabs(deltaY) * mouseSensitivity >= MouseInputDeadZoneMin)
    {
        angleVertical -= deltaY * mouseSensitivity;
    }

    // ������p�x�ȏ�/�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
    float maxVerticalAngle = DX_PI_F / 2.0f - 0.6;
    float minVerticalAngle = -DX_PI_F / AngleVerticalOffset;

    if (angleVertical > maxVerticalAngle)
    {
        angleVertical = maxVerticalAngle;
    }
    else if (angleVertical < minVerticalAngle)
    {
        angleVertical = minVerticalAngle;
    }
}

/// <summary>
/// �J�������W�̏C��
/// </summary>
/// <param name="stage">�X�e�[�W</param>
void PlayerCamera::FixCameraPosition(const Stage& stage)
{
    MATRIX rotateZ, rotateY;
    float cameraPlayerLength;
    MV1_COLL_RESULT_POLY_DIM hitResult;
    int hitNum;

    // ���������̉�]�͂x����]
    rotateY = MGetRotY(angleHorizon);

    // ���������̉�]�͂y����] )
    rotateZ = MGetRotZ(angleVertical);

    // �J��������v���C���[�܂ł̏����������Z�b�g
    cameraPlayerLength = ToPlayerLength;

    // �J�����̍��W���Z�o
    // �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
    // ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
    // �����_�̍��W�𑫂������̂��J�����̍��W
    cameraPosition = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotateZ), rotateY), targetPosition);

    // �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
    hitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, cameraPosition, CollisionSize);
    hitNum = hitResult.HitNum;
    MV1CollResultPolyDimTerminate(hitResult);
    if (hitNum != 0)
    {
        float noHItLength;
        float hitLength;
        float testLength;
        VECTOR testPosition;

        // �������疳���ʒu�܂Ńv���C���[�ɋ߂Â�

        // �|���S���ɓ�����Ȃ��������Z�b�g
        noHItLength = 0.0f;

        // �|���S���ɓ����鋗�����Z�b�g
        hitLength = cameraPlayerLength;
        do
        {
            // �����邩�ǂ����e�X�g���鋗�����Z�b�g( ������Ȃ������Ɠ����鋗���̒��� )
            testLength = noHItLength + (hitLength - noHItLength) / 2.0f;

            // �e�X�g�p�̃J�������W���Z�o
            testPosition = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotateZ), rotateY), targetPosition);

            // �V�������W�ŕǂɓ����邩�e�X�g
            hitResult = MV1CollCheck_Capsule(stage.GetModelHandle(), -1, targetPosition, testPosition, CollisionSize);
            hitNum = hitResult.HitNum;
            MV1CollResultPolyDimTerminate(hitResult);
            if (hitNum != 0)
            {
                // ���������瓖���鋗���� testLength �ɕύX����
                hitLength = testLength;
            }
            else
            {
                // ������Ȃ������瓖����Ȃ������� testLength �ɕύX����
                noHItLength = testLength;
            }

            // hitLength �� NoHitLength ���\���ɋ߂Â��Ă��Ȃ������烋�[�v
        } while (hitLength - noHItLength > 0.1f);

        // �J�����̍��W���Z�b�g
        cameraPosition = testPosition;
    }
}

/// <summary>
/// �J�����̑O�����x�N�g�����X�V����
/// </summary>
void PlayerCamera::UpdateCameraForwardVector()
{
    // �J�������王�_�����ւ̃x�N�g��
    cameraForwardVector = VSub(targetPosition, cameraPosition);

    // ���K��
    cameraForwardVector = VNorm(cameraForwardVector);
}

/// <summary>
/// �J�����̃s�b�`�p�x���X�V����
/// </summary>
/// HACK:
/// �s�b�`�F�㉺�p�x
/// �v���C���[���f���ƃv���C���[�J�����̊p�x�͓������Ă���̂ŁA
/// �㉺�p�x�݂̂��̊֐��ōX�V
void PlayerCamera::UpdateCameraPitch()
{
    // �J�����̑O�����x�N�g���擾�i�J�������ǂ��������Ă���̂��j
    VECTOR forwardVector = cameraForwardVector;

    //---- �J�������㉺�ɂǂ̂��炢�X���Ă��邩���v�Z ----//
    
    // �O�����x�N�g���̒������v�Z
    // MEMO�F
    //  ���̎������]������
    //  X����Z���Ƃō�������ʂ���ǂ̒��x�J�����̑O�����x�N�g�����L�тĂ��邩���v�Z�����
    float horizonLength = sqrt(forwardVector.x * forwardVector.x + forwardVector.z * forwardVector.z);
    
    // X����Z�������������ʂ̒�������ǂ̂��炢�X���Ă��邩�v�Z
    // MEMO:
    //  horizonLength���Q�������ʏ�̎��Ƃ��A
    //  ��������forwardVector.y�܂łǂ̂��炢�̊p�x�����邩���v�Z����
    cameraPitch = atan2f(forwardVector.y, horizonLength);
}