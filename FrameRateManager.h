#pragma once


/// <summary>
/// フレームレート管理クラス
/// </summary>
/// MOME:シングルトン
class FrameRateManager  final
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FrameRateManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectManagerのポインタ</returns>
    static FrameRateManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 待機処理
    /// </summary>
    void SleepForFPS();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FrameRateManager();

    // 定数
    static constexpr int SetFPS = 60;          // 設定したFPS値

    // 変数
    static FrameRateManager* frameRateManager;  // フレームレートマネージャーのインスタンス
    int     nowFpsCount;                        // 現在のフレーム数
    int     fpsCountStartTime;                  // フレームカウントを始めた時間
    float   deltaTime;                          // １フレームにかかった時間

};

