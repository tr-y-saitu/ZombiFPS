#pragma once
#include "SceneBase.h"

class Input;
class ImageDataManager;
class ModleDataManager;
class EffectDataManager;
class SoundDataManager;
class EffectPlayManager;
class SoundPlayManager;
class CollisionManager;
class Stage;
class Player;
class PlayerCamera;
class EnemyGroupController;
class EnemyWaveController;
class EnemyObjectPools;
class MaxAmmo;
class IncomeDouble;
class GameSceneUI;

/// <summary>
///  ゲームシーン
/// </summary>
class GameScene : public SceneBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// シーンのアップデート
    /// </summary>
    /// <returns>次のシーンのポインタ</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UIの描画
    /// </summary>
    void DrawUI() override;

    /// <summary>
    /// サウンドの更新
    /// </summary>
    void UpdateSound();

    /// <summary>
    /// エフェクトの更新
    /// </summary>
    void UpdateEffect();

private:
    // 定数

    // 変数
    // 入力処理
    Input*              input;              // 入力判定処理

    // データ関連
    ImageDataManager*   imageDataManager;   // 画像データ
    ModleDataManager*   modleDataManager;   // モデルデータ
    EffectDataManager*  effectDataManager;  // エフェクトデータ
    SoundDataManager*   soundDataManager;   // サウンドデータ
    
    // 演出関連
    EffectPlayManager*  effectPlayManager;  // エフェクト再生用
    SoundPlayManager*   soundPlayManager;   // サウンド再生用

    // オブジェクト関連
    CollisionManager*   collisionManager;   // 当たり判定
    Stage*              stage;              // ステージ
    Player*             player;             // プレイヤー
    PlayerCamera*       playerCamera;       // プレイヤー専用カメラ
    
    // エネミー関連
    EnemyGroupController*   enemyGroupController;   // エネミーの群れ
    EnemyWaveController*    enemyWaveController;    // エネミーのウェーブ管理
    EnemyObjectPools*       enemyObjectPools;       // エネミーのオブジェクトプール

    // アイテム関連
    MaxAmmo*                maxAmmoItem;            // 弾薬マックスアイテム
    IncomeDouble*           incomeDoubleItem;       // ポイント２倍アイテム

    // UI関連
    GameSceneUI*        gameSceneUI;        // ゲームシーン用のUI

};


