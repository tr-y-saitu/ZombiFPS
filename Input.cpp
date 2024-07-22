#include "Common.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Input::Input()
    : currentFrameInput     (0)
    , nowFrameNewInput      (0)
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

    // ���݂̓��͏�Ԃ��擾
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // ���݂̃t���[���ŐV���ɓ��͂��ꂽ�{�^���̃r�b�g�������Ă���l��
    // nowFrameNewInput �ɑ������
    nowFrameNewInput = currentFrameInput & ~oldFrameInput;
}