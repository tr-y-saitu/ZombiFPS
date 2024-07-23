#pragma once
#include "Common.h"

/// <summary>
/// �摜�f�[�^�ǂݍ��݃N���X
/// </summary>
class ImageDataManager
{
public:
    enum ImageDataType
    {

    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ImageDataManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectManager�̃|�C���^</returns>
    static ImageDataManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// �g�p�������摜�f�[�^���擾����
    /// </summary>
    /// <param name="type">�f�[�^�̎��</param>
    /// <returns>�f�[�^�n���h��</returns>
    static int GetImageHandle(ImageDataType type);

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ImageDataManager();

    /// <summary>
    /// �摜�f�[�^�̓ǂݍ���
    /// </summary>
    void ImageDataLoad();


    // �ϐ�
    static ImageDataManager*        imageDataManager;   // �摜�f�[�^�Ǘ��N���X�̃C���X�^���X�̃A�h���X
    static map<ImageDataType, int>  imageDataList;      // �g�p����摜�̃f�[�^���X�g
};

