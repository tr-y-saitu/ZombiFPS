#pragma once
#include "Common.h"

/// <summary>
/// デバッグ表示クラス
/// </summary>
/// MEMO:シングルトン
class DebugLogger final
{
public:
    /// <summary>
    /// デバッグ表示したい情報
    /// </summary>
    struct DebugPrintData
    {
        string  objectName; // オブジェクトの名前
        string  dataType;   // データの種類
        float   floatData;  // float型情報
        VECTOR  vector;     // VECTOR型情報
    };

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~DebugLogger();

    /// <summary>
    /// インスタス作成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// インスタンスのポインタを渡す
    /// </summary>
    /// <returns>EffectManagerのポインタ</returns>
    static DebugLogger* GetInstance();

    /// <summary>
    /// インスタンスの削除
    /// </summary>
    static void DeleteInstance();

    /// <summary>
    /// デバッグ表示リストに登録する
    /// </summary>
    /// <param name="data">登録するデータ</param>
    static void RegisterDebugData(DebugPrintData* data);

    /// <summary>
    /// 更新
    /// </summary>
    static void Update();

    /// <summary>
    /// デバッグ情報リストをクリアにする
    /// </summary>
    static void ClearDebugDataList();

    /// <summary>
    /// 入力更新
    /// </summary>
    static void UpdateKeyState();

private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DebugLogger();


    // 変数
    static DebugLogger* debugLogger;    // デバッグ表示クラスのインスタンス
    static vector<DebugPrintData*> debugDataList;   // デバッグ表示したいリスト

    // 入力関係
    static bool     isKeyOn;            // キー入力されたか
    static bool     isKeyRelease;       // キー入力が離れたか
    static bool     isPreviousKeyOn;    // 前フレームでキー入力があったか
};


