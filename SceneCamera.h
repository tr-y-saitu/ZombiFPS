#pragma once
#include "Common.h"

/// <summary>
/// �V�[���p�̃J����
/// </summary>
class SceneCamera
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneCamera();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SceneCamera();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="initializePosition">�J�����̍��W</param>
    /// <param name="targetPosition">�J�����̌��Ă�����W</param>
    void Initialize(VECTOR initializePosition, VECTOR targetPosition);

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

private:

    // �ϐ�
    VECTOR  position;           // �|�W�V����
    float   angle;              // �p�x

};

