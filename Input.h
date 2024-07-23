#pragma once

#define USE_MOUSE       // �}�E�X���g�p����

/// <summary>
/// ���͊Ǘ��N���X
/// </summary>
class Input
{
public:
    struct MousePosition
    {
        int x;      // X���W
        int y;      // Y���W
    };

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

    /// <summary>
    /// �}�E�X�ł̍X�V����
    /// </summary>
    void UpdateMouse();

    // �Q�b�^�[
    int GetCurrentFrameInput() const { return currentFrameInput; }
    int GetNowNewFrameInput() const { return nowFrameNewInput; }
    const MousePosition GetMousePosition() const { return mousePosition; }

    // �萔
    static constexpr float MouseSensitivity = 0.005f;        // �}�E�X���x

private:

    // �ϐ�
    int     currentFrameInput;      // ���݂̃t���[���ŉ�����Ă��{�^��
    int     nowFrameNewInput;       // ���݂̃t���[���ŐV���ɓ��͂��ꂽ�{�^��
    MousePosition mousePosition;    // �}�E�X�̍��W
};

