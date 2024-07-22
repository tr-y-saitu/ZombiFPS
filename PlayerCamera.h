#pragma once
#include "Common.h"

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
    void Update();

private:
    // �萔
    static constexpr float AngleSpeed = 0.05f;                  // ���񑬓x
    static constexpr float CameraPlayerTargetHeight = 400.0f;   // �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
    static constexpr float ToPlayerLength = 1600.0f;            // �v���C���[�Ƃ̋���
    static constexpr float CollisionSize = 50.0f;               // �J�����̓����蔻��T�C�Y

    // �ϐ�
    float   angleHorizon;       // �����p�x
    float   angleVertical;      // �����p�x
    VECTOR  targetPosition;     // �J���������鎋�_���W
    VECTOR  cameraPosition;     // �J�������g�̍��W
};

