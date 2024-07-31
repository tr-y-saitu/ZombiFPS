#pragma once
#include "Common.h"

class EnemyGroup;
class Stage;

/// <summary>
/// 集合したエネミーを一つにまとめる
/// </summary>
class EnemyGroupController
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyGroupController();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyGroupController();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="targetPosition">進むべき座標</param>
    /// <param name="stage">ステージ</param>
    void Update(VECTOR targetPosition, Stage& stage);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private:
    // 定数
    // TODO: エネミーウェーブコントローラーで生成数を管理する
    //       オブジェクトプールでの管理ものちに行う
    static constexpr int TestEnmeyGroupNumber = 1;  // 仮のエネミーの生成数

    // 変数
    vector<EnemyGroup*> enemyGroup;     // エネミーの集合体
};


