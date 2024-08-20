﻿#pragma once
#include "SceneUIBase.h"
#include "SceneBase.h"

class ImageDataManager;
class Input;
struct ImageUIData;


/// <summary>
/// リザルトシーンのUI
/// </summary>
class ResultSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultSceneUI();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ResultSceneUI();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    // ゲッター
    const SceneBase::SceneState GetNextState()const { return nextState; }

private:
    /// <summary>
    /// キー入力文字を点滅描画させる
    /// </summary>
    void DrawBlinkingTextKeyInfomation();

    /// <summary>
    /// スコアボードの描画
    /// </summary>
    void DrawScoreBoard();

    /// <summary>
    /// キーフレームの描画
    /// </summary>
    void DrawKeyFrame();

    /// <summary>
    /// マウスの更新処理
    /// </summary>
    void UpdateMouse();

    /// <summary>
    /// マウスカーソルの描画
    /// </summary>
    void DrawMouse();

    /// <summary>
    /// 当たり判定の更新
    /// </summary>
    void UpdateCollision();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // テキスト「ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ」
    static constexpr int    KeyInformationTextBlinkInterval     = 800;       // 文字の点滅間隔
    static constexpr int    KeyInformationTextPositionY         = 900;       // 「ｷｰｦﾆｭｳﾘｮｸｼﾃｸﾀﾞｻｲ」の描画Y位置
    static constexpr float  MouseCursorInitializePositionX      = -1000;     // マウスカーソルの初期X座標
    static constexpr float  MouseCursorInitializePositionY      = -1000;     // マウスカーソルの初期Y座標
    // 閉じるボタン
    static constexpr int    ScoreBoardCloseButtonRedDrawPositionX   = 1555; // 閉じるボタンX座標
    static constexpr int    ScoreBoardCloseButtonRedDrawPositionY   = 215;  // 閉じるボタンY座標
    // yesボタン
    static constexpr float  YesKeyFrameDrawPositionX = 750;
    static constexpr float  YesKeyFrameDrawPositionY = 850;
    // noボタン
    static constexpr float  NoKeyFrameDrawPositionX = 1200;
    static constexpr float  NoKeyFrameDrawPositionY = 850;

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // 管理クラス　
    ImageDataManager*   imageDataManager;               // 画像データ

    // 入力
    Input*              input;                          // 入力処理

    // キー入力文字
    bool                isVisibleKeyInfomation;         // キー入力文字が表示されているかどうか
    int                 keyInfomationPreviousTime;      // キー入力文字が前回表示された時間
    SceneBase::SceneState   nextState;                  // 次のステートの名前

    // 画像ハンドル
    int                 scoreBoardImageHandel;          // スコアボードの画像ハンドル
    int                 scoreBoardCloseButtonRed;       // スコアボードを閉じるボタン(赤色)
    int                 checkKeyFrameBlack;             // キーの入力画像(赤色)
    int                 checkKeyFrameDefaults;          // キーの入力画像(デフォルト)
    int                 mouseCursorImageHandel;         // マウスカーソルの画像ハンドル

    // 当たり判定情報
    ImageUIData         mouseCursorData;                // マウスカーソル
    ImageUIData         yesKeyFrameData;                // yes キーフレーム
    ImageUIData         noKeyFrameData;                 // no  キーフレーム
    ImageUIData         scoreBoardCloseButtonRedData;   // スコアボードを閉じるボタン
};


