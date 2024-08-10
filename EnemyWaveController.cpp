#include "EnemyWaveController.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyWaveController::EnemyWaveController()
    : currentWaveState      (Wave1)
    , waveStartTime         (0)
    , waveElapsedTime       (0)
    , lastEnemySpawnTime    (0)
    , enemySpawnFlag        (false)
    , currentWaveSpawnCount (0)
{
    // 現在のウェーブで出現するエネミーの数
    waveEnemySpawnCount = currentWaveState * EnemySpawnRate;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyWaveController::~EnemyWaveController()
{
}

/// <summary>
/// 初期化
/// </summary>
void EnemyWaveController::Initialize()
{
    currentWaveState = Wave1;       // 現在のウェーブ設定
    waveStartTime = GetNowCount();  // ウェーブ開始時間を設定
}

/// <summary>
/// 更新
/// </summary>
void EnemyWaveController::Update(int activeEnemyNumber)
{
    // 現在使用中のエネミーがいない場合ウェーブを進める
    if (activeEnemyNumber == 0)
    {
        // 次のウェーブに進む
        currentWaveState = static_cast<WaveState>(static_cast<int>(currentWaveState) + 1);

        // ウェーブ開始時間を更新
        waveStartTime = GetNowCount();
        lastEnemySpawnTime = waveStartTime;     // 最後のエネミー出現時間を更新
        enemySpawnFlag = false;                 // 出現フラグをリセット
        currentWaveSpawnCount = 0;              // このウェーブで出現させたエネミーの数をリセット
    }

    // 現在のウェーブの経過時間を計測
    waveElapsedTime = GetNowCount() - waveStartTime;

    // レスポンス時間ごとにエネミー出現フラグを立てる
    if (GetNowCount() - lastEnemySpawnTime >= EnemySpawnResponseTime * 1000)
    {
        // 現在のウェーブで出現できるエネミーの数を越えていなければ
        if ((currentWaveState * EnemySpawnRate) >= currentWaveSpawnCount)
        {
            // 一度に存在できるエネミーの総数を越えていなければ
            if (activeEnemyNumber < EnemySpawnLimit)
            {
                // エネミーを出現させる処理
                if (!enemySpawnFlag)
                {
                    // 最後のエネミー出現時間を更新
                    lastEnemySpawnTime = GetNowCount();

                    // 出現フラグを設定
                    enemySpawnFlag = true;

                    // このウェーブで出したエネミーの数を数える
                    currentWaveSpawnCount++;
                }
            }
        }
    }
    else
    {
        // レスポンス時間内は出現フラグをリセット
        enemySpawnFlag = false;
    }

}

/// <summary>
/// 描画
/// </summary>
void EnemyWaveController::Draw()
{
    // 現在時間を描画
    DrawFormatString(100, 600, DebugFontColor, "WaveTime:%d", waveElapsedTime / WaveDurationMS);
    DrawFormatString(100, 700, DebugFontColor, "CurrentWave:%d", (int)currentWaveState);
}
