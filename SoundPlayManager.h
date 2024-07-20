#pragma once
#include "Common.h"

/// <summary>
/// サウンドマネージャー
/// </summary>
/// MEMO:シングルトンクラス
class SoundPlayManager  final
{
public:
    /// <summary>
    /// 再生する効果音
    /// </summary>
    enum PlaySoundSE
    {
        PUSH_SE,            // ボタン入力音
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
    virtual ~SoundPlayManager();

    /// <summary>
    /// インスタンス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// サウンドマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>SoundPlayManagerのポインタ</returns>
    static SoundPlayManager* GetInstance();

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
    SoundPlayManager();

    // 管理用
    static SoundPlayManager* soundPlayManager;      // サウンドマネージャークラスのインスタンス
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


