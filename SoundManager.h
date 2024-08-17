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
    enum PlaySoundSE
    {
        // システム
        PUSH_SE,                    // ボタン入力音
        ShutterOpenSE,              // シャッターを開けたときの音
        MoneyUseSE,                 // お金を使った時の音

        // プレイヤー
        WalkingSE,                  // 歩く音
        RunSE,                      // 走る音
        PlayerDamageSE,             // プレイヤーが攻撃を受けたときの音

        // 銃
        AssaulRifleShootingSE,      // アサルトライフル発砲音
        BattleRifleShootingSE,      // バトルライフル発砲音
        SubmachineGunShootingSE,    // サブマシンガン発砲音
        GunReloadStartSE,           // リロード開始音
        GunReloadEndSE,             // リロード終了音
        EnemyHitSE,                 // エネミーに当たった時の音
        MissShootingSE,             // 弾丸が当たらなかった音

        // エネミー
        ZombieVoice1SE,             // ゾンビの声１
        ZonbieVoice2SE,             // ゾンビの声２
        ZonbieVoice3SE,             // ゾンビの声３
    };

    /// <summary>
    /// 再生するBGM
    /// </summary>
    enum PlaySoundBGM
    {
        TITLE_SCENE_BGM,    // タイトルシーンのBGM
        GAME_SCENE_BGM,     // ゲームシーンのBGM
        CLEAR_SCENE_BGM,    // クリアシーンのBGM
        CLEAR_FINISH_BGM,   // 終了音
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
    void PlaySoundListSE(PlaySoundSE soundType);

    /// <summary>
    /// 読み込んだサウンドリストからBGM再生
    /// </summary>
    /// <param name="soundType">再生したいBGMの種類</param>
    void PlaySoundListBGM(PlaySoundBGM soundType);

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundManager();

    // 管理用
    static SoundManager* soundManager;      // サウンドマネージャークラスのインスタンス
    int playingSoundHandle;                 // 現在再生中のサウンド
    vector<int> playingList;                // 現在再生中のサウンドリスト
    map<PlaySoundSE, int> soundListSE;    // 再生する効果音のリスト
    map<PlaySoundBGM, int> soundListBGM;  // 再生するBGMのリスト

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


