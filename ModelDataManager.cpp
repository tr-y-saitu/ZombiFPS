#include "Common.h"
#include "ModelDataManager.h"

// ������
ModelDataManager* ModelDataManager::modelDataManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelDataManager::ModelDataManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelDataManager::~ModelDataManager()
{
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void ModelDataManager::CreateInstance()
{
    if (modelDataManager == NULL)
    {
        modelDataManager = new ModelDataManager();
    }
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�摜�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X</returns>
ModelDataManager* ModelDataManager::GetInstance()
{
    return modelDataManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void ModelDataManager::DeleteInstance()
{
    delete(modelDataManager);
}