#include "SoundPlayManager.h"

// ������
SoundPlayManager* SoundPlayManager::soundPlayManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundPlayManager::SoundPlayManager()
    : playingSoundHandle(0)
{
    // �T�E���h�f�[�^�ǂݍ���
    LoadData();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundPlayManager::~SoundPlayManager()
{
    DeleteSoundMem(pushuSE);
    DeleteSoundMem(titleSceneBGM);
    DeleteSoundMem(gameSceneBGM);
    DeleteSoundMem(clearSceneBGM);
}

/// <summary>
/// �T�E���h�f�[�^�̓ǂݍ���
/// </summary>
void SoundPlayManager::LoadData()
{
    // ���ʉ�
    pushuSE = LoadSoundMem("data/sound/Common/pushuSE.mp3");
    soundListSE[PUSH_SE] = pushuSE;
    // BGM
    titleSceneBGM = LoadSoundMem("data/sound/TitleScene/TitleSceneBGM1.mp3");
    gameSceneBGM = LoadSoundMem("data/sound/GameScene/GameSceneBMG1.mp3");
    clearSceneBGM = LoadSoundMem("data/sound/ClearScene/ClearSceneBGM.mp3");
    clearFinishBGM = LoadSoundMem("data/sound/ClearScene/gameClearSE.mp3");
    soundListBGM[TITLE_SCENE_BGM] = titleSceneBGM;
    soundListBGM[GAME_SCENE_BGM] = gameSceneBGM;
    soundListBGM[CLEAR_SCENE_BGM] = clearSceneBGM;
    soundListBGM[CLEAR_FINISH_BGM] = clearFinishBGM;
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void SoundPlayManager::CreateInstance()
{
    if (soundPlayManager == NULL)
    {
        soundPlayManager = new SoundPlayManager();
    }
}

/// <summary>
/// �T�E���h�}�l�[�W���[�N���X�̃C���X�^���X�|�C���^��n��
/// </summary>
SoundPlayManager* SoundPlayManager::GetInstance()
{
    return soundPlayManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void SoundPlayManager::DeleteInstance()
{
    delete(soundPlayManager);
}

/// <summary>
/// �X�V
/// </summary>
void SoundPlayManager::Update()
{

}

/// <summary>
/// �Đ����̉������ׂĎ~�߂�
/// </summary>
void SoundPlayManager::StopAllSounds()
{
    // �Đ����̃T�E���h��T��
    for (int i = playingList.size() - 1; i >= 0; i--)
    {
        if (CheckSoundMem(playingList[i]))
        {
            StopSoundMem(playingList[i]);               // ��~
        }
        playingList.erase(playingList.begin() + i);     // �폜
    }
}

/// <summary>
/// �ǂݍ��񂾃T�E���h���X�g������ʉ��Đ�
/// </summary>
/// <param name="soundType">�Đ����������ʉ��̎��</param>
void SoundPlayManager::PlaySoundListSE(PlaySoundSE soundType)
{
    playingSoundHandle = soundListSE[soundType];
    playingList.push_back(playingSoundHandle);
    PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// �ǂݍ��񂾃T�E���h���X�g����BGM�Đ�
/// </summary>
/// <param name="soundType">�Đ�������BGM�̎��</param>
void SoundPlayManager::PlaySoundListBGM(PlaySoundBGM soundType)
{
    playingSoundHandle = soundListBGM[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_LOOP, true);
    }
}

