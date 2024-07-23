#include "ModelDataManager.h"

// ������
ModelDataManager* ModelDataManager::modelDataManager = NULL;

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
    // ���f���f�[�^�̍폜
    for (int i = 0; i < modelDataList.size(); i++)
    {
<<<<<<< HEAD
=======
        // ���X�g�Ƀf�[�^�������Ă����
>>>>>>> main
        if (modelDataList[(ModelDataType)i])
        {
            MV1DeleteModel(modelDataList[(ModelDataType)i]);
        }
    }
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
    modelDataList[StageModelData] = MV1LoadModel("Data/Stage/backroomsScaleMini.mv1");
    //modelDataList[PlayerModelData] = MV1LoadModel("Data/Player/playerScaleMini.mv1");
    modelDataList[PlayerModelData] = MV1LoadModel("Data/Player/playerAnimationFixed.mv1");
}

/// <summary>
/// ������g�p���Ȃ����f���f�[�^���擾����
/// </summary>
/// <param name="type">���f���̎��</param>
/// <returns>�f�[�^�n���h��</returns>
int ModelDataManager::GetOriginalModelHandle(ModelDataType type)
{
    // �I���W�i���f�[�^��n��
    return modelDataList[type];
}

/// <summary>
/// �������g�p���郂�f���f�[�^���擾����
/// </summary>
/// <param name="type">�f�[�^�̎��</param>
/// <returns>�f�[�^�n���h��</returns>
int ModelDataManager::GetDuplicatesModelHandle(ModelDataType type)
{
    // �����f�[�^��n��
    return MV1DuplicateModel(modelDataList[type]);
}