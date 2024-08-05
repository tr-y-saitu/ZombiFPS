#include "Pathfinding.h"


/// <summary>
/// コンストラクタ
/// </summary>
Pathfinding::Pathfinding()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Pathfinding::~Pathfinding()
{
}

/// <summary>
/// 初期化
/// </summary>
void Pathfinding::Initialize()
{

}

/// <summary>
/// すべての部屋リストを作成
/// </summary>
void Pathfinding::CreateAllRooms()
{
    
}

/// <summary>
/// 更新
/// </summary>
void Pathfinding::Update()
{

}


/// <summary>
/// エネミーがプレイヤーへどの部屋を経由したら最短か計算し、次の部屋番号を返す
/// </summary>
/// <param name="plyaerRoom">プレイヤーのいる部屋</param>
/// <param name="enemyPosition">エネミーの現在の座標</param>
/// <returns>エネミーが行くべき部屋</returns>
Pathfinding::Room Pathfinding::FindRoomPathToPlayer(Room plyaerRoom, VECTOR enemyPosition)
{
    // 線形探索を行った結果どの部屋に行けばよいか
    Room targetRoom;

    // エネミーがどの部屋にいるかを調べる

    // プレイヤーの部屋からエネミーがどの部屋を経由すればよいか検索

    // エネミーが行くべき部屋番号を返す
    return targetRoom;
}
