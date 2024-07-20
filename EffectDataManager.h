#pragma once

/// <summary>
/// エフェクトデータ管理クラス
/// </summary>
class EffectDataManager
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectDataManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectPlayManagerのポインタ</returns>
    static EffectDataManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectDataManager();
    
    // 変数
    static EffectDataManager* effectDataManager;       // エフェクトデータクラスのインスタンスのアドレス
};

