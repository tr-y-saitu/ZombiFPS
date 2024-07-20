#include "Common.h"
#include "ModleDataManager.h"

// ������
ModleDataManager* ModleDataManager::modleDataManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModleDataManager::ModleDataManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModleDataManager::~ModleDataManager()
{
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void ModleDataManager::CreateInstance()
{
    if (modleDataManager == NULL)
    {
        modleDataManager = new ModleDataManager();
    }
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�摜�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X</returns>
ModleDataManager* ModleDataManager::GetInstance()
{
    return modleDataManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void ModleDataManager::DeleteInstance()
{
    delete(modleDataManager);
}