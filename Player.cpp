#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerOnHitEnemyState.h"
#include "PlayerRunState.h"
#include "PlayerWalkState.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
    : position      (VGet(0,0,0))
{
    playerState = new PlayerIdleState();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
    delete(playerState);
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <param name="palyerCamera">プレイヤーのカメラ</param>
void Player::Update(Input& input, PlayerCamera& palyerCamera)
{

}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{

}

/// <summary>
/// 天井に接触した時の処理
/// </summary>
void Player::OnHitRoof()
{

}

/// <summary>
/// 床に当たった時の処理
/// </summary>
void Player::OnHitFloor()
{

}

/// <summary>
/// 落下が確定した時の処理
/// </summary>
void Player::OnFall()
{

}



