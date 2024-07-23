#include "CollisionManager.h"

// ������
CollisionManager* CollisionManager::collisionManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// �C���X�^���X�̍쐬
/// </summary>
void CollisionManager::CreateInstance()
{
    if (collisionManager == NULL)
    {
        collisionManager = new CollisionManager();
    }
}

/// <summary>
/// �R���W�����}�l�[�W���̃C���X�^���X�̃|�C���^��n��
/// </summary>
/// <returns></returns>
CollisionManager* CollisionManager::GetInstance()
{
    return collisionManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void CollisionManager::DeleteInstance()
{
    delete(collisionManager);
}

/// <summary>
/// ������
/// </summary>
void CollisionManager::Initialize()
{
    
}

/// <summary>
/// ���ׂĂ̓����蔻�菈��
/// </summary>
void CollisionManager::Update()
{

}