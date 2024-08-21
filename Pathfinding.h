#pragma once
#include "Common.h"

class ImageDataManager;
class Enemy;

/// <summary>
/// 線形探索クラス
/// </summary>
class Pathfinding
{
public:
    /// <summary>
    /// 部屋番号
    /// </summary>
    enum RoomNumber
    {
        West1,      // 西の部屋１        0
        West2,      // 西の部屋２        1
        West3,      // 西の部屋３        2
        West4,      // 西の部屋４        3
        Center1,    // 中央の部屋１      4
        Center2,    // 中央の部屋２      5
        Center3,    // 中央の部屋３      6
        Center4,    // 中央の部屋４      7
        East1,      // 東の部屋１        8
        East2,      // 東の部屋２        9
        East3,      // 東の部屋３        10
        East4,      // 東の部屋４        11
    };
    
    /// <summary>
    /// 部屋の情報
    /// </summary>
    struct Room
    {
        RoomNumber          roomNumber;         // 部屋番号
        VECTOR              centerPosition;     // 部屋の中心座標（これをエネミーは経由する）
        float               width;              // 部屋の幅
        float               depth;              // 部屋の奥行
        int                 imageHandle;        // 画像ハンドル
        vector<Room*>       adjacencyRoom;      // 隣接し、現在の部屋から行くことのできる部屋リスト
    };

    /// <summary>
    /// 部屋へ入ったキャラのステート
    /// </summary>
    enum RoomEntryState
    {
        EntryRoom,          // 部屋に入った
        RoomCenter,         // その部屋の中心座標にいる
        MovingToNextRoom,   // 次の部屋を目指している
        MovingTarget,       // 室内のターゲットを目指している
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Pathfinding();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Pathfinding();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// すべての部屋リストを作成
    /// </summary>
    void CreateRooms();

    /// <summary>
    /// 部屋情報の初期化
    /// </summary>
    void InitializeRoomsData();

    /// <summary>
    /// 更新
    /// </summary>
    void Update(VECTOR playerPosition);

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// 部屋とする範囲を描画する
    /// </summary>
    /// <param name="centerPosition">部屋の中心座標</param>
    /// <param name="width">幅</param>
    /// <param name="depth">奥行き</param>
    void DrawDebugRoomArea(VECTOR centerPosition, float width, float depth);

    /// <summary>
    /// 現在位置する部屋を取得
    /// </summary>
    /// <param name="objectPosition">どの部屋にいるか調べたいキャラの座標</param>
    /// <param name="previousRoom">今ままで位置していた部屋</param>
    /// <returns>現在位置する部屋情報</returns>
    Room GetCurrentRoom(VECTOR objectPosition,Room& previousRoom);

    /// <summary>
    /// エネミーがプレイヤーへどの部屋を経由したら最短か計算し、次の部屋番号を返す
    /// </summary>
    /// BFS幅優先探索で実装
    Room FindRoomPathToPlayer(Room playerRoom,Enemy& enemy);

    Room UpdateBFS(Room playerRoom, Enemy& enemy, Room* enemyCurrentRoom);

    /// <summary>
    /// 二つの座標の距離を計算
    /// </summary>
    /// <param name="vector1">座標１</param>
    /// <param name="vector2">座標２</param>
    /// <returns>二つの座標の距離</returns>
    float GetDistance3D(const VECTOR position1, const VECTOR position2);

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // 部屋情報
    // 西部屋
    static constexpr VECTOR West1RoomCenterPosition                 = { -45.0f,  4.5f,  45.0f };    // 西１番部屋の中心座標
    static constexpr VECTOR West2RoomCenterPosition                 = { -45.0f,  4.5f,  18.0f };    // 西２番部屋の中心座標
    static constexpr VECTOR West3RoomCenterPosition                 = { -45.0f,  4.5f,  -5.0f };    // 西３番部屋の中心座標
    static constexpr VECTOR West4RoomCenterPosition                 = { -48.0f,  4.5f, -35.0f };    // 西４番部屋の中心座標
    // 中央部屋
    static constexpr VECTOR Center1RoomCenterPosition               = { -12.0f,  4.5f,  58.0f };    // 中央１番部屋の中心座標
    static constexpr VECTOR Center2RoomCenterPosition               = {  -9.0f,  4.5f,  -5.0f };    // 中央２番部屋の中心座標
    static constexpr VECTOR Center3RoomCenterPosition               = { -12.0f,  4.5f, -47.0f };    // 中央３番部屋の中心座標
    static constexpr VECTOR Center4RoomCenterPosition               = { -12.0f,  4.5f, -83.0f };    // 中央４番部屋の中心座標
    // 東部屋
    static constexpr VECTOR East1RoomCenterPosition                 = {  25.0f,  4.5f,  25.0f };     // 東１番部屋の中心座標
    static constexpr VECTOR East2RoomCenterPosition                 = {  45.0f,  4.5f,  -5.0f };     // 東２番部屋の中心座標
    static constexpr VECTOR East3RoomCenterPosition                 = {  22.0f,  4.5f, -35.0f };     // 東３番部屋の中心座標
    static constexpr VECTOR East4RoomCenterPosition                 = {  50.0f,  4.5f, -35.0f };     // 東４番部屋の中心座標
    
private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int    RoomTotalNumber                         = 12;       // 部屋の総数
    static constexpr float  RoomCenterDistance                      = 4.0f;     // この範囲なら部屋の中心とみなす

    // デバッグ
    static constexpr float  DebugRoomCenterPositionSphereRadius     = 0.7f;     // デバッグ用の球体の半径
    static constexpr int    DebugRoomCenterPositionSphereDivision   = 8;        // 球を形成するポリゴンの細かさ
    static constexpr float  DebugRoomNumberImageSize                = 5.0f;     // デバッグ用部屋番号画像のサイズ
    static constexpr float  DebugRoomNumberImageAngle               = 0.0f;     // デバッグ用部屋番号画像の角度
    static constexpr float  DebugRoomNumberImageOffset              = 7.0f;     // デバッグ用部屋番号画像のずらし位置
    static constexpr float  DebugRoomNumberImageDrawCenter          = 0.5f;     // (0.5f固定)デバッグ用部屋番号画像のお描画する中心座標

    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 情報
    list<Room*>         roomList;                           // マップに存在するすべての部屋のリスト
    Room                initRoomData[RoomTotalNumber];      // 部屋の情報
    

    // 管理クラス
    ImageDataManager*   imageDataManager;                   // 画像データ読み込みクラス

};

