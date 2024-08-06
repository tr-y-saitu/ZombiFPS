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
    // 部屋のデータ   // 部屋番号     // 中心座標             // 幅   // 奥行        // 画像データ
    initRoomData[0]  = { West1,     VGet(  -45.0f,  4.5f,  45.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::West1ImageData) };
    initRoomData [1] = { West2,     VGet(  -45.0f,  4.5f,  18.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::West2ImageData) };
    initRoomData [2] = { West3,     VGet(  -45.0f,  4.5f,  -5.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::West3ImageData) };
    initRoomData [3] = { West4,     VGet(  -48.0f,  4.5f, -33.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::West4ImageData) };
    initRoomData [4] = { Center1,   VGet(  -10.0f,  4.5f,  58.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::Center1ImageData) };
    initRoomData [5] = { Center2,   VGet(  -10.0f,  4.5f,  -5.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::Center2ImageData) };
    initRoomData [6] = { Center3,   VGet(  -10.0f,  4.5f, -47.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::Center3ImageData) };
    initRoomData [7] = { Center4,   VGet(  -10.0f,  4.5f, -75.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::Center4ImageData) };
    initRoomData [8] = { East1,     VGet(   25.0f,  4.5f,  25.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::East1ImageData) };
    initRoomData [9] = { East2,     VGet(   45.0f,  4.5f,  -5.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::East2ImageData) };
    initRoomData[10] = { East3,     VGet(   15.0f,  4.5f, -35.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::East3ImageData) };
    initRoomData[11] = { East4,     VGet(   50.0f,  4.5f, -35.0f)     ,1      ,1   ,imageDataManager->GetImageHandle(ImageDataManager::East4ImageData) };
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
    // 部屋の情報を描画
    for (auto& room : roomList)
    {
        // 中心座標を球体で描画
        DrawSphere3D(room->centerPosition, DebugRoomCenterPositionSphereRadius,
            DebugRoomCenterPositionSphereDivision,
            DebugPolygonColor, DebugPolygonColor, true);

        // 部屋番号を画像で描画
        DrawBillboard3D(room->centerPosition, DebugRoomNumberImageDrawCenter, 0.0f,
            DebugRoomNumberImageSize, DebugRoomNumberImageAngle, room->imageHandle, true);
    }
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
