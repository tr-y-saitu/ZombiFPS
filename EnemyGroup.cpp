#include "EnemyGroup.h"
#include "Stage.h"
#include"Calculation.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyGroup::EnemyGroup()
{
    // 線形探索クラス
    pathfinding = new Pathfinding();

    // ゾンビを生成
    enemys.push_back(new Enemy());
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerAddMoney">プレイヤーの所持金を増加させる関数ポインタ</param>
EnemyGroup::EnemyGroup(std::function<void(int)> playerAddMoney)
{
    // 線形探索クラス
    pathfinding = new Pathfinding();

    // ゾンビを生成
    enemys.push_back(new Enemy(playerAddMoney));
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
void EnemyGroup::Initialize(int currentWave)
{
    // エネミーの数だけ初期化
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Initialize(currentWave);
    }
}

/// <summary>
/// タイトルシーンでの初期化
/// </summary>
void EnemyGroup::InitializeTitleScene()
{
    // エネミーの数だけ初期化
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->InitializeTitleScene();
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
        // 線形探索
        VECTOR enemyTargetPosition = UpdateEnemyTargetPosition(playerPosition, *enemys[i], stage);

        // エネミーの現在の部屋を更新
        Pathfinding::Room enemyPreviousRoom = enemys[i]->GetPreviousRoom();
        Pathfinding::Room enemyRoom = pathfinding->GetCurrentRoom(enemys[i]->GetPosition(), enemyPreviousRoom);
        enemys[i]->SetCurrentRoom(enemyRoom);
        

        // ターゲットがプレイヤーか部屋の中心座標かチェック
        float distance = Calculation::Distance3D(playerPosition, enemyTargetPosition);
        ObjectTag tag;

        if (distance < 1.0f)
        {
            tag = ObjectTag::Player;
        }
        else
        {
            tag = ObjectTag::RoomCenter;
        }

        // エネミーの更新
        enemys[i]->Update(enemyTargetPosition,stage, tag);
    }

    for (int i = 0; i < enemys.size(); i++)
    {
        // エネミーが使用中かを調べる
        isActive = enemys[i]->GetIsActive();
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
    //pathfinding->Draw();

    // プレイヤーの位置する部屋を描画
    //Pathfinding::Room playerRoom = pathfinding->GetCurrentRoom(playerPosition, playerPreviousRoom);
    //DrawFormatString(100, 500, DebugFontColor, "PlayerRoom:%d", playerRoom.roomNumber);
}

/// <summary>
/// エネミーの線形探索の更新
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
/// <param name="stage">ステージ</param>
/// <returns>そのエネミーが目指す座標</returns>
VECTOR EnemyGroup::UpdateEnemyTargetPosition(VECTOR playerPosition,Enemy& enemy, Stage& stage)
{
    // 線形探索の更新
    VECTOR enemyTargetPosition = playerPosition; // エネミーが目指す座標
    
    // プレイヤーの位置する部屋を取得
    Pathfinding::Room playerRoom = pathfinding->GetCurrentRoom(playerPosition, playerPreviousRoom);

    // そのエネミーが度超え行けばよいかが帰ってくる
    Pathfinding::Room enemyTargetRoom;  // エネミーが目指す部屋

    // 線形探索開始
    enemyTargetRoom = pathfinding->FindRoomPathToPlayer(playerRoom, enemy);

    // プレイヤーとエネミーの今いる部屋を取得
    Pathfinding::Room enemyPreviousRoom = enemy.GetPreviousRoom();
    Pathfinding::Room enemyRoom = pathfinding->GetCurrentRoom(enemy.GetPosition(), enemyPreviousRoom);

    // エネミーの部屋とプレイヤーの部屋が一致した場合
    if (playerRoom.roomNumber == enemyRoom.roomNumber)
    {
        // プレイヤーの座標を目指す
        enemyTargetPosition = playerPosition;
    }
    else
    {
        // 次の部屋の中心座標を目指す
        enemyTargetPosition = enemyTargetRoom.centerPosition;
    }

    // エネミーが目指す座標
    return enemyTargetPosition;
}

/// <summary>
/// エネミーグループ内のエネミーのコリジョンデータを使用するかどうかを設定する
/// </summary>
/// <param name="set">使用したいかどうか</param>
void EnemyGroup::SetCollisionDataIsActive(bool set)
{
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->SetCollisionDataIsActive(set);
    }
}

/// <summary>
/// エネミーの現在の部屋を取得
/// </summary>
const Pathfinding::Room EnemyGroup::GetCurrentRoom()
{
    for (int i = 0; i < enemys.size(); i++)
    {
        return enemys[i]->GetCurrentRoom();
    }
}

/// <summary>
/// エネミーの座標を返す
/// </summary>
/// <returns>エネミーの座標</returns>
const VECTOR EnemyGroup::GetPosition()
{
    for (int i = 0; i < enemys.size(); i++)
    {
        return enemys[i]->GetPosition();
    }
}
