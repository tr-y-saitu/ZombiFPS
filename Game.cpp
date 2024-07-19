#include "Game.h"
#include "Common.h"

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    : keyOn         (false)
    , keyRelease    (false)
    , prevKeyOn     (false)
{
    // 初期化
    Initialize();
    // 最初のシーンの設定
    nowScene = SceneBase::InitializeBase();
    // 次のシーンの初期化
    nextScene = NULL;
}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    delete(nowScene);
}

/// <summary>
/// 実際のゲームループ
/// </summary>
void Game::Update()
{
    // 画面の削除
    ClearDrawScreen();

    // 現在シーンの更新・描画
    nextScene = nowScene->UpdateScene();
    nowScene->Draw();

    // 描画を反映
    ScreenFlip();

    // Update内で return new 次のScene();された場合
    if (nowScene != nextScene)
    {
        // シーンを切り替える
        ChangeScene();
    }
}

/// <summary>
/// シーンの切り替え
/// </summary>
void Game::ChangeScene()
{
    // 現在のシーンを削除
    delete(nowScene);

    // 現在のシーンを切り替え
    nowScene = nextScene;

    // 初期関数を呼ぶ
    nowScene->Initialize();

    // 次のシーンを初期化
    nextScene = NULL;
}

/// <summary>
/// 初期化
/// </summary>
void Game::Initialize()
{
}

/// <summary>
/// 入力処理
/// </summary>
void Game::UpdateKeyState()
{
    // キーを離した瞬間をとる
    if (keyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            keyOn = false;
            keyRelease = true;
        }
    }
    else if (prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        keyRelease = false;
        keyOn = true;
    }
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        prevKeyOn = true;
    }
    else
    {
        prevKeyOn = false;
    }
}




