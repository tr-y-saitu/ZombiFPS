#include "Pathfinding.h"


/// <summary>
/// コンストラクタ
/// </summary>
Pathfinding::Pathfinding()
{
    // すべての部屋をメモリ確保
    CreateRooms();
}

/// <summary>
/// デストラクタ
/// </summary>
Pathfinding::~Pathfinding()
{
    for (auto it = roomList.begin(); it != roomList.end(); ++it)
    {
        delete* it;
        *it = nullptr;
    }
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
void Pathfinding::CreateRooms()
{
    for (int i = 0; i < RoomTotalNumber; i++)
    {
        roomList.push_back(new Room());
    }
}

/// <summary>
/// 部屋の初期化
/// </summary>
void Pathfinding::InitializeRooms()
{
    initRoomData [0] = {West1,VGet(0,0,0),1,1 };
    initRoomData[1] = { West2,VGet(0,0,0),1,1 };
    initRoomData[2] = { West3,VGet(0,0,0),1,1 };
    initRoomData[3] = { West4,VGet(0,0,0),1,1 };
    initRoomData[4] = { Center1,VGet(0,0,0),1,1 };
    initRoomData[5] = { Center2,VGet(0,0,0),1,1 };
    initRoomData[6] = { Center3,VGet(0,0,0),1,1 };
    initRoomData[7] = { Center4,VGet(0,0,0),1,1 };
    initRoomData[8] = { East1,VGet(0,0,0),1,1 };
    initRoomData[9] = { East2,VGet(0,0,0),1,1 };
    initRoomData[10] = { East3,VGet(0,0,0),1,1 };
    initRoomData[11] = { East4,VGet(0,0,0),1,1 };

    for (int i = 0; i < RoomTotalNumber; i++)
    {
        Room* roomData = new Room(initRoomData[i]);
        roomList.push_back(roomData);
    }
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
