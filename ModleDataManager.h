#pragma once

/// <summary>
/// ���f���f�[�^�Ǘ��N���X
/// </summary>
class ModleDataManager
{
public:
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ModleDataManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectPlayManager�̃|�C���^</returns>
    static ModleDataManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ModleDataManager();

    // �ϐ�
    static ModleDataManager* modleDataManager;     // ���f���Ǘ��N���X�̃C���X�^���X�̃A�h���X

};

