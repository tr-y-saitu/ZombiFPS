#pragma once

/// <summary>
/// ���͊Ǘ��N���X
/// </summary>
class Input
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Input();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Input();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    // �Q�b�^�[
    int GetCurrentFrameInput() const { return currentFrameInput; }
    int GetNowNewFrameInput() const { return nowFrameNewInput; }

private:
    // �ϐ�
    int     currentFrameInput;      // ���݂̃t���[���ŉ�����Ă��{�^��
    int     nowFrameNewInput;       // ���݂̃t���[���ŐV���ɓ��͂��ꂽ�{�^��
};

