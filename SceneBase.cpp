#include "SceneBase.h"
#include "TitleScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
}

/// <summary>
/// �x�[�X�̏�����
/// </summary>
/// <returns>�ŏ��Ɏn�߂�V�[���̃|�C���^</returns>
SceneBase* SceneBase::InitializeBase()
{
    return new TitleScene();
}

/// <summary>
/// ������
/// </summary>
void SceneBase::Initialize()
{

}
