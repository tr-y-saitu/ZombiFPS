#pragma once
#include "Common.h"

class Bullet;

/// <summary>
/// 弾丸のオブジェクトプール
/// </summary>
class BulletObjectPools
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BulletObjectPools();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BulletObjectPools();

    /// <summary>
    /// 未使用の弾丸のインスタンスを渡す
    /// </summary>
    void GetInactiveBulletInstance(Bullet& bullet);

    // 使い終わった弾丸のインスタンスを未使用に変換する


private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int BulletInstanceNumber = 100;        // 弾丸のインスタンスの数


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    list<Bullet*>   inactiveBullet;     // 未使用の弾丸
    list<Bullet*>   activeBullet;       // 使用中の弾丸

};

