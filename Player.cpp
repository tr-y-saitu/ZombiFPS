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
    Initialize();
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
    position = VGet(0.0f, 0.0f, 0.0f);
    angle = 0.0f;
    modelHandle = MV1LoadModel("DxChara.x");
    state = State::None;
    
    // ジャンプ力は初期状態では０
    currentJumpPower = 0.0f;
    
    // 影描画用の画像の読み込み
    shadowHandle = LoadGraph("Shadow.tga");
    
    // 初期状態でプレイヤーが向くべき方向はＸ軸方向
    targetMoveDirection = VGet(1.0f, 0.0f, 0.0f);
    
    // アニメーションのブレンド率を初期化
    animBlendRate = 1.0f;
    
    // 初期状態ではアニメーションはアタッチされていないにする
    currentPlayAnim = -1;
    prevPlayAnim = -1;
    
    // ただ立っているアニメーションを再生
    // TODO: マジックナンバーの4が何なのか解析して定数化
    PlayAnim(AnimationType::None);           // HACK: 中ではアタッチとカウンタの初期化をしているだけ
}

/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <param name="palyerCamera">プレイヤーのカメラ</param>
void Player::Update(const Input& input, PlayerCamera& palyerCamera, Stage& stage)
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


// プレイヤーのアニメーションを再生する
void Player::PlayAnim(AnimationType PlayAnim)
{
    // HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
    // 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
    if (prevPlayAnim != -1)
    {
        MV1DetachAnim(modelHandle, prevPlayAnim);
        prevPlayAnim = -1;
    }

    // 今まで再生中のモーションだったものの情報をPrevに移動する
    prevPlayAnim = currentPlayAnim;
    prevAnimCount = currentAnimCount;

    // 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
    currentPlayAnim = MV1AttachAnim(modelHandle, static_cast<int>(PlayAnim));
    currentAnimCount = 0.0f;

    // ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
    animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}
