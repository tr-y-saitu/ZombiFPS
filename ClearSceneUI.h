#pragma once
#include "SceneUIBase.h"

class ImageDataManager;


/// <summary>
/// クリアシーンのUI
/// </summary>
class ClearSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ClearSceneUI();

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="setScore"></param>
    /// <param name="setKillCount"></param>
    /// <param name="setWaveCount"></param>
    ClearSceneUI(int setScore, int setKillCount, int setWaveCount);

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ClearSceneUI();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ImageDataManager* imageDataManager;         // 画像管理クラス

    // 画像ハンドル
    int     goodEndBackImageHandle;             // グッドエンド用の背景画像
    int     goodEndTextImageHandle;             // グッドエンド用のテキスト画像
    VECTOR  goodEndTextPosition;                // グッドエンド用のテキスト画像の座標

    // ステータス
    int     frameCount;                         // フレームカウント

    // スコア
    int                 score;                          // スコア
    int                 killCount;                      // エネミーを殺した数
    int                 waveCount;                      // 最終ウェーブ数
};



