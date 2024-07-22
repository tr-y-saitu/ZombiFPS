#pragma once


/// <summary>
/// �t���[�����[�g�Ǘ��N���X
/// </summary>
/// MOME:�V���O���g��
class FrameRateManager  final
{
public:
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FrameRateManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectManager�̃|�C���^</returns>
    static FrameRateManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �ҋ@����
    /// </summary>
    void SleepForFPS();

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FrameRateManager();

    // �萔
    static constexpr int SetFPS = 60;          // �ݒ肵��FPS�l

    // �ϐ�
    static FrameRateManager* frameRateManager;  // �t���[�����[�g�}�l�[�W���[�̃C���X�^���X
    int     nowFpsCount;                        // ���݂̃t���[����
    int     fpsCountStartTime;                  // �t���[���J�E���g���n�߂�����
    float   deltaTime;                          // �P�t���[���ɂ�����������

};

