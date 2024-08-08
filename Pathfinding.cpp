#include "ImageDataManager.h"
#include "Pathfinding.h"
#include "Enemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
Pathfinding::Pathfinding()
{
    // 画像データ管理クラス
    imageDataManager = ImageDataManager::GetInstance();

    // すべての部屋をメモリ確保
    InitializeRoomsData();
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
    // 部屋情報の初期化
    InitializeRoomsData();

    // 部屋情報の書き込み
    int i = 0;
    for (auto& room : roomList)
    {
        room->centerPosition = initRoomData[i].centerPosition;
        room->width = initRoomData[i].width;
        room->depth = initRoomData[i].depth;
        i++;
    }
}

/// <summary>
/// すべての部屋リストを作成
/// </summary>
void Pathfinding::CreateRooms()
{
    // 部屋リストに書き込み
    for (int i = 0; i < RoomTotalNumber; i++)
    {
        // listなのでローカルでポインタ変数を作成
        Room* roomData = new Room(initRoomData[i]);
        roomList.push_back(roomData);
    }
}

/// <summary>
/// 部屋情報の初期化
/// </summary>
void Pathfinding::InitializeRoomsData()
{
    // 部屋のデータ   // 部屋番号     // 中心座標                 // 幅     // 奥行        // 画像データ
    initRoomData[West1]     = { West1,     VGet( -45.0f,  4.5f,  45.0f),      30,        40,       imageDataManager->GetImageHandle(ImageDataManager::West1ImageData) };
    initRoomData[West2]     = { West2,     VGet( -45.0f,  4.5f,  18.0f),      45,        13,       imageDataManager->GetImageHandle(ImageDataManager::West2ImageData) };
    initRoomData[West3]     = { West3,     VGet( -45.0f,  4.5f,  -5.0f),      45,        30,       imageDataManager->GetImageHandle(ImageDataManager::West3ImageData) };
    initRoomData[West4]     = { West4,     VGet( -48.0f,  4.5f, -35.0f),      50,        28,       imageDataManager->GetImageHandle(ImageDataManager::West4ImageData) };
    initRoomData[Center1]   = { Center1,   VGet( -12.0f,  4.5f,  58.0f),      15,       100,       imageDataManager->GetImageHandle(ImageDataManager::Center1ImageData) };
    initRoomData[Center2]   = { Center2,   VGet(  -9.0f,  4.5f,  -5.0f),      25,        25,       imageDataManager->GetImageHandle(ImageDataManager::Center2ImageData) };
    initRoomData[Center3]   = { Center3,   VGet( -12.0f,  4.5f, -47.0f),      18,        58,       imageDataManager->GetImageHandle(ImageDataManager::Center3ImageData) };
    initRoomData[Center4]   = { Center4,   VGet( -12.0f,  4.5f, -83.0f),      18,        13,       imageDataManager->GetImageHandle(ImageDataManager::Center4ImageData) };
    initRoomData[East1]     = { East1,     VGet(  25.0f,  4.5f,  25.0f),      55,        28,       imageDataManager->GetImageHandle(ImageDataManager::East1ImageData) };
    initRoomData[East2]     = { East2,     VGet(  45.0f,  4.5f,  -5.0f),      80,        30,       imageDataManager->GetImageHandle(ImageDataManager::East2ImageData) };
    initRoomData[East3]     = { East3,     VGet(  22.0f,  4.5f, -35.0f),      45,        28,       imageDataManager->GetImageHandle(ImageDataManager::East3ImageData) };
    initRoomData[East4]     = { East4,     VGet(  50.0f,  4.5f, -35.0f),      10,        28,       imageDataManager->GetImageHandle(ImageDataManager::East4ImageData) };

    // 隣接する部屋を追加
    // West１
    initRoomData[West1].adjacencyRoom.push_back(&initRoomData[West2]);
    // West2
    initRoomData[West2].adjacencyRoom.insert(initRoomData[West2].adjacencyRoom.end(),
        { &initRoomData[West1], &initRoomData[West3] });
    // West3
    initRoomData[West3].adjacencyRoom.insert(initRoomData[West3].adjacencyRoom.end(),
        { &initRoomData[West2], &initRoomData[Center2] });
    // West4
    initRoomData[West4].adjacencyRoom.insert(initRoomData[West4].adjacencyRoom.end(),
        { &initRoomData[Center3] });
    // Center1
    initRoomData[Center1].adjacencyRoom.insert(initRoomData[Center1].adjacencyRoom.end(),
        { &initRoomData[Center2] });
    // Center2
    initRoomData[Center2].adjacencyRoom.insert(initRoomData[Center2].adjacencyRoom.end(),
        { &initRoomData[Center1], &initRoomData[West3], &initRoomData[Center3], &initRoomData[East2] });
    // Center3
    initRoomData[Center3].adjacencyRoom.insert(initRoomData[Center3].adjacencyRoom.end(),
        { &initRoomData[West4],&initRoomData[Center2],&initRoomData[Center4] });
    // Center4
    initRoomData[Center4].adjacencyRoom.insert(initRoomData[Center4].adjacencyRoom.end(),
        { &initRoomData[Center3] });
    // East1
    initRoomData[East1].adjacencyRoom.insert(initRoomData[East1].adjacencyRoom.end(),
        { &initRoomData[East2] });
    // East2
    initRoomData[East2].adjacencyRoom.insert(initRoomData[East2].adjacencyRoom.end(),
        { &initRoomData[East1],&initRoomData[Center2],&initRoomData[East4] });
    // East3
    initRoomData[East3].adjacencyRoom.insert(initRoomData[East3].adjacencyRoom.end(),
        { &initRoomData[East4] });
    // East4
    initRoomData[East4].adjacencyRoom.insert(initRoomData[East4].adjacencyRoom.end(),
        { &initRoomData[East2],&initRoomData[East3]});
}

