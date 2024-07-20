#pragma once
#include "Common.h"

/// <summary>
/// �T�E���h�}�l�[�W���[
/// </summary>
/// MEMO:�V���O���g���N���X
class SoundPlayManager  final
{
public:
    /// <summary>
    /// �Đ�������ʉ�
    /// </summary>
    enum PlaySoundSE
    {
        PUSH_SE,            // �{�^�����͉�
    };

    /// <summary>
    /// �Đ�����BGM
    /// </summary>
    enum PlaySoundBGM
    {
        TITLE_SCENE_BGM,    // �^�C�g���V�[����BGM
        GAME_SCENE_BGM,     // �Q�[���V�[����BGM
        CLEAR_SCENE_BGM,    // �N���A�V�[����BGM
        CLEAR_FINISH_BGM,   // �I����
    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SoundPlayManager();

    /// <summary>
    /// �C���X�^���X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �T�E���h�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>SoundPlayManager�̃|�C���^</returns>
    static SoundPlayManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// �T�E���h�f�[�^�̓ǂݍ���
    /// </summary>
    void LoadData();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �Đ����̉������ׂĎ~�߂�
    /// </summary>
    void StopAllSounds();

    /// <summary>
    /// �ǂݍ��񂾃T�E���h���X�g������ʉ��Đ�
    /// </summary>
    /// <param name="soundType">�Đ����������ʉ��̎��</param>
    void PlaySoundListSE(PlaySoundSE soundType);

    /// <summary>
    /// �ǂݍ��񂾃T�E���h���X�g����BGM�Đ�
    /// </summary>
    /// <param name="soundType">�Đ�������BGM�̎��</param>
    void PlaySoundListBGM(PlaySoundBGM soundType);

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SoundPlayManager();

    // �Ǘ��p
    static SoundPlayManager* soundPlayManager;      // �T�E���h�}�l�[�W���[�N���X�̃C���X�^���X
    int playingSoundHandle;                 // ���ݍĐ����̃T�E���h
    vector<int> playingList;                // ���ݍĐ����̃T�E���h���X�g
    map<PlaySoundSE, int> soundListSE;    // �Đ�������ʉ��̃��X�g
    map<PlaySoundBGM, int> soundListBGM;  // �Đ�����BGM�̃��X�g

    //                  �T�E���h�f�[�^                  //
    // ����
    int     pushuSE;            // �{�^�����������Ƃ��̉�

    // �^�C�g���V�[��
    int     titleSceneBGM;      // �^�C�g���V�[����BGM

    // �Q�[���V�[��
    int     gameSceneBGM;       // �Q�[���V�[����BGM

    // �N���A�V�[��
    int     clearSceneBGM;      // �N���A�V�[����BGM
    int     clearFinishBGM;     // �N���A���o��
};


