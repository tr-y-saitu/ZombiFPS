#pragma once

/// <summary>
/// プレイヤーステート基礎クラス
/// </summary>
class PlayerStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerStateBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerStateBase();

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() abstract;

private:

};

