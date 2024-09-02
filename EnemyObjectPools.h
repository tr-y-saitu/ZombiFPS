#pragma once
#include "Common.h"
#include "Enemy.h"
#include "EnemyGroup.h"

class Enemy;

/// <summary>
/// エネミーのオブジェクトプール
/// </summary>
class EnemyObjectPools
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    EnemyObjectPools();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="playerAddMoney">プレイヤーの所持金を増加させる関数ポインタ</param>
    EnemyObjectPools(std::function<void(int)> playerAddMoney);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyObjectPools();

    /// <summary>
    /// 現在未使用のエネミーがあるかどうか調べる
    /// </summary>
    /// <returns>未使用のエネミーがある:true   ない:false</returns>
    bool HasInactiveEnemyInstance();

    /// <summary>
    /// 未使用のエネミーのインスタンスを渡す
    /// </summary>
    /// <returns>未使用のエネミーがあればそのインスタンス　　無ければnullptr</returns>
    EnemyGroup* GetInactiveEnemy();

    /// <summary>
    /// 使用中のリストから未使用リストにインスタンスを移動する
    /// </summary>
    /// <param name="activeEnemy">移動したい使用中のリストのアドレス</param>
    void ReturnActiveEnemyInstance(list<EnemyGroup*>& activeEnemy);

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int EnemyTotalNumber = 20;   // エネミーの総合数

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    list<EnemyGroup*> inactiveEnemy;     // 未使用のエネミー

};

