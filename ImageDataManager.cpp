#include "Common.h"
#include "ImageDataManager.h"

// ������
ImageDataManager* ImageDataManager::imageDataManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ImageDataManager::ImageDataManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ImageDataManager::~ImageDataManager()
{
    // �摜�f�[�^�̍폜
    for (int i = 0; i < imageDataList.size(); i++)
    {
        if (imageDataList[(ImageDataType)i])
        {
            DeleteGraph(imageDataList[(ImageDataType)i]);
        }
    }
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void ImageDataManager::CreateInstance()
{
    if (imageDataManager == NULL)
    {
        imageDataManager = new ImageDataManager();
    }
}

/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�摜�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X</returns>
ImageDataManager* ImageDataManager::GetInstance()
{
    return imageDataManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void ImageDataManager::DeleteInstance()
{
    delete(imageDataManager);
}

/// <summary>
/// �摜�f�[�^�̓ǂݍ���
/// </summary>
void ImageDataManager::ImageDataLoad()
{

}

/// <summary>
/// �g�p�������摜�f�[�^���擾����
/// </summary>
/// <param name="type">�f�[�^�̎��</param>
/// <returns>�f�[�^�n���h��</returns>
int ImageDataManager::GetImageHandle(ImageDataType type)
{
    return imageDataList[type];
}