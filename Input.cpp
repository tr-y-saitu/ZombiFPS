#include "Common.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
Input::Input()
    : currentFrameInput     (0)
    , nowFrameNewInput      (0)
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

    // 現在の入力状態を取得
    currentFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 現在のフレームで新たに入力されたボタンのビットが立っている値を
    // nowFrameNewInput に代入する
    nowFrameNewInput = currentFrameInput & ~oldFrameInput;
}