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
    , canSwichWave          (false)
    , waveChangeStartTime   (0)
    , isWaitingWaveChange   (false)
{
    // 現在のウェーブで出現するエネミーの数
    waveEnemySpawnCount = currentWaveState * EnemySpawnRate;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyWaveController::~EnemyWaveController()
{
    // 処理なし
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
void EnemyWaveController::Update(int activeEnemyCount)
{
    // 現在時間を取得
    int currentTime = GetNowCount();

    // 現在使用中のエネミーがいない場合ウェーブを進める
    if (activeEnemyCount == 0 && canSwichWave)
    {
        // ウェーブが切り替わるのを少し待つ
        if (!isWaitingWaveChange)
        {
            // ウェーブ切り替え開始時間を記録
            waveChangeStartTime = currentTime;
            isWaitingWaveChange = true;
        }
        else if(currentTime - waveChangeStartTime >= EnemySpawnDelayMS)
        {
            // 次のウェーブに進む
            currentWaveState = static_cast<WaveState>(static_cast<int>(currentWaveState) + 1);

            // ウェーブ開始時間を更新
            waveStartTime = GetNowCount();
            lastEnemySpawnTime = waveStartTime;     // 最後のエネミー出現時間を更新
            enemySpawnFlag = false;                 // 出現フラグをリセット
            currentWaveSpawnCount = 0;              // このウェーブで出現させたエネミーの数をリセット
            canSwichWave = false;                   // 連続でウェーブが変わらないようにする
        }
    }

    // 現在のウェーブの経過時間を計測
    waveElapsedTime = GetNowCount() - waveStartTime;

    // エネミーが出現可能か確認 //
    
    // レスポンス時間ごとにエネミー出現フラグを立てる
    bool isSpawnTime = GetNowCount() - lastEnemySpawnTime >= EnemySpawnResponseTime;

    // 現在のウェーブで出現できるエネミーの数を越えていなければ
    bool isLimitSpawnCountInWave = (currentWaveState * EnemySpawnRate) <= currentWaveSpawnCount;

    // 一度に存在できるエネミーの総数を越えていなければ
    bool isLimitSpawnCount = activeEnemyCount > EnemySpawnLimit;

    // すべて可能であればエネミーは出現できる
    bool canSpawnEnemy = isSpawnTime && !isLimitSpawnCountInWave && !isLimitSpawnCount && !enemySpawnFlag;

    // エネミーを出現させる処理
    if (canSpawnEnemy)
    {
        // ウェーブを切り替え可能かどうか
        canSwichWave = true;

        // 最後のエネミー出現時間を更新
        lastEnemySpawnTime = GetNowCount();

        // 出現フラグを設定
        enemySpawnFlag = true;

        // このウェーブで出したエネミーの数を数える
        currentWaveSpawnCount++;
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
    /*DrawFormatString(100, 600, DebugFontColor, "WaveTime:%d", waveElapsedTime / 1000);
    DrawFormatString(100, 700, DebugFontColor, "CurrentWave:%d", (int)currentWaveState);*/
}