/// <summary>
/// 更新
/// </summary>
void Pathfinding::Update(VECTOR playerPosition)
{
    
}

/// <summary>
/// 描画
/// </summary>
void Pathfinding::Draw()
{
    // 初期化
    Initialize();

    // 部屋の情報を描画
    for (auto& room : roomList)
    {
        // 中心座標を球体で描画
        DrawSphere3D(room->centerPosition, DebugRoomCenterPositionSphereRadius,
            DebugRoomCenterPositionSphereDivision,
            DebugPolygonColorRed, DebugPolygonColorRed, true);

        // 部屋番号を画像で描画
        VECTOR drawPosition = room->centerPosition;
        drawPosition.y = DebugRoomNumberImageOffset;
        DrawBillboard3D(drawPosition, DebugRoomNumberImageDrawCenter, 0.0f,
            DebugRoomNumberImageSize, DebugRoomNumberImageAngle, room->imageHandle, true);

        // 部屋とする範囲を描画する
        DrawDebugRoomArea(room->centerPosition, room->width, room->depth);
    }
}

/// <summary>
/// 部屋とする範囲を描画する
/// </summary>
/// <param name="centerPosition">部屋の中心座標</param>
/// <param name="width">幅</param>
/// <param name="depth">奥行き</param>
void Pathfinding::DrawDebugRoomArea(VECTOR centerPosition, float width, float depth)
{
    // 半分の幅と奥行き
    float halfWidth = width / 2.0f;
    float halfDepth = depth / 2.0f;
    float halfHeight = centerPosition.y / 2.0f;

    // 四角形の頂点を計算
    VECTOR p1 = VGet(centerPosition.x - halfWidth, halfHeight, centerPosition.z - halfDepth);
    VECTOR p2 = VGet(centerPosition.x + halfWidth, halfHeight, centerPosition.z - halfDepth);
    VECTOR p3 = VGet(centerPosition.x + halfWidth, halfHeight, centerPosition.z + halfDepth);
    VECTOR p4 = VGet(centerPosition.x - halfWidth, halfHeight, centerPosition.z + halfDepth);

    // 三角形1: p1, p2, p3
    DrawTriangle3D(p1, p2, p3, DebugPolygonColorRed, TRUE);
    // 三角形2: p3, p4, p1
    DrawTriangle3D(p3, p4, p1, DebugPolygonColorBlue, TRUE);
}

