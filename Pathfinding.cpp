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
    // エネミーがどの部屋にいるかを調べる
    // TODO:GetCurrentRoomの第二引数が&型でこの段階ではまだ前いた部屋の更新を行ってほしくないため、
    //      ローカル変数で値だけもらって対応
    Room enemyPreviousRoom = enemy.GetPreviousRoom();
    Room tempEnemyCurrentRoom = GetCurrentRoom(enemy.GetPosition(), enemyPreviousRoom);
    
    Room enemyPreviousRoomView = enemy.GetPreviousRoom();   // エネミーの前にいた部屋の情報
    
    // エネミーの今いる部屋と前いた部屋が違えば、エネミーが今いる部屋の中心座標をタッチしたかのフラグをリセット
    if (tempEnemyCurrentRoom.roomNumber != enemyPreviousRoomView.roomNumber  && enemy.GetRoomEntryState() == MovingToNextRoom)
    {
        enemy.SetRoomEntryState(EntryRoom);             // 部屋に入った
        enemy.SetPreviousRoom(tempEnemyCurrentRoom);   // エネミーの前に位置していた部屋を更新
    }

    // 前に位置していた部屋を更新したのち現在の部屋に追加
    Room* enemyCurrentRoom = &tempEnemyCurrentRoom;
    
    // エネミーの現在の座標と今いる部屋の中心座標を見比べる
    VECTOR enemyPosition = enemy.GetPosition();                             // エネミーの現在座標
    VECTOR roomCenterPosition = enemyCurrentRoom->centerPosition;           // エネミーのいる部屋の中心座標
    float distance = GetDistance3D(enemyPosition, roomCenterPosition);      // 座標間の距離を計算
    
    // エネミーが部屋の中心に到達した場合、フラグをセットしステートを更新
    if (distance < RoomCenterDistance)
    {
        enemy.SetRoomEntryState(MovingToNextRoom);      // 次の部屋に移動する
    }
    
    // エネミーがプレイヤーと同じ部屋にいる場合は、プレイヤーの部屋情報を返す
    if (enemyCurrentRoom->roomNumber == playerRoom.roomNumber)
    {
        return playerRoom;
    }
    
    // 幅優先探索(BFS)
    return UpdateBFS(playerRoom, enemy, enemyCurrentRoom);
}

/// <summary>
/// 幅優先探索(BFS)
/// </summary>
/// <param name="playerRoom">プレイヤーの位置する部屋</param>
/// <param name="enemy">エネミー</param>
/// <param name="enemyCurrentRoom">エネミーの位置する部屋</param>
/// <returns>エネミーが目指す部屋</returns>
Pathfinding::Room Pathfinding::UpdateBFS(Room playerRoom, Enemy& enemy,Room* enemyCurrentRoom)
{
    // 幅優先探索 (BFS) のためのデータ構造
    std::queue<Room*>                   searchQueue;    // 探索用のキュー（調査待ちの部屋）
    std::unordered_map<Room*, Room*>    pathMap;        // どの部屋からどの部屋に移動したのかを記録する配列
    std::unordered_map<Room*, bool>     visitedRooms;   // 調査済みの部屋を記録するマップ

    // 初期設定
    searchQueue.push(enemyCurrentRoom);             // 現在エネミーの位置する部屋を探索用のキューに追加
    visitedRooms[enemyCurrentRoom] = true;          // エネミーが現在位置している部屋はもうすでに探索済みである

    // BFS のメインループ
    while (!searchQueue.empty() && enemy.GetRoomEntryState() == MovingToNextRoom)
    {
        Room* currentRoom = searchQueue.front();    // 探索用のキューから現在の部屋を抽出
        searchQueue.pop();                          // 探索用のキューからは除く

        // 現在の部屋に隣接する部屋を調べる
        for (Room* adjacentRoom : currentRoom->adjacencyRoom)   // adjacentRoomは現在の部屋の隣接リストになる
        {
            // 今から調べる部屋がまだ探索されていないか
            if (visitedRooms.find(adjacentRoom) == visitedRooms.end())
            {
                visitedRooms[adjacentRoom]  = true;         // 探索済み
                pathMap[adjacentRoom]       = currentRoom;  // 隣接部屋に到達するために、現在の部屋を経由することを記録
                searchQueue.push(adjacentRoom);             // 隣接部屋を次に探索するキューに追加

                // プレイヤーの部屋に到達した場合
                if (adjacentRoom->roomNumber == playerRoom.roomNumber)
                {
                    // 最短経路を保存するためのベクター
                    std::vector<Room*> path;

                    // エネミーの現在の部屋からプレイヤーの部屋へのパスを見つける
                    Room* nextRoom = nullptr;

                    // プレイヤーの部屋からエネミーの現在の部屋までの逆順にパスをたどる
                    for (Room* room = adjacentRoom; room != nullptr; room = pathMap[room])
                    {
                        path.push_back(room);   // 現在の部屋のパスを追加

                        // 現在の部屋がエネミーの部屋である場合
                        if (pathMap[room] == enemyCurrentRoom)
                        {
                            nextRoom = room;    // 現在の部屋にとどまる
                        }
                    }

                    // パスを逆順にして正しい順序にする(最短経路確認用配列)
                    std::reverse(path.begin(), path.end());

                    // 次に進むべき部屋が見つからない場合の処理
                    if (nextRoom == nullptr)
                    {
                        return *enemyCurrentRoom;  // 現在の部屋に留まる
                    }

                    // それ以外の場合は、次の部屋に移動
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
