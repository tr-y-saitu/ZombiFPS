#pragma once
#include "Common.h"

class Player;


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
    // 定数
    static const int MaxHitColl = 2048;             // 処理するコリジョンポリゴンの最大数
    static constexpr float	DefaultSize = 800.0f;   // 周囲のポリゴン検出に使用する球の初期サイズ
    static constexpr float	HitWidth = 200.0f;      // 当たり判定カプセルの半径
    static constexpr float	HitHeight = 700.0f;     // 当たり判定カプセルの高さ
    static constexpr int	HitTryNum = 16;         // 壁押し出し処理の最大試行回数
    static constexpr float	HitSlideLength = 5.0f;  // 一度の壁押し出し処理でスライドさせる距離

    // 変数
    // モデル関係
    int                         modelHandle;        // モデルハンドル
    MV1_COLL_RESULT_POLY_DIM    hitDim;             // プレイヤー周辺の当たりのポリゴンの衝突結果
    bool                        isCreatedHitDim;

    // ポリゴン
    int                         wallNum;            // 壁ポリゴンの数
    int                         floorNum;           // 床ポリゴンの数
    MV1_COLL_RESULT_POLY*       wall[MaxHitColl];   // 壁ポリゴンとの接触したポリゴンのアドレスを保存する構造体
    MV1_COLL_RESULT_POLY*       floor[MaxHitColl];  // 床ポリゴンとの接触したポリゴンのアドレスを保存する構造体


    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    void AnalyzeWallAndFloor(const VECTOR& CheckPosition);

    // 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
    VECTOR CheckHitWithWall(Player& player, const VECTOR& CheckPosition);

    // 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
    VECTOR CheckHitWithFloor(Player& player, const VECTOR& CheckPosition);
};