/// <summary>
/// 現在位置する部屋を取得
/// </summary>
/// <param name="objectPosition">どの部屋にいるか調べたいキャラの座標</param>
/// <param name="previousRoom">今ままで位置していた部屋</param>
/// <returns>現在位置する部屋情報</returns>
Pathfinding::Room Pathfinding::GetCurrentRoom(VECTOR objectPosition, Room& previousRoom)
{
    Room room;

    // 位置する部屋を検索
    for (int i = 0; i < RoomTotalNumber; i++)
    {
        room = initRoomData[i];

        // 部屋の範囲を計算 (XZ平面のみ)
        float halfWidth = room.width / 2.0f;
        float halfDepth = room.depth / 2.0f;

        // 部屋の最小点と最大点を計算 (XZ平面、Y座標は無視)
        float minX = room.centerPosition.x - halfWidth;
        float maxX = room.centerPosition.x + halfWidth;
        float minZ = room.centerPosition.z - halfDepth;
        float maxZ = room.centerPosition.z + halfDepth;

        // オブジェクトが部屋の範囲内にいるかをチェック (XZ平面)２次元当たり判定
        if (objectPosition.x >= minX && objectPosition.x <= maxX &&
            objectPosition.z >= minZ && objectPosition.z <= maxZ)
        {
            previousRoom = room;    // プレイヤーの以前いた部屋を更新する
            return room;            // 部屋の情報を返す
        }
    }

    return room = previousRoom;
}

