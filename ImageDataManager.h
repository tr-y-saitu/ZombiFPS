#pragma once

/// <summary>
/// �摜�f�[�^�ǂݍ��݃N���X
/// </summary>
class ImageDataManager
{
public:
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

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ImageDataManager();


    // �ϐ�
    static ImageDataManager* imageDataManager;
};

