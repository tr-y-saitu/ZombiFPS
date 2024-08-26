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

    /// <summary>
    /// マウスを自由に動かす更新
    /// </summary>
    void UpdateMouseWithScreen();

    // ゲッター
    int GetCurrentFrameInput() const { return currentFrameInput; }
    int GetNowNewFrameInput() const { return nowFrameNewInput; }
    const MousePosition GetMousePosition() const { return mousePosition; }
    int GetMouseCurrentFrameInput()const { return mouseCurrentFrameInput; }
    int GetMouseNowFrameInput()const { return mouseNowFrameInput; }

    // 定数
    static constexpr float  MouseSensitivityHipShoot    = 0.0005f;                              // 腰だめ時のエイム感度
    static constexpr float  MouseSensitivityAim         = MouseSensitivityHipShoot * 0.7f;      // エイム時のエイム感度
private:

    // 変数
    int     currentFrameInput;      // 現在のフレームで押されていボタン
    int     nowFrameNewInput;       // 現在のフレームで新たに入力されたボタン
    int     previousFrameInput;     // 前のフレームで入力されたボタン
    MousePosition mousePosition;    // マウスの座標
    int     mouseCurrentFrameInput; // 現在のフレームで押されたボタン
    int     mouseNowFrameInput;     // 現在のフレームで新たに入力されたマウスボタン
};

