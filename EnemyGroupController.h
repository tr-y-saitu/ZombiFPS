#pragma once
#include "Common.h"

class EnemyGroup;
class Stage;
class EnemyObjectPools;
class SoundManager;

/// <summary>
/// 集合したエネミーを一つにまとめる
/// </summary>
class EnemyGroupController
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyGroupController();
    
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
    void CreateEnemy(int currentWave);

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="playerPosition">プレイヤー座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR playerPosition, Stage& stage,
        bool enemySpawnFlag, int curretWave);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(VECTOR playerPosition);

    // Getter
    const int GetEnemyGroupSize()const { return activeEnemyGroup.size(); }
    const int GetEnemyKillCount()const { return enemyKillCount; }

private:
    /// <summary>
    /// 音の更新
    /// </summary>
    void UpdateSound();

    // 定数
    // TODO: エネミーウェーブコントローラーで生成数を管理する
    //       オブジェクトプールでの管理ものちに行う
    static constexpr int TestEnemyGroupNumber   = 1;    // 仮のエネミーの生成数
    static constexpr int ZombieSoundInterval    = 300;  // ゾンビの声を再生するフレーム間隔
    static constexpr int ZombieSoundTypeNumber  = 3;    // ゾンビの声の種類数

    // 変数
    SoundManager*       soundManager;       // サウンドマネージャー
    vector<EnemyGroup*> enemyGroup;         // エネミーの集合体
    list<EnemyGroup*>   activeEnemyGroup;   // 使用中のエネミーの集合体
    EnemyObjectPools*   enemyObjectPools;   // エネミーのオブジェクトプール
    int                 frameCount;         // フレームカウント
    int                 enemyKillCount;     // エネミーを殺した数
};


