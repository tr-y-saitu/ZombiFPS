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

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//]
    // 管理クラス
    ImageDataManager*   imageDataManager;   // 画像管理クラス
    
    int     vhsFilterImageHandle;   // VHSフィルター画像
    int     crosshairImageHandle;   // クロスヘア画像
};


