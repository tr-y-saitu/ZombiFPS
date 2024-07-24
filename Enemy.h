#pragma once
#include "Common.h"

/// <summary>
/// エネミー(ゾンビ)
/// </summary>
class Enemy
{
public:
    /// <summary>
    /// エネミーの状態
    /// </summary>
    enum EnemyState
    {
        None,       // 停止
        Walk,       // 歩き
        Run,        // 走り
        Attack,     // 攻撃
    };

    /// <summary>
    /// エネミーのアニメーションタイプ
    /// </summary>
    enum AnimationType
    {
        
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Enemy();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    // 定数
    

    // 変数
    VECTOR      position;               // 座標
    VECTOR      targetMoveDirection;    // モデルが向くべき方向のベクトル
    float       angle;                  // モデルが向いている方向の角度
    float       currentJumpPower;       // Ｙ軸方向の速度
    int         modelHandle;            // モデルハンドル
    int         shadowHandle;           // 影画像ハンドル
    //State     State;                  // 状態

    int         currentPlayAnim;        // 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       currentAnimCount;       // 再生しているアニメーションの再生時間
    int         prevPlayAnim;           // 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float       prevAnimCount;          // 前の再生アニメーションの再生時間
    float       animBlendRate;          // 現在と過去のアニメーションのブレンド率
    bool        currentFrameMove;                 // そのフレームで動いたかどうか

};

