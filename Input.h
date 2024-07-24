#pragma once

#define USE_MOUSE       // マウスを使用する

/// <summary>
/// 入力管理クラス
/// </summary>
class Input
{
public:
    struct MousePosition
    {
        int x;      // X座標
        int y;      // Y座標
    };

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

    /// <summary>
    /// マウスでの更新処理
    /// </summary>
    void UpdateMouse();

    // ゲッター
    int GetCurrentFrameInput() const { return currentFrameInput; }
    int GetNowNewFrameInput() const { return nowFrameNewInput; }
    const MousePosition GetMousePosition() const { return mousePosition; }

    // 定数
    static constexpr float MouseSensitivity = 0.005f;        // マウス感度

private:

    // 変数
    int     currentFrameInput;      // 現在のフレームで押されていボタン
    int     nowFrameNewInput;       // 現在のフレームで新たに入力されたボタン
    MousePosition mousePosition;    // マウスの座標
};

