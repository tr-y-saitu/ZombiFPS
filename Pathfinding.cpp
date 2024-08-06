#include "ImageDataManager.h"
#include "Pathfinding.h"


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
    initRoomData [0] = { West1,     VGet(  -45.0f,  4.5f,  45.0f),      30,        40,       imageDataManager->GetImageHandle(ImageDataManager::West1ImageData) };
    initRoomData [1] = { West2,     VGet(  -45.0f,  4.5f,  18.0f),      45,        13,       imageDataManager->GetImageHandle(ImageDataManager::West2ImageData) };
    initRoomData [2] = { West3,     VGet(  -45.0f,  4.5f,  -5.0f),      45,        30,       imageDataManager->GetImageHandle(ImageDataManager::West3ImageData) };
    initRoomData [3] = { West4,     VGet(  -48.0f,  4.5f, -35.0f),      50,        28,       imageDataManager->GetImageHandle(ImageDataManager::West4ImageData) };
    initRoomData [4] = { Center1,   VGet(  -12.0f,  4.5f,  58.0f),      15,       100,       imageDataManager->GetImageHandle(ImageDataManager::Center1ImageData) };
    initRoomData [5] = { Center2,   VGet(   -9.0f,  4.5f,  -5.0f),      25,        25,       imageDataManager->GetImageHandle(ImageDataManager::Center2ImageData) };
    initRoomData [6] = { Center3,   VGet(  -12.0f,  4.5f, -47.0f),      18,        58,       imageDataManager->GetImageHandle(ImageDataManager::Center3ImageData) };
    initRoomData [7] = { Center4,   VGet(  -12.0f,  4.5f, -83.0f),      18,        13,       imageDataManager->GetImageHandle(ImageDataManager::Center4ImageData) };
    initRoomData [8] = { East1,     VGet(   25.0f,  4.5f,  25.0f),      55,        28,       imageDataManager->GetImageHandle(ImageDataManager::East1ImageData) };
    initRoomData [9] = { East2,     VGet(   45.0f,  4.5f,  -5.0f),      80,        30,       imageDataManager->GetImageHandle(ImageDataManager::East2ImageData) };
    initRoomData[10] = { East3,     VGet(   22.0f,  4.5f, -35.0f),      45,        28,       imageDataManager->GetImageHandle(ImageDataManager::East3ImageData) };
    initRoomData[11] = { East4,     VGet(   50.0f,  4.5f, -35.0f),      10,        28,       imageDataManager->GetImageHandle(ImageDataManager::East4ImageData) };
}

/// <summary>
/// 更新
/// </summary>
void Pathfinding::Update()
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
/// <param name="cneterPosition">部屋の中心座標</param>
/// <param name="width">幅</param>
/// <param name="depth">奥行き</param>
void Pathfinding::DrawDebugRoomArea(VECTOR cneterPosition, float width, float depth)
{
    // 半分の幅と奥行き
    float halfWidth = width / 2.0f;
    float halfDepth = depth / 2.0f;
    float halfHeight = cneterPosition.y / 2.0f;

    // 四角形の頂点を計算
    VECTOR p1 = VGet(cneterPosition.x - halfWidth, halfHeight, cneterPosition.z - halfDepth);
    VECTOR p2 = VGet(cneterPosition.x + halfWidth, halfHeight, cneterPosition.z - halfDepth);
    VECTOR p3 = VGet(cneterPosition.x + halfWidth, halfHeight, cneterPosition.z + halfDepth);
    VECTOR p4 = VGet(cneterPosition.x - halfWidth, halfHeight, cneterPosition.z + halfDepth);

    // 三角形1: p1, p2, p3
    DrawTriangle3D(p1, p2, p3, DebugPolygonColorRed, TRUE);
    // 三角形2: p3, p4, p1
    DrawTriangle3D(p3, p4, p1, DebugPolygonColorBlue, TRUE);
}

/// <summary>
/// 現在位置する部屋を取得
/// </summary>
/// <param name="objectPosition">どの部屋にいるか調べたいキャラの座標</param>
/// <returns>現在位置する部屋の情報</returns>
Pathfinding::Room Pathfinding::GetCurrentRoom(VECTOR objectPosition)
{
    // 現在いる部屋
    Room currentRoom;


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
