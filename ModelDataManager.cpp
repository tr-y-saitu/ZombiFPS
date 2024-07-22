#include "ModelDataManager.h"

// ������
ModelDataManager* ModelDataManager::modelDataManager = NULL;
map<ModelDataManager::ModelDataType, int> ModelDataManager::modelDataList;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelDataManager::ModelDataManager()
{
    // ���f���f�[�^�̓ǂݍ���
    ModelDataLoad();
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

/// <summary>
/// ���f���f�[�^�̓ǂݍ���
/// </summary>
void ModelDataManager::ModelDataLoad()
{
    modelDataList[StageModelData] = MV1LoadModel("Data/Stage/BO2Map0716.mv1");
}

/// <summary>
/// �g�p���������f���f�[�^���擾����
/// </summary>
/// <param name="type">�f�[�^�̎��</param>
/// <returns>�f�[�^�n���h��</returns>
int ModelDataManager::GetModelHandle(ModelDataType type)
{
    // �����f�[�^��n��
    return MV1DuplicateModel(modelDataList[type]);
}