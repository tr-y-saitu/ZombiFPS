#include "Stage.h"
#include "Shutter.h"
#include "Player.h"


Stage::Stage()
{
    // 初期化
    Initialize();
}

Stage::~Stage()
{
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize()
{
	// ステージモデルの読み込み
	modelHandle = MV1LoadModel("BO2Map0716.mv1");
	MV1SetScale(modelHandle, VGet(4, 4, 4));

	// モデル全体のコリジョン情報のセットアップ
	MV1SetupCollInfo(modelHandle, -1);

	isCreatedHitDim = false;
}

/// <summary>
/// 終了時処理
/// </summary>
void Stage::Finalize()
{
	// ステージモデルの後始末
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


