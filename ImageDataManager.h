#pragma once
#include "Common.h"

/// <summary>
/// 画像データ読み込みクラス
/// </summary>
class ImageDataManager
{
public:
    enum ImageDataType
    {

    };

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

    /// <summary>
    /// 使用したい画像データを取得する
    /// </summary>
    /// <param name="type">データの種類</param>
    /// <returns>データハンドル</returns>
    static int GetImageHandle(ImageDataType type);

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ImageDataManager();

    /// <summary>
    /// 画像データの読み込み
    /// </summary>
    void ImageDataLoad();


    // 変数
    static ImageDataManager*        imageDataManager;   // 画像データ管理クラスのインスタンスのアドレス
    static map<ImageDataType, int>  imageDataList;      // 使用する画像のデータリスト
};

