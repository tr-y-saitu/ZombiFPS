#pragma once
#include "Common.h"

class Input;
class Player;
class Stage;

/// <summary>
/// �v���C���[��p�̃J����
/// </summary>
class PlayerCamera
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerCamera();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayerCamera();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();
    
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="input">���͍X�V���</param>
    /// <param name="player">�v���C���[</param>
    /// <param name="stage">�X�e�[�W</param>
    void Update(const Input& input, const Player& player, const Stage& stage);

    /// <summary>
    /// �J�����̊p�x���X�V����
    /// </summary>
    /// <param name="input">���͍X�V���</param>
    void UpdateCameraAngle(const Input& input);

    /// <summary>
    /// �}�E�X�ł̃J�����̊p�x�X�V
    /// </summary>
    /// <param name="input">���͍X�V���</param>
    void UpdateCameraAngleMouse(const Input& input);

    /// <summary>
    /// �J�������W�̏C��
    /// </summary>
    /// <param name="stage">�X�e�[�W</param>
    void FixCameraPosition(const Stage& stage);

    /// <summary>
    /// �J�����̑O�����x�N�g�����X�V����
    /// </summary>
    void UpdateCameraForwardVector();

    /// <summary>
    /// �J�����̃s�b�`�p�x���X�V����
    /// </summary>
    /// HACK:
    /// �s�b�`�F�㉺�p�x
    /// �v���C���[���f���ƃv���C���[�J�����̊p�x�͓������Ă���̂ŁA
    /// �㉺�p�x�݂̂��̊֐��ōX�V
    void UpdateCameraPitch();

    // �Q�b�^�[
    const VECTOR& GetCameraPosition() const { return cameraPosition; }
    const VECTOR& GetTargetPosition() const { return targetPosition; }
    const VECTOR& GetCameraForwardVector() const { return cameraForwardVector; }
    const float GetAngleHorizon() const { return angleHorizon; }
    const float GetAngleVertical() const { return angleVertical; }
    const float GetCameraPitch() const { return cameraPitch; }

private:
    //---------------------------------------------------------------------------------//
    //                                      �萔                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  CameraNearClip              = 0.1f;     // �J�����̃j�A�N���b�v
    static constexpr float  CameraFarClip               = 200.0f;   // �J�����̃t�@�[�N���b�v
    static constexpr float  AngleSpeed                  = 0.05f;    // ���񑬓x
    static constexpr float  CameraPlayerTargetHeight    = 1.0f;     // �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
    static constexpr float  ToPlayerLength              = 3.0f;     // �v���C���[�Ƃ̋���
    static constexpr float  CollisionSize               = 1.0f;     // �J�����̓����蔻��T�C�Y
    static constexpr float  AngleVerticalOffset         = 2.6f;     // ���p�x�ȏ��������Ȃ��悤�ɂ��邽�߂̃o�t�l
    static constexpr float  AngleVerticalDonwOffset     = 1.4f;     // �����͎��Ɉ��ȏ�p�x�����ɂȂ�Ȃ��悤�ɂ��邽�߂̃o�t�l
    static constexpr VECTOR CameraPlayerTargetPosition  = { 0.0f,CameraPlayerTargetHeight,0.0f };    // �J�����̒����_�̍��W


    //---------------------------------------------------------------------------------//
    //                                      �ϐ�                                       //
    //---------------------------------------------------------------------------------//
    float   angleHorizon;           // �����p�x
    float   angleVertical;          // �����p�x
    float   cameraPitch;            // �㉺�̊p�x��
    VECTOR  targetPosition;         // �J���������鎋�_���W
    VECTOR  cameraPosition;         // �J�������g�̍��W
    VECTOR  cameraForwardVector;    // �J�����̑O�����x�N�g��
};

