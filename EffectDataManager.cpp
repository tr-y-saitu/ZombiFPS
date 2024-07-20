#include "Common.h"
#include "EffectDataManager.h"

// ������
EffectDataManager* EffectDataManager::effectDataManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectDataManager::EffectDataManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectDataManager::~EffectDataManager()
{
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void EffectDataManager::CreateInstance()
{
    if (effectDataManager == NULL)
    {
        effectDataManager = new EffectDataManager();
    }
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�G�t�F�N�g�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X</returns>
EffectDataManager* EffectDataManager::GetInstance()
{
    return effectDataManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void EffectDataManager::DeleteInstance()
{
    delete(effectDataManager);
}