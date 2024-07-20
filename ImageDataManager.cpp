#include "Common.h"
#include "ImageDataManager.h"

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