#pragma once
#include "Common.h"

/// <summary>
/// ���f���f�[�^�Ǘ��N���X
/// </summary>
class ModelDataManager
{
public:

    /// <summary>
    /// �ǂݍ��ރf�[�^�̎��
    /// </summary>
    enum ModelDataType
    {
        StageModelData,      // �X�e�[�W���f��
    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ModelDataManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectManager�̃|�C���^</returns>
    static ModelDataManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// ������g�p���Ȃ����f���f�[�^���擾����
    /// </summary>
    /// <param name="type">���f���̎��</param>
    /// <returns>�f�[�^�n���h��</returns>
    int GetOriginalModelHandle(ModelDataType type);

    /// <summary>
    /// �������g�p���郂�f���f�[�^���擾����
    /// </summary>
    /// <param name="type">�f�[�^�̎��</param>
    /// <returns>�f�[�^�n���h��</returns>
    int GetDuplicatesModelHandle(ModelDataType type);

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ModelDataManager();

    /// <summary>
    /// ���f���f�[�^�̓ǂݍ���
    /// </summary>
    void ModelDataLoad();

    // �ϐ�
    static ModelDataManager*            modelDataManager;   // ���f���Ǘ��N���X�̃C���X�^���X�̃A�h���X
    map<ModelDataType, int>      modelDataList;      // �g�p���郂�f���f�[�^�̃��X�g

};

