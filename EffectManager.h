#pragma once
#include "Common.h"

/// <summary>
/// エフェクト再生管理クラス
/// </summary>
class EffectManager     final
{
public:
    /// <summary>
    /// 再生状態
    /// </summary>
    enum EffectPlayState
    {
        NoPlay = -1,    // 再生されていない
        Play,           // 再生中
    };

    /// <summary>
    /// エフェクトの種類
    /// </summary>
    enum EffectType
    {

    };

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectManagerのポインタ</returns>
    static EffectManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// エフェクトの読み込み
    /// </summary>
    void LoadEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 現在再生中のエフェクトがあるかどうか
    /// </summary>
    /// <returns></returns>
    bool IsAnyEffectPlaying();

    /// <summary>
    /// 読み込んだエフェクトリストから再生
    /// </summary>
    /// <param name="effectType">再生するエフェクトの種類</param>
    /// <param name="playPosition">再生する座標</param>
    /// <param name="scale">※エフェクトの描画サイズ</param>
    /// NOTE:第3引数の「scale」はデフォルト引数　デフォルト値{1.0f,1.0f,1.0f}
    ///      1.0fが読み込み時サイズ
    void PlayEffectList(EffectType effectType, VECTOR playPosition, VECTOR scale = { 1.0f,1.0f,1.0f });

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectManager();

    // 管理用
    static EffectManager* effectManager;    // エフェクトマネージャーのインスタンス
    int playingEffectHandle;                        // 現在再生中のエフェクトのハンドル
    vector<int> playingList;                        // 現在再生中のリスト
    map< EffectType, int> effectList;               // 再生するエフェクトのリスト

    // ハンドル

};

