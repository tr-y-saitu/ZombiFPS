#pragma once
#include "Common.h"

class EnemyGroup;
class Stage;
class EnemyObjectPools;

/// <summary>
/// 集合したエネミーを一つにまとめる
/// </summary>
class EnemyGroupController
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    EnemyGroupController();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="playerAddMoney">プレイヤーの所持金を増加させる関数ポインタ</param>
    EnemyGroupController(std::function<void(int)> playerAddMoney);
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyGroupController();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// エネミーを作成する
    /// </summary>
    void CreateEnemy();

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="playerPosition">プレイヤー座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR playerPosition, Stage& stage,bool enemySpawnFlag);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(VECTOR playerPosition);

    // Getter
    const int GetEnemyGroupSize()const { return activeEnemyGroup.size(); }

private:
    // 定数
    // TODO: エネミーウェーブコントローラーで生成数を管理する
    //       オブジェクトプールでの管理ものちに行う
    static constexpr int TestEnemyGroupNumber = 1;  // 仮のエネミーの生成数

    // 変数
    vector<EnemyGroup*> enemyGroup;         // エネミーの集合体
    list<EnemyGroup*>   activeEnemyGroup;   // 使用中のエネミーの集合体
    EnemyObjectPools*   enemyObjectPools;   // エネミーのオブジェクトプール
};


