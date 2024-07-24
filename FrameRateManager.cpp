#include "Common.h"
#include "FrameRateManager.h"

// 初期化
FrameRateManager* FrameRateManager::frameRateManager = NULL;

// コストラクタ
FrameRateManager::FrameRateManager()
    : fpsCountStartTime     (0)
    , nowFpsCount           (0)
    , deltaTime             (0)
{

}

/// <summary>
/// デストラクタ
/// </summary>
FrameRateManager::~FrameRateManager()
{
    // 処理なし
}

/// <summary>
/// インスタンスを作成
/// </summary>
void FrameRateManager::CreateInstance()
{
    if (frameRateManager == NULL)
    {
        frameRateManager = new FrameRateManager();
    }
}

/// <summary>
/// フレームレートマネージャーのインスタンスのポインタを返す
/// </summary>
/// <returns>インスタンスのあるアドレス</returns>
FrameRateManager* FrameRateManager::GetInstance()
{
    return frameRateManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void FrameRateManager::DeleteInstance()
{
    delete(frameRateManager);
}

/// <summary>
/// 更新
/// </summary>
void FrameRateManager::Update()
{
    // 1フレーム目なら時刻を記憶
    if (nowFpsCount == 0)
    {
        fpsCountStartTime = GetNowCount();	//基準となる時間を決める
    }
    // 60フレーム目なら平均を計算する
    if (nowFpsCount == (float)SetFPS)
    {
        int nowTime = GetNowCount();		//今の時間を設定
        deltaTime = 1000.f / ((nowTime - fpsCountStartTime) / (float)SetFPS);	//１フレームにかかった時間を計算
        nowFpsCount = 0;					//フレームのカウントを初期化
    }
    else
    {
        nowFpsCount++;
    }
}

/// <summary>
/// 待機処理
/// </summary>
void FrameRateManager::SleepForFPS()
{
    //かかった時間
    int _tookTime = GetNowCount() - fpsCountStartTime;
    //待つべき時間
    int _waitTime = nowFpsCount * 1000 / SetFPS - _tookTime;

    //待つべき時間待機する
    if (_waitTime > 0)
    {
        Sleep(_waitTime);
    }
}