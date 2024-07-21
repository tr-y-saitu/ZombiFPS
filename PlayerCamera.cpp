#include "PlayerCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerCamera::PlayerCamera()
    : angleHorizon          (DX_PI_F)
    , angleVertical         (0.0f)
    , targetPosition        (VGet(-100,5,-5))
    , cameraPosition        (VGet(10,5,5))
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
void PlayerCamera::Update()
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();

    

}