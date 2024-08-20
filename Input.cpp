#include "Common.h"
#include "Input.h"



/// <summary>
/// コンストラクタ
/// </summary>
Input::Input()
    : currentFrameInput         (0)
    , nowFrameNewInput          (0)
    , mousePosition             ({0,0})
    , mouseCurrentFrameInput    (0)
    , mouseNowFrameInput        (0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Input::~Input()
{
    // 処理なし
}

/// <summary>
/// 更新
/// </summary>
void Input::Update()
{
    // 一つ前のフレームの入力を保存
    int oldFrameInput;
    oldFrameInput = currentFrameInput;

#ifdef USE_MOUSE
    // マウスで入力状態を更新
    UpdateMouse();
#else
    // パッド、キーボード処理
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
#endif

    // 現在のフレームで新たに入力されたボタンのビットが立っている値を
    // nowFrameNewInput に代入する
    // 連続入力を防ぐために行う
    nowFrameNewInput = currentFrameInput & ~oldFrameInput;
}

/// <summary>
/// マウスでの更新処理
/// </summary>
/// MEMO：
/// マウスはスクリーン中央に固定する
void Input::UpdateMouse()
{
    // 入力更新
    mouseCurrentFrameInput = GetMouseInput();               // クリック
    GetMousePoint(&mousePosition.x, &mousePosition.y);      // カーソル

    // 移動だけキー入力
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // スクリーン中央に固定
    SetMousePoint(ScreenWidthHalf, ScreenHeightHalf);
}

/// <summary>
/// マウスを自由に動かす更新
/// </summary>
void Input::UpdateMouseWithScreen()
{
    // 入力更新
    mouseCurrentFrameInput = GetMouseInput();               // クリック
    GetMousePoint(&mousePosition.x, &mousePosition.y);      // カーソル

    // 移動だけキー入力
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
