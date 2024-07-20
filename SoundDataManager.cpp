#include "Common.h"
#include "SoundDataManager.h"

// ������
SoundDataManager* SoundDataManager::soundDataManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundDataManager::SoundDataManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundDataManager::~SoundDataManager()
{
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void SoundDataManager::CreateInstance()
{
    if (soundDataManager == NULL)
    {
        soundDataManager = new SoundDataManager();
    }
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�摜�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X</returns>
SoundDataManager* SoundDataManager::GetInstance()
{
    return soundDataManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void SoundDataManager::DeleteInstance()
{
    delete(soundDataManager);
}