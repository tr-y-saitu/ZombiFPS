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
#include "ModleDataManager.h"
#include "EffectDataManager.h"
#include "SoundDataManager.h"
#include "EffectPlayManager.h"
#include "SoundPlayManager.h"

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
    ModleDataManager::CreateInstance();     // モデルデータ
    EffectDataManager::CreateInstance();    // エフェクトデータ
    SoundDataManager::CreateInstance();     // 音データ
    EffectPlayManager::CreateInstance();    // エフェクト再生
    SoundPlayManager::CreateInstance();     // 音再生

    // ゲームのインスタンスを作成
    Game game;

    // エスケープキーが押されるかウインドウが閉じられるまでループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ゲームの更新
        game.Update();


        // Windows 特有の面倒な処理をＤＸライブラリにやらせる
        // マイナスの値（エラー値）が返ってきたらループを抜ける
        if (ProcessMessage() < 0)
        {
            break;
        }
        // もしＥＳＣキーが押されていたらループから抜ける
        else if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }
    }

    // Effekseerを終了する。
    Effkseer_End();

    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}
