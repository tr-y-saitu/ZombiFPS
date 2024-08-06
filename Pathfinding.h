#pragma once
#include "Common.h"

class ImageDataManager;

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
        West1,      // 西の部屋１
        West2,      // 西の部屋２
        West3,      // 西の部屋３
        West4,      // 西の部屋４
        Center1,    // 中央の部屋１
        Center2,    // 中央の部屋２
        Center3,    // 中央の部屋３
        Center4,    // 中央の部屋４
        East1,      // 東の部屋１
        East2,      // 東の部屋２
        East3,      // 東の部屋３
        East4,      // 東の部屋４
    };

    /// <summary>
    /// 部屋の情報
    /// </summary>
    struct Room
    {
        RoomNumber  roomNumber;         // 部屋番号
        VECTOR      centerPosition;     // 部屋の中心座標（これをエネミーは経由する）
        float       width;              // 部屋の幅
        float       depth;              // 部屋の奥行
        int         imageHandle;        // 画像ハンドル
        list<Room*> adjacencyRoom;      // 隣接し、現在の部屋から行くことのできる部屋リスト
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
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// エネミーがプレイヤーへどの部屋を経由したら最短か計算し、次の部屋番号を返す
    /// </summary>
    /// <param name="plyaerRoom">プレイヤーのいる部屋</param>
    /// <param name="enemyPosition">エネミーの現在の座標</param>
    /// <returns>エネミーが行くべき部屋</returns>
    Room FindRoomPathToPlayer(Room plyaerRoom, VECTOR enemyPosition);

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int RoomTotalNumber = 12;          // 部屋の総数
    // デバッグ
    static constexpr float  DebugRoomCenterPositionSphereRadius = 0.7f;     // デバッグ用の球体の半径
    static constexpr int    DebugRoomCenterPositionSphereDivision = 8;        // 球を形成するポリゴンの細かさ


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    // 情報
    list<Room*>         roomList;                           // マップに存在するすべての部屋のリスト
    Room                initRoomData[RoomTotalNumber];      // 部屋の情報

    // 管理クラス
    ImageDataManager*   imageDataManager;                   // 画像データ読み込みクラス

};

