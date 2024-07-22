#pragma once
#include "Common.h"

class Player;
class Shutter;
class ModelDataManager;


/// <summary>
/// ステージ
/// </summary>
class Stage
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Stage();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Stage();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 終了時処理
    /// </summary>
    void Finalize();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 当たり判定
    /// </summary>
    /// <param name="player">プレイヤー</param>
    /// <param name="checkPosition">当たり判定をしたい対象</param>
    /// <param name="moveVector">移動方向</param>
    void IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector);

    // ゲッター
    int GetModelHandle() const { return modelHandle; }

private:
    /// <summary>
    /// 判定処理する壁と床のポリゴン数を検出する
    /// </summary>
    /// <param name="CheckPosition">判定する座標</param>
    void AnalyzeWallAndFloor(const VECTOR& CheckPosition);

    /// <summary>
    /// 壁ポリゴンとの当たり判定をチェックし、そこからずらす量を返す
    /// </summary>
    /// <param name="player">プレイヤー</param>
    /// <param name="CheckPosition">当たり判定する座標</param>
    /// <returns>補正する移動ベクトル</returns>
    VECTOR CheckHitWithWall(Player& player, const VECTOR& CheckPosition);

    /// <summary>
    /// 床ポリゴンとの当たり判定をチェックし、そこからずらす量を返す
    /// </summary>
    /// <param name="player">プレイヤー</param>
    /// <param name="CheckPosition">当たり判定する座標</param>
    /// <returns>補正する移動ベクトル</returns>
    VECTOR CheckHitWithFloor(Player& player, const VECTOR& CheckPosition);
    

    // 定数
    // 当たり判定
    static constexpr int    SelectCollisionEntire = -1;             // モデル全体にコリジョンを適用させる
    static const int        MaxHitColl = 2048;                      // 処理するコリジョンポリゴンの最大数
    static constexpr float  DefaultSize = 800.0f;                   // 周囲のポリゴン検出に使用する球の初期サイズ
    static constexpr float  HitWidth = 200.0f;                      // 当たり判定カプセルの半径
    static constexpr float  HitHeight = 700.0f;                     // 当たり判定カプセルの高さ
    static constexpr int    HitTryNum = 16;                         // 壁押し出し処理の最大試行回数
    static constexpr float  HitSlideLength = 5.0f;                  // 一度の壁押し出し処理でスライドさせる距離
    static constexpr float  NormalVecterMaximumValue = 0.000001f;   // 法線のY成分の最大値(垂直判定用)
    static constexpr float  NormalVecterMinimumValue = -0.000001f;  // 法線のY成分の最大値(垂直判定用)
    static constexpr float  CheckPositionOffset = 0.1f;             // ポリゴンとの当たり判定処理の余分量
    // ステータス
    static constexpr VECTOR StageModelScale = { 0.1,0.1,0.1 };  // ステージモデルのスケール


    // 変数
    ModelDataManager*           modelDataManager;   // モデルデータを取得するためのマネージャー

    // モデル関係 Dim → Dimensions (次元)
    int                         modelHandle;        // モデルハンドル
    MV1_COLL_RESULT_POLY_DIM    hitDim;             // プレイヤー周辺の当たりのポリゴンの衝突結果
    bool                        isCreatedHitDim;

    // ポリゴン
    int                         wallNum;            // 壁ポリゴンの数
    int                         floorNum;           // 床ポリゴンの数
    MV1_COLL_RESULT_POLY*       wall[MaxHitColl];   // 壁ポリゴンとの接触したポリゴンのアドレスを保存する構造体
    MV1_COLL_RESULT_POLY*       floor[MaxHitColl];  // 床ポリゴンとの接触したポリゴンのアドレスを保存する構造体

    // シャッター(ドア)
    Shutter* shutter;                               // シャッター(ドア)

};

