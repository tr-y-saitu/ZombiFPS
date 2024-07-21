#pragma once
#include "Common.h"


/// <summary>
/// �l�蔻�菈���N���X
/// </summary>
class CollisionManager
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

};

