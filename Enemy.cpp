#include "CollisionManager.h"
#include "Enemy.h"
#include "ModelDataManager.h"
#include "Stage.h"
#include "Calculation.h"

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
    : hitPoints                 (InitializeHitPoints)
    , currentPlayAnimation      (-1)
    , previousPlayAnimation     (-1)
    , animationBlendRate        (1.0f)
    , targetMoveDirection       (InitializeDirection)
    , currentJumpPower          (0.0f)
    , currentState              (State::Run)
    , position                  (InitializePosition)
    , targetNextPosition        (InitializePosition)
    , isTouchingRoomCenter      (false)
    , isActive                  (true)
    , deathFrameCount           (0)
{
    modelDataManager = ModelDataManager::GetInstance();
    collisionManager = CollisionManager::GetInstance();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
    MV1DeleteModel(modelHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize()
{
    // モデルハンドルを取得
    modelHandle = modelDataManager->GetDuplicatesModelHandle(ModelDataManager::ModelDataType::EnemyModelData);

    // モデルサイズを再設定
    MV1SetScale(modelHandle, EnemyScale);

    // 初期状態でエネミーが向くべき方向はＸ軸方向
    targetMoveDirection = VGet(1.0f, 0.0f, 0.0f);

    // アニメーション関係
    currentPlayAnimation = -1;
    previousPlayAnimation = -1;
    animationBlendRate = 1.0f;

    // アニメーション設定
    PlayAnimation(AnimationType::Run);

    // 当たり判定用情報更新
    UpdateCollisionData();          // 自身の当たり判定
    UpdateAttackCollisionData();    // 攻撃用の当たり判定

    // 初期化時にいる部屋を設定
    previousRoom.roomNumber = Pathfinding::Center1;
    roomEntryState = Pathfinding::MovingToNextRoom;

    // ステータス
    hitPoints = InitializeHitPoints;

    // 死亡してからの経過フレーム数を初期化
    deathFrameCount = 0;

    // 自身のOnHit関数をもとに新しい引数を持った関数を作成
    // std::bind(&名前空間::関数名,その関数のある参照,引数の数だけプレースホルダーが増える)
    collisionData.onHit = std::bind(&Enemy::OnHit, this, std::placeholders::_1);                // 胴体
    attackCollisionData.onHit = std::bind(&Enemy::OnHitAttack, this, std::placeholders::_1);    // 攻撃

    // 当たり判定に必要なデータを渡す
    collisionManager->RegisterCollisionData(&collisionData);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="targetPosition">目標座標</param>
/// <param name="stage">ステージ</param>
void Enemy::Update(VECTOR targetPosition,Stage& stage,ObjectTag targetTag)
{
    // ルートフレームのＺ軸方向の移動パラメータを無効にする
    DisableRootFrameZMove();

    // 移動
    UpdateMoveVector(targetPosition);
    Move(targetMoveDirection, stage);

    // 回転制御
    UpdateAngle();

    // 死んだかどうかのチェック
    UpdateDead();

    // 攻撃の更新
    UpdateAttack(targetPosition,targetTag);

    // アニメーション更新
    UpdateAnimation();

    // 座標設定
    MV1SetPosition(modelHandle, position);

    // 当たり判定用情報更新
    UpdateCollisionData();
    UpdateAttackCollisionData();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw()
{
    // 自身のモデルを描画
    MV1DrawModel(modelHandle);

    // カプセル型の当たり判定描画
    DrawCapsule3D(collisionData.startPosition, collisionData.endPosition,
        collisionData.radius, PolygonDetail, DebugPolygonColorRed, DebugPolygonColorRed, false);

    // 自身のHPを描画
    DrawFormatString(DebugHitPointDrawX, DebugHitPointDrawY,
        DebugFontColor, "HP:%d", hitPoints);

    // 攻撃の当たり判定を描画する
    if (attackCollisionData.isCollisionActive)
    {
        DrawSphere3D(attackCollisionData.centerPosition, attackCollisionData.radius,
            DebugSphereDivision, DebugPolygonColorBlue, DebugPolygonColorBlue, true);
    }
}

/// <summary>
/// オブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData">オブジェクトのデータ</param>
void Enemy::OnHit(CollisionData hitObjectData)
{
    VECTOR direction;
    float distance;
    float radiusSum;
    float penetrationDepth;

    switch (hitObjectData.tag)
    {
    case ObjectTag::Bullet: // 弾丸と当たった時
        // HPを減少
        hitPoints -= hitObjectData.bulletPower;

        break;

    case ObjectTag::EnemyBoby:  // エネミーと当たった時
        // 押し出し処理を行う

        // 進行方向を計算 (相手の位置から自分の位置を引いて方向ベクトルを求める)
        VECTOR direction = VSub(position, hitObjectData.centerPosition);

        // 方向ベクトルを正規化する（長さを1にする）
        direction = VNorm(direction);
        direction.y = 0.0f;  // Y方向の成分を無視

        // 自分と相手の距離を計算
        distance = VSize(VSub(position, hitObjectData.centerPosition));

        // 自分と相手の半径の合計
        radiusSum = collisionData.radius + hitObjectData.radius;

        // めり込んだ分を計算 (半径の合計 - 距離)
        penetrationDepth = radiusSum - distance;

        // めり込んだ分だけ方向に押し戻す
        if (penetrationDepth > 0)
        {
            position = VAdd(position, VScale(direction, penetrationDepth));
        }

        break;

    default:
        break;
    }
}

/// <summary>
/// 攻撃がオブジェクトと接触した時の処理
/// </summary>
/// <param name="hitObjectData"></param>
void Enemy::OnHitAttack(CollisionData hitObjectData)
{
    if (hitObjectData.tag == ObjectTag::Player)
    {
        attackCollisionData.isCollisionActive = false;  // 非アクティブ化
    }
}

/// 当たり判定に必要なデータの更新
/// </summary>
void Enemy::UpdateCollisionData()
{
    // タグを設定
    collisionData.tag = ObjectTag::EnemyBoby;

    // 座標をもとにカプセルを作成
    collisionData.startPosition = VAdd(position, CapsulePositionOffset);
    collisionData.endPosition = position;

    // カプセルの半径を登録
    collisionData.radius = CollisionRadius;
}

/// <summary>
/// 攻撃の当たり判定に必要なデータの更新
/// </summary>
void Enemy::UpdateAttackCollisionData()
{

    attackCollisionData.centerPosition      = position;                 // 座標
    attackCollisionData.centerPosition.y    = 4.5f;                     // Y座標をプレイヤーに合わせる

    attackCollisionData.tag                 = ObjectTag::EnemyAttack;   // エネミーの攻撃である
    attackCollisionData.radius              = AttackCollisionRadius;    // 攻撃の当たり判定の半径
    attackCollisionData.attackPower         = AttackPower;              // 攻撃力
}

/// <summary>
/// ルートフレームのZ軸方向の移動パラメータを無効にする
/// </summary>
void Enemy::DisableRootFrameZMove()
{
    // HACK:
    // ・DXライブラリのモデルファイル内には、複数のメッシュ（ポリゴンの集合）やカメラ、ライトを入れることができる
    // ・置いた複数のファイルは、親子関係をつけたり、Unityのヒエラルキーみたいに、階層構造が作れる
    // ・この階層それぞれには名前が付けられる Root-Meshes-Model1
    //                                                   |-Model2
    // ・この名前の付いた階層のことをDXライブラリではフレームという
    // ・一番親の階層を「ルートフレーム」と呼ぶ。ルートフレームは一つ

    MATRIX localMatrix;

    // ユーザー行列を解除する
    // MEMO:
    // コード記入者がmodelHandleにMATRIXで回転変換を行ったものを、デフォルトに戻す
    MV1ResetFrameUserLocalMatrix(modelHandle, 2);

    // 現在のルートフレームの行列を取得する
    // MEMO:
    // すでにMATRIXを使用して回転していた回転量を返す
    localMatrix = MV1GetFrameLocalMatrix(modelHandle, 2);

    // Ｚ軸方向の平行移動成分を無効にする
    // m[0][3] はX軸方向の平行移動成分
    // m[1][3] はY軸方向の平行移動成分
    // m[2][3] はZ軸方向の平行移動成分
    localMatrix.m[3][2] = 0.0f;

    // ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
    MV1SetFrameUserLocalMatrix(modelHandle, 2, localMatrix);
}

/// <summary>
/// 移動ベクトルの更新
/// </summary>
/// <param name="targetPosition">向かうべき座標</param>
void Enemy::UpdateMoveVector(VECTOR targetPosition)
{
    // ターゲット座標から現在の位置への方向ベクトルを計算
    VECTOR direction = VSub(targetPosition, position);

    // Y軸方向の移動は無視
    direction.y = 0.0f;

    // 方向ベクトルを正規化
    direction = VNorm(direction);

    // 移動ベクトルを更新
    targetMoveDirection = direction;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="MoveVector">移動ベクトル</param>
/// <param name="stage">ステージ</param>
void Enemy::Move(const VECTOR& MoveVector, Stage& stage)
{
    // 死亡していたら無視
    if (currentState != State::Death)
    {
        // 当たり判定をして、新しい座標を保存する
        VECTOR oldPosition = position;                      // 移動前の座標
        VECTOR nextPosition = VAdd(position, VScale(MoveVector, MoveSpeed));   // 移動後の座標

        // ステージとの当たり判定処理
        position = stage.IsHitCollisionEnemy(*this, nextPosition, MoveVector);

        // 床より少し高くする
        if (position.y <= MoveLimitY)
        {
            position.y = MoveLimitY;
        }

        // 座標の更新
        MV1SetPosition(modelHandle, position);
    }
}

/// <summary>
/// 回転制御
/// </summary>
void Enemy::UpdateAngle()
{
    // ターゲットから現在の位置への方向を計算
    targetMoveDirection.y = 0.0f;   // 上方向の回転は無視

    // 方向ベクトルを正規化
    targetMoveDirection = VNorm(targetMoveDirection);

    // モデルの回転行列を作成
    // TODO:
    // targetMoveDirectionをマイナスしないとモデルが逆を向くのでどうにかしたい
    MATRIX rotation = MGetRotY(atan2(-targetMoveDirection.x, -targetMoveDirection.z));

    // モデルを回転
    MV1SetFrameUserLocalMatrix(modelHandle, 0, rotation);
}

/// <summary>
/// 死んだかどうかチェックし、死んだ後の更新
/// </summary>
void Enemy::UpdateDead()
{
    // HPがゼロになった場合
    if (hitPoints < 0)
    {
        // 現在のアニメーションが Death でない場合のみ再生
        if (currentState != State::Death)
        {
            // 死亡アニメーションを再生
            PlayAnimation(AnimationType::Death);

            // 現在のステート更新
            currentState = State::Death;
        }

        // 死んでからのフレーム数をカウント
        deathFrameCount++;

        // 死亡してから一定フレームが経過した場合は削除する
        if (deathFrameCount > DeathInactiveFrame)
        {
            isActive = false;
        }
    }
}

/// <summary>
/// 攻撃の更新
/// </summary>
/// <param name="playerPosition">ターゲットの座標</param>
void Enemy::UpdateAttack(VECTOR targetPosition, ObjectTag targetTag)
{
    // プレイヤーとエネミーとの距離を図る
    if (targetTag == ObjectTag::Player)
    {
        // 距離を図る
        VECTOR playerPosition = targetPosition;
        playerPosition.y = 1.0f;
        float distance = Calculation::Distance3D(playerPosition, position);

        // 距離が近ければ攻撃する
        if (distance < AttackRange)
        {
            if (currentState != State::Attack)
            {
                // 攻撃アニメーション再生
                PlayAnimation(AnimationType::Attack);

                // 現在のステート更新
                currentState = State::Attack;
            }
        }
        else if (currentState == State::Attack) // 攻撃アニメーションの終了判定
        {
            // 再生しているアニメーションの総時間
            float animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnimation);

            // 当たり判定を出現させる
            if (currentAnimationCount >= animationTotalTime / 3 && !attackCollisionData.isCollisionActive)
            {
                // 攻撃当たり判定を行う
                attackCollisionData.isCollisionActive = true;
                collisionManager->RegisterCollisionData(&attackCollisionData);
            }

            // 攻撃アニメーションが終了しているかチェック
            if (currentAnimationCount >= animationTotalTime / 2)
            {
                // Runアニメーションに変更
                PlayAnimation(AnimationType::Run);

                // 現在のステートをRunに更新
                currentState = State::Run;

                // 攻撃アニメーションが終了したら当たり判定も消す
                attackCollisionData.isCollisionActive = false;
            }
        }

    }

}

/// <summary>
/// アニメーションを新しく再生する
/// </summary>
/// <param name="type">アニメーションの種類</param>
void Enemy::PlayAnimation(AnimationType type)
{
    // HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
    // 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
    if (previousPlayAnimation != -1)
    {
        MV1DetachAnim(modelHandle, previousPlayAnimation);
        previousPlayAnimation = -1;
    }

    // 今まで再生中のモーションだったものの情報をPrevに移動する
    previousPlayAnimation = currentPlayAnimation;
    previousAnimationCount = currentAnimationCount;

    // 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
    currentPlayAnimation = MV1AttachAnim(modelHandle, static_cast<int>(type));
    currentAnimationCount = 0.0f;

    // ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
    animationBlendRate = previousPlayAnimation == -1 ? 1.0f : 0.0f;
}

/// <summary>
/// アニメーション処理
/// </summary>
void Enemy::UpdateAnimation()
{
    float animationTotalTime;       // 再生しているアニメーションの総時間

    // ブレンド率が１以下の場合は１に近づける
    if (animationBlendRate < 1.0f)
    {
        animationBlendRate += AnimationBlendSpeed;
        if (animationBlendRate > 1.0f)
        {
            animationBlendRate = 1.0f;
        }
    }

    // 再生しているアニメーション１の処理
    if (currentPlayAnimation != -1)
    {
        // アニメーションの総時間を取得
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnimation);

        // 再生時間を進める
        currentAnimationCount += PlayAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (currentAnimationCount >= animationTotalTime)
        {
            currentAnimationCount = static_cast<float>(fmod(currentAnimationCount, animationTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(modelHandle, currentPlayAnimation, currentAnimationCount);

        // アニメーション１のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnimation, animationBlendRate);
    }

    // 再生しているアニメーション２の処理
    if (previousPlayAnimation != -1)
    {
        // アニメーションの総時間を取得
        animationTotalTime = MV1GetAttachAnimTotalTime(modelHandle, previousPlayAnimation);

        // 再生時間を進める
        previousAnimationCount += PlayAnimationSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (previousAnimationCount > animationTotalTime)
        {
            previousAnimationCount = static_cast<float>(fmod(previousAnimationCount, animationTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(modelHandle, previousPlayAnimation, previousAnimationCount);

        // アニメーション２のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(modelHandle, previousPlayAnimation, 1.0f - animationBlendRate);
    }
}

