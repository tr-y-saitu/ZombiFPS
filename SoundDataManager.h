#pragma once

/// <summary>
/// サウンドデータ管理クラス
/// </summary>
class SoundDataManager
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SoundDataManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectPlayManagerのポインタ</returns>
    static SoundDataManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SoundDataManager();

    // 変数
    static SoundDataManager* soundDataManager;     // サウンドデータマネージャーのインスタンスのアドレス

};


