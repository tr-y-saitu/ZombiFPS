#pragma once
#include "Common.h"

class EnemyObjectPools;

/// <summary>
/// エネミーの出現ウェーブを管理する
/// </summary>
class EnemyWaveController
{
public:
    /// <summary>
    /// ゲームの全ウェーブ
    /// </summary>
    enum WaveState
    {
        Wave1 = 1,      // ウェーブ１
        Wave2,          // ウェーブ２
        Wave3,          // ウェーブ３
        Wave4,          // ウェーブ４
        Wave5,          // ウェーブ５
        Wave6,          // ウェーブ６
        Wave7,          // ウェーブ７
        Wave8,          // ウェーブ８
        Wave9,          // ウェーブ９
        Wave10,         // ウェーブ１０
        WaveEnd,        // ウェーブ終了
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyWaveController();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyWaveController();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();
    
    /// <summary>
    /// 更新
    /// </summary>
    void Update(int activeEnemyCount);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    // Getter
    const bool GetEnemySpawnFlag()const { return enemySpawnFlag; }

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int EnemySpawnLimit            = 15;   // 同時に存在できるエネミーの数
    static constexpr int EnemySpawnResponseTime     = 1;    // 敵の出現頻度
    static constexpr int EnemySpawnRate             = 5;    // 現在のウェーブにこの値を掛けてそのウェーブに出現するエネミーの数を決定する
    static constexpr int WaveDurationMS             = 1000; //
    static constexpr int EnemySpawnDelayMS          = 5000; // ウェーブが切り替わってからエネミーが出現するまでの時間

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    int         waveStartTime;          // ウェーブの開始時間
    int         waveElapsedTime;        // 現在のウェーブの経過時間
    int         waveEnemySpawnCount;    // このウェーブで何体のエネミーを出現させるか
    WaveState   currentWaveState;       // 現在のウェーブステート
    int         lastEnemySpawnTime;     // 最後にエネミーを出現させた時間
    bool        enemySpawnFlag;         // エネミーを出現させる指示
    int         currentWaveSpawnCount;  // 現在のウェーブで出現させたエネミーの数
};


