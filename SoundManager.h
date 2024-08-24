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
        GunAimSE,                   // 銃を構える音
        GunPowerUpShootSE,          // 銃が強化された際の発砲音

        // エネミー
        ZombieVoice1SE,             // ゾンビの声１
        ZombieVoice2SE,             // ゾンビの声２
        ZombieVoice3SE,             // ゾンビの声３

        // インタラクトオブジェクト
        RefillAmmoSE,               // 弾薬を補充した時の音
        GunPowerUpSE,               // 銃を強化した時の音
    };

    /// <summary>
    /// 再生するBGM
    /// </summary>
    enum PlaySoundBGM
    {
        // タイトル
        TitleSceneBGM,          // タイトルシーンBGM

        // ゲームシーン
        GameSceneBGM,           // ゲームシーンBGM

        // リザルトシーン
        ResultSceneBGM,         // リザルトシーンBGM

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
    void PlaySoundListSE(PlaySoundSE soundType);

    /// <summary>
    /// 読み込んだサウンドリストから効果音再生（ループ再生したい効果音用）
    /// </summary>
    /// <param name="soundType">再生したい効果音の種類</param>
    void PlaySoundListSETypeLoop(PlaySoundSE soundType);

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
    static SoundManager*    soundManager;           // サウンドマネージャークラスのインスタンス
    int                     playingSoundHandle;     // 現在再生中のサウンド
    vector<int>             playingList;            // 現在再生中のサウンドリスト
    map<PlaySoundSE, int>   soundListSE;            // 再生する効果音のリスト
    map<PlaySoundBGM, int>  soundListBGM;           // 再生するBGMのリスト

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


