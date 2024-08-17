#pragma once
#include "Common.h"

/// <summary>
/// 画像データ読み込みクラス
/// </summary>
class ImageDataManager
{
public:
    /// <summary>
    /// 読み込むデータの種類
    /// </summary>
    enum ImageDataType
    {
        West1ImageData  ,       // 西の部屋１
        West2ImageData  ,       // 西の部屋２
        West3ImageData  ,       // 西の部屋３
        West4ImageData  ,       // 西の部屋４
        Center1ImageData,       // 中央の部屋１
        Center2ImageData,       // 中央の部屋２
        Center3ImageData,       // 中央の部屋３
        Center4ImageData,       // 中央の部屋４
        East1ImageData  ,       // 東の部屋１
        East2ImageData  ,       // 東の部屋２
        East3ImageData  ,       // 東の部屋３
        East4ImageData  ,       // 東の部屋４
        VHSFiltersImageData,    // VHSフィルター
        CrosshairImageData,     // 銃のクロスヘア
        RECImageData,           // REC(録画)
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
    int GetImageHandle(ImageDataType type);

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
    map<ImageDataType, int>  imageDataList;      // 使用する画像のデータリスト
};

