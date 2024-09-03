#pragma once
#include "Common.h"

// 当たり判定の情報を持った構造体を宣言するヘッダー

struct LineCollisionData;
struct SphereCollisionData;
struct CapsuleCollisionData;

class HitObjectAddress
{

};

/// <summary>
/// オブジェクトの種別
/// </summary>
enum class ObjectTag : int
{
    Player,                 // プレイヤー
    Enemy,                  // エネミー
    EnemyHead,              // エネミーの頭
    EnemyBoby,              // エネミーの胴体
    Bullet,                 // 弾丸
    RoomCenter,             // 部屋の中心
    EnemyAttack,            // エネミーの攻撃
    Shutter,                // シャッター
    AmmoBox,                // 弾薬補充箱
    GunPowerUpMachine,      // 銃強化マシン
    PlayerPowerUpMachine,   // プレイヤー強化マシン
};

/// <summary>
/// 当たり判定用情報
/// </summary>
struct CollisionData
{
    // タグ
    ObjectTag   tag;                    // このオブジェクトが何なのかのタグ(Player、Enemy、Bullet）

    // 球用
    VECTOR      centerPosition;         // 球の中心座標
    float       attackPower;            // このオブジェクトの攻撃力

    // カプセル用
    VECTOR      startPosition;          // カプセルを形成し始める座標
    VECTOR      endPosition;            // カプセルの形成を終わる座標
    float       radius;                 // カプセルの半径

    // 線形用
    VECTOR      lineStartPosition;      // 線の始点
    VECTOR      lineEndPosition;        // 線の終点
    int         bulletPower;            // 弾丸の威力

    // インタラクト
    float       interactRadius;         // そのオブジェクトにアクセルできる半径
    int         interactionCost;        // そのオブジェクトのインタラクトにかかるコスト
    bool        isInteracted;           // インタラクトを行ったかどうか

    std::function<void(CollisionData)> onHit;   // 当たった時に行われる処理
    bool        isCollisionActive;              // 当たり判定を適用させたいかどうか

    HitObjectAddress* objectAddress;
};

