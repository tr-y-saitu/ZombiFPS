#pragma once
#include "Common.h"

/// <summary>
/// �G�t�F�N�g�Đ��Ǘ��N���X
/// </summary>
class EffectManager     final
{
public:
    /// <summary>
    /// �Đ����
    /// </summary>
    enum EffectPlayState
    {
        NoPlay = -1,    // �Đ�����Ă��Ȃ�
        Play,           // �Đ���
    };

    /// <summary>
    /// �G�t�F�N�g�̎��
    /// </summary>
    enum EffectType
    {

    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EffectManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectManager�̃|�C���^</returns>
    static EffectManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// �G�t�F�N�g�̓ǂݍ���
    /// </summary>
    void LoadEffect();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// ���ݍĐ����̃G�t�F�N�g�����邩�ǂ���
    /// </summary>
    /// <returns></returns>
    bool IsAnyEffectPlaying();

    /// <summary>
    /// �ǂݍ��񂾃G�t�F�N�g���X�g����Đ�
    /// </summary>
    /// <param name="effectType">�Đ�����G�t�F�N�g�̎��</param>
    /// <param name="playPosition">�Đ�������W</param>
    /// <param name="scale">���G�t�F�N�g�̕`��T�C�Y</param>
    /// NOTE:��3�����́uscale�v�̓f�t�H���g�����@�f�t�H���g�l{1.0f,1.0f,1.0f}
    ///      1.0f���ǂݍ��ݎ��T�C�Y
    void PlayEffectList(EffectType effectType, VECTOR playPosition, VECTOR scale = { 1.0f,1.0f,1.0f });

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EffectManager();

    // �Ǘ��p
    static EffectManager* effectManager;    // �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X
    int playingEffectHandle;                        // ���ݍĐ����̃G�t�F�N�g�̃n���h��
    vector<int> playingList;                        // ���ݍĐ����̃��X�g
    map< EffectType, int> effectList;               // �Đ�����G�t�F�N�g�̃��X�g

    // �n���h��

};

