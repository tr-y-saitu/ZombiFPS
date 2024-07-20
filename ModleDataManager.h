#pragma once

/// <summary>
/// モデルデータ管理クラス
/// </summary>
class ModleDataManager
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ModleDataManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectPlayManagerのポインタ</returns>
    static ModleDataManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ModleDataManager();

    // 変数
    static ModleDataManager* modleDataManager;     // モデル管理クラスのインスタンスのアドレス

};

