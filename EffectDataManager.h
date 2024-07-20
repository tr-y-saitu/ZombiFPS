#pragma once

/// <summary>
/// �G�t�F�N�g�f�[�^�Ǘ��N���X
/// </summary>
class EffectDataManager
{
public:
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EffectDataManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectPlayManager�̃|�C���^</returns>
    static EffectDataManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EffectDataManager();
    
    // �ϐ�
    static EffectDataManager* effectDataManager;       // �G�t�F�N�g�f�[�^�N���X�̃C���X�^���X�̃A�h���X
};

