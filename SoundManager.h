#pragma once
#include "Common.h"

/// <summary>
/// サウンドマネージャー
/// </summary>
/// MEMO:シングルトンクラス
class SoundManager  final
{
public:
    /// <summary>
    /// 再生する効果音
    /// </summary>
    enum SoundEffectType
    {
        // システム
        PUSH_SE,                    // ボタン入力音
        ShutterOpenSE,              // シャッターを開けたときの音
        MoneyUseSE,                 // お金を使った時の音

        // プレイヤー
        PlayerDamageSE,             // プレイヤーが攻撃を受けたときの音
        PlayerWalkingSE,            // プレイヤーが歩く音
        PlayerRunSE,                // プレイヤーが走る音

        // 銃
        AssaulRifleShootingSE,      // アサルトライフル発砲音
        BattleRifleShootingSE,      // バトルライフル発砲音
        SubmachineGunShootingSE,    // サブマシンガン発砲音
        GunReloadStartSE,           // リロード開始音
        GunReloadEndSE,             // リロード終了音
        EnemyHitSE,                 // エネミーに当たった時の音
        MissShootingSE,             // 弾丸が当たらなかった音
        DryFireSE,                  // マガジン内の弾丸がない状態でトリガーを引いた時の音

        // エネミー
        ZombieVoice1SE,             // ゾンビの声１
        ZombieVoice2SE,             // ゾンビの声２
        ZombieVoice3SE,             // ゾンビの声３
    };

    /// <summary>
    /// ループ再生したいサウンド
    /// </summary>
    enum LoopSoundType
    {
        // プレイヤー
        WalkingBGM,              // 歩く音
        RunBGM,                  // 走る音
    };

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SoundManager();

    /// <summary>
    /// インスタンス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// サウンドマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>SoundManagerのポインタ</returns>
    static SoundManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// サウンドデータの読み込み
    /// </summary>
    void LoadData();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 再生中の音をすべて止める
    /// </summary>
    void StopAllSounds();

    /// <summary>
    /// 読み込んだサウンドリストから効果音再生
    /// </summary>
    /// <param name="soundType">再生したい効果音の種類</param>
    void PlaySoundListSE(SoundEffectType soundType);

    /// <summary>
    /// 読み込んだサウンドリストから効果音再生（ループ再生したい効果音用）
    /// </summary>
    /// <param name="soundType">再生したい効果音の種類</param>
    void PlaySoundListSETypeLoop(SoundEffectType soundType);

    /// <summary>
    /// 読み込んだサウンドリストからループ再生
    /// </summary>
    /// <param name="soundType">ループ再生したい音の種類</param>
    void PlaySoundListBGM(LoopSoundType soundType);

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundManager();

    // 管理用
    static SoundManager*    soundManager;           // サウンドマネージャークラスのインスタンス
    int                     playingSoundHandle;     // 現在再生中のサウンド
    vector<int>             playingList;            // 現在再生中のサウンドリスト
    map<SoundEffectType, int>   soundListSE;        // 再生する効果音のリスト
    map<LoopSoundType, int>  soundListBGM;          // 再生するループサウンドのリスト

    //                  サウンドデータ                  //
    // 共通
    int     pushuSE;            // ボタンを押したときの音

    // タイトルシーン
    int     titleSceneBGM;      // タイトルシーンのBGM

    // ゲームシーン
    int     gameSceneBGM;       // ゲームシーンのBGM

    // クリアシーン
    int     clearSceneBGM;      // クリアシーンのBGM
    int     clearFinishBGM;     // クリア演出音
};


