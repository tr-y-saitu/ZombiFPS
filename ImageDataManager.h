#pragma once

/// <summary>
/// 画像データ読み込みクラス
/// </summary>
class ImageDataManager
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ImageDataManager();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// エフェクトマネージャーのインスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectManagerのポインタ</returns>
    static ImageDataManager* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ImageDataManager();


    // 変数
    static ImageDataManager* imageDataManager;
};

