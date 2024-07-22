#pragma once

/// <summary>
/// 入力管理クラス
/// </summary>
class Input
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Input();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Input();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    // ゲッター
    int GetCurrentFrameInput() const { return currentFrameInput; }
    int GetNowNewFrameInput() const { return nowFrameNewInput; }

private:
    // 変数
    int     currentFrameInput;      // 現在のフレームで押されていボタン
    int     nowFrameNewInput;       // 現在のフレームで新たに入力されたボタン
};

