#pragma once

/// <summary>
/// モデルデータ管理クラス
/// </summary>
class ModelDataManager
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ModelDataManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectManagerのポインタ</returns>
    static ModelDataManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ModelDataManager();

    // 変数
    static ModelDataManager* modelDataManager;     // モデル管理クラスのインスタンスのアドレス

};

