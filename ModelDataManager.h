#pragma once
#include "Common.h"

/// <summary>
/// モデルデータ管理クラス
/// </summary>
class ModelDataManager
{
public:

    /// <summary>
    /// 読み込むデータの種類
    /// </summary>
    enum ModelDataType
    {
        StageModelData,      // ステージモデル
    };

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

    /// <summary>
    /// 一つしか使用しないモデルデータを取得する
    /// </summary>
    /// <param name="type">モデルの種類</param>
    /// <returns>データハンドル</returns>
    int GetOriginalModelHandle(ModelDataType type);

    /// <summary>
    /// 複製し使用するモデルデータを取得する
    /// </summary>
    /// <param name="type">データの種類</param>
    /// <returns>データハンドル</returns>
    int GetDuplicatesModelHandle(ModelDataType type);

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ModelDataManager();

    /// <summary>
    /// モデルデータの読み込み
    /// </summary>
    void ModelDataLoad();

    // 変数
    static ModelDataManager*            modelDataManager;   // モデル管理クラスのインスタンスのアドレス
    map<ModelDataType, int>      modelDataList;      // 使用するモデルデータのリスト

};

