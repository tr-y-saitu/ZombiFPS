#include "SceneCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneCamera::SceneCamera()
    : angle         (0)
{
    // �`��͈͂̐ݒ�
    SetCameraNearFar(0.1f, 600.0f);

    // �J�����̃|�W�V����
    position = VGet(0,0,0);

    // �J������ݒ�
    SetCameraPositionAndTarget_UpVecY(position, VGet(-7, 5, 20));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneCamera::~SceneCamera()
{
    // �����Ȃ�
}

/// <summary>
/// ������
/// </summary>
/// <param name="initializePosition">�J�����̍��W</param>
/// <param name="targetPosition">�J�����̌��Ă�����W</param>
void SceneCamera::Initialize(VECTOR initializePosition, VECTOR targetPosition)
{
    // �J�����ݒ�
    // initializePosition����targetPosition������
    SetCameraPositionAndTarget_UpVecY(initializePosition, targetPosition);
}

/// <summary>
/// �X�V
/// </summary>
void SceneCamera::Update()
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();
}