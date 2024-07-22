#include "Stage.h"
#include "Shutter.h"
#include "Player.h"


Stage::Stage()
{
    // ������
    Initialize();
}

Stage::~Stage()
{
}

/// <summary>
/// ������
/// </summary>
void Stage::Initialize()
{
	// �X�e�[�W���f���̓ǂݍ���
	modelHandle = MV1LoadModel("BO2Map0716.mv1");
	MV1SetScale(modelHandle, VGet(4, 4, 4));

	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo(modelHandle, -1);

	isCreatedHitDim = false;
}

/// <summary>
/// �I��������
/// </summary>
void Stage::Finalize()
{
	// �X�e�[�W���f���̌�n��
	MV1DeleteModel(modelHandle);
	if (isCreatedHitDim)
	{
		MV1CollResultPolyDimTerminate(hitDim);
		isCreatedHitDim = false;
	}
}

void Stage::Draw()
{

}


void Stage::IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector)
{
}


