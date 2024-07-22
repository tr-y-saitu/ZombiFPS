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
    /// <param name="input">���͏���</param>
    /// <param name="player">�v���C���[</param>
    /// <param name="stage">�X�e�[�W</param>
    void Update(const Input& input, const Player& player, const Stage& stage);

    /// <summary>
    /// �J�����̊p�x���X�V����
    /// </summary>
    /// <param name="input"></param>
    void UpdateCameraAngle(const Input& input);

    /// <summary>
    /// �J�������W�̏C��
    /// </summary>
    /// <param name="stage">�X�e�[�W</param>
    void FixCameraPosition(const Stage& stage);

    // �Q�b�^�[
    const VECTOR& GetCameraPosition() const { return cameraPosition; }
    const VECTOR& GetTargetPosition() const { return targetPosition; }

private:
    // �萔
    static constexpr float CameraNearClip = 0.1f;               // �J�����̃j�A�N���b�v
    static constexpr float CameraFarClip = 5000.0f;             // �J�����̃t�@�[�N���b�v
    static constexpr float AngleSpeed = 0.05f;                  // ���񑬓x
    static constexpr float CameraPlayerTargetHeight = 5.0f;     // �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
    static constexpr float ToPlayerLength = 10.0f;              // �v���C���[�Ƃ̋���
    static constexpr float CollisionSize = 1.0f;                // �J�����̓����蔻��T�C�Y
    static constexpr VECTOR CameraPlayerTargetPosition = { 10.0f,CameraPlayerTargetHeight,0.0f };    // �J�����̒����_�̍��W
    static constexpr float AngleVerticalOffset = 2.6f;          // ���p�x�ȏ��������Ȃ��悤�ɂ��邽�߂̃o�t�l

    // �ϐ�
    float   angleHorizon;       // �����p�x
    float   angleVertical;      // �����p�x
    VECTOR  targetPosition;     // �J���������鎋�_���W
    VECTOR  cameraPosition;     // �J�������g�̍��W
};

