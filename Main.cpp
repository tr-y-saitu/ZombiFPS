// 標準ライブラリ
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "math.h"
// 追加外部ライブラリ
#include "DxLib.h"
#include "EffekseerForDXLib.h"
// 自作ヘッダー
// シングルトン
#include "FrameRateManager.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "DebugLogger.h"

// 各ヘッダー
#include "Common.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // DXライブラリの表示方法をウィンドウモードに変更する。
#ifdef _DEBUG
    ChangeWindowMode(true);     // ウィンドウモード
#else
    ChangeWindowMode(false);    // 全画面モード
#endif

    ChangeWindowMode(false);     // 全画面モード

    //描画先を裏画面に変更する。
    SetDrawScreen(DX_SCREEN_BACK);

    // フルシーンアンチエイリアスを設定する
    SetFullSceneAntiAliasingMode(4, 2);  // 4x アンチエイリアシングを設定

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        DxLib_End();  // エラーが起きたら直ちに終了
    }

    // 画面モードのセット
    SetGraphMode(ScreenWidth,ScreenHeight, ScreenColorBitNum);

    // 描画先グラフィック領域の指定
    SetDrawScreen(DX_SCREEN_BACK);

    // シングルトンクラスをインスタンス化
    FrameRateManager::CreateInstance();     // フレームレート
    ImageDataManager::CreateInstance();     // 画像データ
    ModelDataManager::CreateInstance();     // モデルデータ
    EffectManager::CreateInstance();        // エフェクト管理
    SoundManager::CreateInstance();         // サウンド管理
    CollisionManager::CreateInstance();     // 当たり判定管理
    DebugLogger::CreateInstance();          // デバッグ表示管理

    // ゲームのインスタンスを作成
    Game game;

    // ゲームの進行を制御するフラグ
    bool isPaused = false;

    DebugLogger* debugLogger = DebugLogger::GetInstance();
    DebugLogger::DebugPrintData data = { "Player","HP",100 };
    debugLogger->RegisterDebugData(&data);

    // エスケープキーが押されるかウインドウが閉じられるまでループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ゲームの更新
        game.Update();
        data.floatData++;

        // デバッグ処理をコンソール画面に出力
        debugLogger->Update();
    }

    // シングルトンクラスを解放
    FrameRateManager::DeleteInstance();     // フレームレート
    ImageDataManager::DeleteInstance();     // 画像データ
    ModelDataManager::DeleteInstance();     // モデルデータ
    EffectManager::DeleteInstance();        // エフェクト管理
    SoundManager::DeleteInstance();         // サウンド管理
    CollisionManager::DeleteInstance();     // 当たり判定管理
    DebugLogger::DeleteInstance();          // デバッグ描画管理

    // Effekseerを終了する。
    Effkseer_End();

    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}
