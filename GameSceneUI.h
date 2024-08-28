#pragma once
#include "SceneUIBase.h"
#include "EnemyWaveController.h"

class ImageDataManager;
class Player;

/// <summary>
/// ゲームシーンのUI
/// </summary>
class GameSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSceneUI();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameSceneUI();

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
    void Draw(Player& player,int waveState);

    /// <summary>
    /// バッドエンドの演出更新
    /// </summary>
    /// <returns>演出が終了したかどうか</returns>
    bool UpdateBadEnd();

    /// <summary>
    /// グッドエンドの演出更新
    /// </summary>
    /// <returns>演出が終了したかどうか</returns>
    bool UpdateGoodEnd();

private:
    /// <summary>
    /// プレイヤーの情報を描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawPlayerInformation(Player& player);

    /// <summary>
    /// 現在のウェーブステートを描画する
    /// </summary>
    /// <param name="waveState">現在のウェーブステート</param>
    void DrawWaveState(int waveState);

    /// <summary>
    /// 銃の情報を描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawGunInformation(Player& player);

    /// <summary>
    /// 残弾数が少なくなったことを警告描画する
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawLowAmmoWarning();

    /// <summary>
    /// 予備弾薬が少なくなった場合のアナウンス表示
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawLowBackUpAmmoWarning(Player& player);

    /// <summary>
    /// プレイヤーのインタラクトできるステート情報を描画する
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawPlayerInteractState(Player& player);

    /// <summary>
    /// プレイヤーの所持金を描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawPlayerMoney(Player& player);

    /// <summary>
    /// プレイヤーのヒットポイントを描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawPlayerHitPoint(Player& player);

    /// <summary>
    /// リロード情報を描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawReloadInfomation(Player& player);

    /// <summary>
    /// プレイヤーの銃のクロスヘアの描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawCrosshair(Player& player);

    /// <summary>
    /// プレイヤーの装備中の銃の名称を描画
    /// </summary>
    /// <param name="player">プレイヤー</param>
    void DrawEquippedGunName(Player& player);

    /// <summary>
    /// ビデオ風の情報を画面に描画
    /// </summary>
    void DrawVHSInformation();

    /// <summary>
    /// オブジェクトのインタラクト費用を描画
    /// </summary>
    /// <param name="interactionCost">インタラクト費用</param>
    void DrawInteractionCost(int interactionCost);

    /// <summary>
    /// インタラクトできるオブジェクトのアイコンを描画
    /// </summary>
    void DrawInteractIcon();

    /// <summary>
    /// アイコン画像のずらし量更新
    /// </summary>
    float UpdateIconOffset();

    

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // 文字
    static constexpr int    InteractLocationInfomationDrawPositionY = 800;      // インタラクト情報の描画Y座標
    static constexpr int    InteractLocationCostDrawPositionY       = 900;      // インタラクトできるコスト描画Y座標
    // ウェーブステート
    static constexpr int    CurrentWaveStateDrawPositionX           = 150;      // 現在のウェーブステートの描画X位置
    static constexpr int    CurrentWaveStateDrawPositionY           = 850;      // 現在のウェーブステートの描画Y位置
    const int               CurrentWaveStateFontColor               = GetColor(200, 0, 0);  // 現在のウェーブステートの文字色
    // 武器情報
    static constexpr int    GunInformationDrawPositionX             = 1600;     // 銃の情報を描画するX座標
    static constexpr int    GunInformationDrawPositionY             = 950;      // 銃の情報を描画するY座標
    static constexpr int    AmmoLow                                 = 5;        // 銃の総弾数が少ない
    static constexpr int    AmmoHalfRate                            = 2;        // 銃の総弾数を半分にするための値
    static constexpr int    LowAmmoWarningTextBlinkInterval         = 300;      // 銃の総弾数が少なくなった時の警告表示の点滅間隔
    static constexpr int    LowAmmoWarningTextDrawPositionY         = 300;      // 銃の総弾数が少なくなった時の警告表示の描画Y位置
    // 武器強化マシン
    static constexpr VECTOR GunPowerUpMachineIconDrawOffset         = { 0.0f,3.0f,0.0f };   // 武器強化マシンのアイコン描画ずらし量
    // 弾薬補充箱
    static constexpr VECTOR AmmoBoxIconDrawOffset                   = { 0.0f,4.0f,0.0f };   // 弾薬補充箱のアイコンの描画ずらし量
    static constexpr float  AmmoBoxIconDrawCenterXRate = 0.5f;
    // アイコン
    static constexpr float  IconOffsetRange                         = 0.5f;     // アイコンのオフセットの振幅
    static constexpr float  IconOffsetCycle                         = 0.05f;    // アイコンのオフセットする周期（フレームごとの変化量）
    static constexpr float  IconDrawCenterXRate                     = 0.5f;     // 画像内の中心比率X
    static constexpr float  IconDrawCenterYRate                     = 0.0f;     // 画像内の中心比率Y
    static constexpr float  IconSize                                = 3.0f;     // アイコン描画サイズ
    static constexpr float  IconAngle                               = 0.0f;     // アイコンの描画角度
    // プレイヤー
    static constexpr int    HitPointBarDrawPositionX                = 1600;     // ヒットポイント描画X位置
    static constexpr int    HitPointBarDrawPositionY                = 910;      // ヒットポイント描画Y位置
    static constexpr int    HitPointBarMaxWidth                     = 350;      // ヒットポイントバーの最大幅
    static constexpr int    HitPointBarHeight                       = 30;       // ヒットポイントバーの高さ
    static constexpr int    HitPointBarFrameThickness               = 5;        // ヒットポイントバーの枠の太さ
    const int               HitPointBarColor                        = GetColor(0, 255, 0);  // ヒットポイントバーの色
    // リロード
    static constexpr int    ReloadBarWidth                          = 500;      // リロード進行状態を知らせるバーの幅
    static constexpr int    ReloadBarHeight                         = 40;       // リロード進行状態を知らせるバーの高さ
    static constexpr int    ReloadInfomationDrawPositionY           = 600;      // リロード情報文字の描画Y位置
    // バッドエンド
    static constexpr float  BadEndTime                              = 6000.0f;  // バッドエンドを行う時間
    static constexpr float  BadEndImageExpansionSpeed               = 1.0f;     // バッドエンド画像の拡大速度
    static constexpr float  BadEndMaximumExpansion                  = 1.5f;     // バッドエンド画像の最大拡大率

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス
    ImageDataManager*   imageDataManager;       // 画像管理クラス
    
    int     vhsFilterImageHandle;               // VHSフィルター画像
    int     crosshairImageHandle;               // クロスヘア画像
    int     recImageHandle;                     // REC画像

    // アイコン
    int     frameCount;                         // フレームカウント
    int     gunPowerUpMachineIconImageHandle;   // 銃強化マシンアイコン画像
    int     ammoBoxIconImageHandle;             // 弾薬補充箱アイコン画像

    // プレイヤーHP
    int     hitFilterImageHandle;               // 被弾時のフィルター画像
    float   previousHitPoint;                   // 前フレームのヒットポイント
    float   redBarWidth;                        // 赤色のバーの幅
    int     redBarAnimationFrame;               // 赤色ののアニメーションフレーム数

    // 総弾数警告
    bool    visibleAmmoLowWarningText;          // 総弾数警告描画されているか
    int     ammoLowWarningTextPreviousTime;     // 総弾数警告描画が前回表示していた時間

    // ウェーブ
    map<EnemyWaveController::WaveState, int>  waveImageDataList;     // ウェーブの画像リスト

    // バッドエンド,グッドエンド
    int     badEndImageHandle;                  // バッドエンド画像
    int     goodEndImageHandle;                 // グッドエンド画像
    float   endImageExpansion;                  // バッドエンド画像の拡大率
    int     endTimer;                           // バッドエンド演出用計測時間
    bool    endStarted;                         // バッドエンド演出が開始されたかどうか
};