/// <summary>
/// エネミーがプレイヤーへどの部屋を経由したら最短か計算し、次の部屋番号を返す
/// </summary>
Pathfinding::Room Pathfinding::FindRoomPathToPlayer(Room playerRoom,Enemy& enemy)
{
    //// エネミーがどの部屋にいるかを調べる
    //Room enemyPreviousRoom = enemy.GetPreviousRoom();
    //Room enemyCurrentRoom1 = GetCurrentRoom(enemy.GetPosition(), enemyPreviousRoom);
    //enemy.SetPreviousRoom(enemyPreviousRoom);  // エネミーの前に位置していた部屋を更新

    //Room* enemyCurrentRoom = &enemyCurrentRoom1;

    //// エネミーがプレイヤーと同じ部屋にいる場合は、プレイヤーの部屋情報を返す
    //if (enemyCurrentRoom->roomNumber == playerRoom.roomNumber) {
    //    return playerRoom;
    //}

    //// 幅優先探索 (BFS) のためのデータ構造
    //std::queue<Room*> queue;
    //std::unordered_map<Room*, Room*> cameFrom;
    //std::unordered_map<Room*, bool> visited;

    //// 初期設定
    //queue.push(enemyCurrentRoom);
    //visited[enemyCurrentRoom] = true;

    //// BFS のメインループ
    //while (!queue.empty()) {
    //    Room* currentRoom = queue.front();
    //    queue.pop();

    //    // プレイヤーの部屋に到達した場合
    //    if (currentRoom->roomNumber == playerRoom.roomNumber) {
    //        // プレイヤーの部屋に到達した場合は、その部屋から最短経路を辿って最初の部屋を見つける
    //        Room* nextRoom = nullptr;
    //        for (Room* room = currentRoom; room != nullptr; room = cameFrom[room]) {
    //            if (room != enemyCurrentRoom) {  // エネミーの現在の部屋を除外
    //                nextRoom = cameFrom[room];
    //                break;
    //            }
    //        }
    //        // 最初に移動すべき部屋を返す
    //        return nextRoom ? *nextRoom : *enemyCurrentRoom;
    //    }

    //    // 隣接する部屋を調べる
    //    for (Room* adjacentRoom : currentRoom->adjacencyRoom) {
    //        if (visited.find(adjacentRoom) == visited.end()) {
    //            visited[adjacentRoom] = true;
    //            cameFrom[adjacentRoom] = currentRoom;
    //            queue.push(adjacentRoom);
    //        }
    //    }
    //}

    //// プレイヤーの部屋に到達できない場合はエネミーの現在の部屋を返す
    //return *enemyCurrentRoom;



    //// エネミーがどの部屋にいるかを調べる
    //Room enemyPreviousRoom = enemy.GetPreviousRoom();
    //Room enemyCurrentRoom1 = GetCurrentRoom(enemy.GetPosition(), enemyPreviousRoom);
    //enemy.SetPreviousRoom(enemyPreviousRoom);  // エネミーの前に位置していた部屋を更新

    //Room* enemyCurrentRoom = &enemyCurrentRoom1;

    //// エネミーがプレイヤーと同じ部屋にいる場合は、プレイヤーの部屋情報を返す
    //if (enemyCurrentRoom->roomNumber == playerRoom.roomNumber) {
    //    return playerRoom;
    //}

    //// 幅優先探索 (BFS) のためのデータ構造
    //std::queue<Room*> queue;
    //std::unordered_map<Room*, Room*> cameFrom;
    //std::unordered_map<Room*, bool> visited;

    //// 初期設定
    //queue.push(enemyCurrentRoom);
    //visited[enemyCurrentRoom] = true;

    //// BFS のメインループ
    //while (!queue.empty()) {
    //    Room* currentRoom = queue.front();
    //    queue.pop();

    //    // 隣接する部屋を調べる
    //    for (Room* adjacentRoom : currentRoom->adjacencyRoom) {
    //        if (visited.find(adjacentRoom) == visited.end()) {
    //            visited[adjacentRoom] = true;
    //            cameFrom[adjacentRoom] = currentRoom;
    //            queue.push(adjacentRoom);

    //            // プレイヤーの部屋に到達した場合
    //            if (adjacentRoom->roomNumber == playerRoom.roomNumber) {
    //                // 現在の部屋がエネミーの現在の部屋なら、次の部屋を返す
    //                if (currentRoom == enemyCurrentRoom) {
    //                    // エネミーの現在の部屋に隣接する部屋がプレイヤーの部屋の場合でも
    //                    // 別の部屋を返すように、cameFromから次の部屋を見つける
    //                    for (Room* room = adjacentRoom; room != nullptr; room = cameFrom[room]) {
    //                        if (cameFrom[room] == enemyCurrentRoom) {
    //                            return *room;
    //                        }
    //                    }
    //                }

    //                // プレイヤーの部屋が隣接しているが、直接移動するのを防ぐために
    //                // エネミーの現在の部屋から別の隣接する部屋を返す
    //                Room* nextRoom = nullptr;
    //                for (Room* room = adjacentRoom; room != nullptr; room = cameFrom[room]) {
    //                    if (cameFrom[room] == enemyCurrentRoom) {
    //                        nextRoom = room;
    //                    }
    //                }

    //                // 次に進むべき部屋がプレイヤーの部屋の隣接部屋であれば、その部屋の中心点を経由
    //                if (nextRoom && nextRoom->roomNumber == playerRoom.roomNumber) {
    //                    // 隣接部屋の中心点を通過してプレイヤーの部屋に移動
    //                    // nextRoomCenterが部屋の中心点
    //                    //Vec3 nextRoomCenter = nextRoom->center;
    //                    //enemy.MoveTo(nextRoomCenter);  // エネミーを隣接部屋の中心点に移動
    //                    return playerRoom;  // その後プレイヤーの部屋に移動
    //                }

    //                // それ以外の場合は、次の部屋に移動
    //                return nextRoom ? *nextRoom : *enemyCurrentRoom;
    //            }
    //        }
    //    }
    //}

    //// プレイヤーの部屋に到達できない場合はエネミーの現在の部屋を返す
    //return *enemyCurrentRoom;



    // エネミーがどの部屋にいるかを調べる
    Room enemyPreviousRoom = enemy.GetPreviousRoom();
    Room enemyCurrentRoom1 = GetCurrentRoom(enemy.GetPosition(), enemyPreviousRoom);
    //enemy.SetPreviousRoom(enemyCurrentRoom1);  // エネミーの前に位置していた部屋を更新
    
    Room* enemyCurrentRoom = &enemyCurrentRoom1;
    
    VECTOR roomPosition = enemyCurrentRoom->centerPosition;

    // エネミーの今いる部屋と、前いた部屋が違えばフラグをリセット
    Room enemyPreviousRoom1 = enemy.GetPreviousRoom();
    if (enemyCurrentRoom1.roomNumber != enemyPreviousRoom1.roomNumber)
    {
        enemy.SetIsTouchingRoomCenter(false);
        enemy.SetPreviousRoom(enemyCurrentRoom1);  // エネミーの前に位置していた部屋を更新
    }



    // エネミーの現在の座標と今いる部屋の中心座標を見比べる
    VECTOR enemyPosition = enemy.GetPosition();

    // エネミーの座標と今いる部屋の中心座標との距離
    float distance = GetDistance3D(enemyPosition, roomPosition);



    // エネミーがまだ部屋の中心に到達していない場合は前の部屋の中心座標を目指す
    if (distance >= 3.6f)
    {
        // 今いる部屋の中心座標をタッチしたのかをチェック
        if (!enemy.GetIsTouchingRoomCenter())
        {
            VECTOR previousRoomCenterPosition = enemyPreviousRoom.centerPosition;
            enemy.SetTargetNextPosition(previousRoomCenterPosition);
            enemy.SetIsTouchingRoomCenter(true);            // 今いる部屋の中心座標をタッチしました
            return *enemyCurrentRoom;
        }
    }

    
    // エネミーがプレイヤーと同じ部屋にいる場合は、プレイヤーの部屋情報を返す
    if (enemyCurrentRoom->roomNumber == playerRoom.roomNumber) {
        return playerRoom;
    }
    
    // 幅優先探索 (BFS) のためのデータ構造
    std::queue<Room*> queue;
    std::unordered_map<Room*, Room*> cameFrom;
    std::unordered_map<Room*, bool> visited;
    
    // 初期設定
    queue.push(enemyCurrentRoom);
    visited[enemyCurrentRoom] = true;
    
    // BFS のメインループ
    while (!queue.empty()) {
        Room* currentRoom = queue.front();
        queue.pop();
    
        // 隣接する部屋を調べる
        for (Room* adjacentRoom : currentRoom->adjacencyRoom) {
            if (visited.find(adjacentRoom) == visited.end()) {
                visited[adjacentRoom] = true;
                cameFrom[adjacentRoom] = currentRoom;
                queue.push(adjacentRoom);
    
                // プレイヤーの部屋に到達した場合
                if (adjacentRoom->roomNumber == playerRoom.roomNumber) {
                    // エネミーの現在の部屋からプレイヤーの部屋へのパスを見つけるa 
                    Room* nextRoom = nullptr;
                    for (Room* room = adjacentRoom; room != nullptr; room = cameFrom[room]) {
                        if (cameFrom[room] == enemyCurrentRoom) {
                            nextRoom = room;
                        }
                    }
    
                    // 次に進むべき部屋が見つからない場合の処理
                    if (nextRoom == nullptr) {
                        return *enemyCurrentRoom;  // 現在の部屋に留まる
                    }
    
                    // エネミーがプレイヤーの部屋の隣接部屋にいる場合
                    if (nextRoom->roomNumber == playerRoom.roomNumber) {
                        enemy.SetTargetNextPosition(nextRoom->centerPosition);  // 隣接部屋の中心点に移動
                        enemy.SetPreviousRoom(*nextRoom);  // 次の部屋として隣接部屋を設定
                        return *nextRoom;  // 隣接部屋を返す
                    }
    
                    // それ以外の場合は、次の部屋に移動
                    enemy.SetTargetNextPosition(nextRoom->centerPosition);
                    return *nextRoom;
                }
            }
        }
    }
    
    // プレイヤーの部屋に到達できない場合はエネミーの現在の部屋を返す
    return *enemyCurrentRoom;

}

/// <summary>
/// 二つの座標の距離を計算
/// </summary>
/// <param name="vector1">座標１</param>
/// <param name="vector2">座標２</param>
/// <returns>二つの座標の距離</returns>
float Pathfinding::GetDistance3D(const VECTOR position1, const VECTOR position2)
{
    return sqrtf((position1.x - position2.x) * (position1.x - position2.x) +
                 (position1.y - position2.y) * (position1.y - position2.y) +
                 (position1.z - position2.z) * (position1.z - position2.z));
}
