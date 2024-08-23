#pragma once
#include "SceneUIBase.h"

class ImageDataManager;
class Player;
class ImageDataManager;

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

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int InteractLocationInfomationDrawPositionY    = 800;      // インタラクト情報の描画Y座標
    static constexpr int InteractLocationCostDrawPositionY          = 900;      // インタラクトできるコスト描画Y座標
    static constexpr VECTOR InteractIconDrawOffset = { 0.0f,3.0f,0.0f };        // インタラクトアイコンの描画位置のずらし量

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//]
    // 管理クラス
    ImageDataManager*   imageDataManager;   // 画像管理クラス
    
    int     vhsFilterImageHandle;   // VHSフィルター画像
    int     crosshairImageHandle;   // クロスヘア画像
    int     recImageHandle;         // REC画像

    // アイコン
    int     gunPowerUpMachineIconImageHandle;   // 銃強化マシンアイコン画像
    int     ammoBoxIconImageHandle;             // 弾薬補充箱アイコン画像
};


