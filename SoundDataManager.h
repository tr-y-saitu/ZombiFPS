#pragma once

/// <summary>
/// �T�E���h�f�[�^�Ǘ��N���X
/// </summary>
class SoundDataManager
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SoundDataManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectPlayManager�̃|�C���^</returns>
    static SoundDataManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SoundDataManager();

    // �ϐ�
    static SoundDataManager* soundDataManager;     // �T�E���h�f�[�^�}�l�[�W���[�̃C���X�^���X�̃A�h���X

};


