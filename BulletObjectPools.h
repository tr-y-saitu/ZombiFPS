#pragma once
#include "Common.h"
#include "Bullet.h"

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
    /// 現在未使用の弾丸があるかどうか調べる
    /// </summary>
    /// <returns>未使用のものがある:true   未使用のものがない:false</returns>
    bool HasInactiveBulletInstance();

    /// <summary>
    /// 未使用の弾丸のインスタンスを渡す
    /// </summary>
    /// <param name="bullet">渡したい使用中リストのアドレス</param>
    void AcquireInactiveBulletInstance(list<Bullet*>& activeBullet,Bullet::BulletInitializeData initializeData);

    /// <summary>
    /// 未使用の弾丸のインスタンスを渡す
    /// </summary>
    /// <returns>未使用弾丸があればそのアドレス   無ければnullptr</returns>
    Bullet* GetInactiveBullet();

    /// <summary>
    /// 使用中リストから未使用リストにインスタンスを移動する
    /// </summary>
    /// <param name="activeBullet">移動したい使用中のリストのアドレス</param>
    void ReturnActiveBulletInstance(list<Bullet*>& activeBullet);

private:
    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    static constexpr int BulletInstanceNumber = 100;        // 弾丸のインスタンスの数


    //---------------------------------------------------------------------------------//
    //                                      変数                                       //
    //---------------------------------------------------------------------------------//
    list<Bullet*>   inactiveBullet;     // 未使用の弾丸

};

