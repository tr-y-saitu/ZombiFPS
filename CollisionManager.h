#pragma once
#include "Common.h"


/// <summary>
/// �l�蔻�菈���N���X
/// </summary>
class CollisionManager  final
{
public:
    /// <summary>
    /// ���`�����蔻��p�\����
    /// </summary>
    struct SphureCollider
    {
        VECTOR  position;   // ���g�̍��W
        float   radius;     // ���g���^�����蔻��̔��a
    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CollisionManager();

    /// <summary>
    /// �C���X�^�X�쐬
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
    /// </summary>
    /// <returns>EffectPlayManager�̃|�C���^</returns>
    static CollisionManager* GetInstance();

    /// <summary>
    /// �C���X�^���X�̍폜
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// ���ׂĂ̓����蔻�菈��
    /// </summary>
    void Update();

private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CollisionManager();

    // �Ǘ��p
    static CollisionManager* collisionManager;      // �R���W�����}�l�[�W���[�̃C���X�^���X

    // �����蔻��p�f�[�^

};

