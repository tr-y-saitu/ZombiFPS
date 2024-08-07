﻿#include "EnemyGroup.h"
#include "Stage.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroup::EnemyGroup()
{
    // 線形探索クラス
    pathfinding = new Pathfinding();

    // ゾンビを生成
    enemys.push_back(new Enemy());

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyGroup::~EnemyGroup()
{
    // メモリ解放
    for (int i = 0; i < enemys.size(); i++)
    {
        delete(enemys[i]);
    }

    delete(pathfinding);
}

/// <summary>
/// 初期化
/// </summary>
void EnemyGroup::Initialize()
{
    // エネミーの数だけ初期化
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Initialize();
    }
}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
/// <param name="stage">ステージ</param>
void EnemyGroup::Update(VECTOR playerPosition, Stage& stage)
{
    // 線形探索の更新
     // プレイヤーの位置する部屋を取得
    Pathfinding::Room playerRoom = pathfinding->GetCurrentRoom(playerPosition, playerPreviousRoom);

    for (int i = 0; i < enemys.size(); i++)
    {
        // そのエネミーが度超え行けばよいかが帰ってくる
        Pathfinding::Room enemyTargetRoom;  // エネミーが目指す部屋

        // 線形探索開始
        enemyTargetRoom = pathfinding->FindRoomPathToPlayer(playerRoom, *enemys[i]);

        // エネミーの更新
        enemys[i]->Update(enemyTargetRoom.centerPosition,stage);
    }
}

/// <summary>
/// 描画
/// </summary>
void EnemyGroup::Draw(VECTOR playerPosition)
{
    // エネミーの数だけ描画
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Draw();
    }

    // 線形探索用に区切った部屋を描画
    pathfinding->Draw();

    // プレイヤーの位置する部屋を描画
    Pathfinding::Room playerRoom = pathfinding->GetCurrentRoom(playerPosition, playerPreviousRoom);
    DrawFormatString(100, 500, DebugFontColor, "PlayerRoom:%d", playerRoom.roomNumber);
}

/// <summary>
/// エネミーの線形探索の更新
/// </summary>
/// <param name="playerPosition">プレイヤー座標</param>
void EnemyGroup::UpdateEnemyPathfinding(VECTOR playerPosition)
{
   
}
