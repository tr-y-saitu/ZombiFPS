#include "Common.h"
#include "Input.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
Input::Input()
    : currentFrameInput     (0)
    , nowFrameNewInput      (0)
    , mousePosition         ({0,0})
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Input::~Input()
{
    // �����Ȃ�
}

/// <summary>
/// �X�V
/// </summary>
void Input::Update()
{
    // ��O�̃t���[���̓��͂�ۑ�
    int oldFrameInput;
    oldFrameInput = currentFrameInput;

#ifdef USE_MOUSE
    // �}�E�X�œ��͏�Ԃ��X�V
    UpdateMouse();
#else
    // �p�b�h�A�L�[�{�[�h����
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
#endif

    // ���݂̃t���[���ŐV���ɓ��͂��ꂽ�{�^���̃r�b�g�������Ă���l��
    // nowFrameNewInput �ɑ������
    nowFrameNewInput = currentFrameInput & ~oldFrameInput;
}

/// <summary>
/// �}�E�X�ł̍X�V����
/// </summary>
/// MEMO�F
/// �}�E�X�̓X�N���[�������ɌŒ肷��
void Input::UpdateMouse()
{
    // ���͍X�V
    //currentFrameInput = GetMouseInput();                  // �N���b�N
    GetMousePoint(&mousePosition.x, &mousePosition.y);      // �J�[�\��

    // �ړ������L�[����
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �X�N���[�������ɌŒ�
    SetMousePoint(ScreenWidthHalf, ScreenHeightHalf);
}