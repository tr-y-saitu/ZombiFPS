#pragma once
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
    /// コンストラクタ
    /// </summary>
    /// <param name="score">スコア</param>
    /// <param name="killCount">エネミーを殺した数</param>
    /// <param name="waveCount">終了した時点でのウェーブ数</param>
    ResultSceneUI(int setScore, int setKillCount, int setWaveCount);

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
    /// VHS風のノイズを描画
    /// </summary>
    void DrawVHSNoise();

    /// <summary>
    /// 当たり判定の更新
    /// </summary>
    void UpdateCollision();

    //---------------------------------------------------------------------------------//
    //                                      定数                                       //
    //---------------------------------------------------------------------------------//
    // テキスト「ｻｲﾁｮｳｾﾝｼﾏｽｶ」
    static constexpr int    KeyInformationTextBlinkInterval     = 600;       // 文字の点滅間隔
    static constexpr int    KeyInformationTextPositionY         = 720;       // 「ｻｲﾁｮｳｾﾝｼﾏｽｶ」の描画Y位置
    static constexpr float  MouseCursorInitializePositionX      = -1000;     // マウスカーソルの初期X座標
    static constexpr float  MouseCursorInitializePositionY      = -1000;     // マウスカーソルの初期Y座標
    // 閉じるボタン
    static constexpr int    ScoreBoardCloseButtonRedDrawPositionX   = 1555; // 閉じるボタンX座標
    static constexpr int    ScoreBoardCloseButtonRedDrawPositionY   = 215;  // 閉じるボタンY座標
    // yesボタン
    static constexpr float  YesKeyFrameDrawPositionX    = 750;  // yesのキーフレームのX座標
    static constexpr float  YesKeyFrameDrawPositionY    = 850;  // yesのキーフレームのY座標
    static constexpr int    YesTextDrawPositionX        = 700;  // yesのテキストのX座標
    static constexpr int    YesTextDrawPositionY        = 820;  // yesのテキストのY座標
    // noボタン
    static constexpr float  NoKeyFrameDrawPositionX     = 1200; // noのキーフレームのX座標
    static constexpr float  NoKeyFrameDrawPositionY     = 850;  // noのキーフレームのY座標
    static constexpr int    NoTextDrawPositionX         = 1170; // noのテキストのX座標
    static constexpr int    NoTextDrawPositionY         = 820;  // noのテキストのY座標
    // スコア文字
    static constexpr int    ScoreDrawPositionY          = 190;  // 「Score」の文字を描画するY座標
    // スコア基準
    static constexpr int    ScoreBaseDrawPositionY      = 300;  // スコアの基準を描画するY座標
    // 現在のスコア
    static constexpr int    NowScoreDrawPositionY       = 500;  // 現在のスコアを描画するY座標
    // VHS風のノイズ
    static constexpr int    VHSNoiseFilterResponseRate  = 5;    // VHS風のノイズ画像を描画する周期

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
    int                 vhsNoiseFilters150;             // VHS風ノイズ150%画像
    int                 vhsNoiseFilters200;             // VHS風ノイズ200%画像
    int                 vhsNoiseCounter;                // VHS風ノイズの描画カウンター

    // スコア
    int                 score;                          // スコア
    int                 killCount;                      // エネミーを殺した数
    int                 waveCount;                      // 最終ウェーブ数

    // 当たり判定情報
    ImageUIData         mouseCursorData;                // マウスカーソル
    ImageUIData         yesKeyFrameData;                // yes キーフレーム
    ImageUIData         noKeyFrameData;                 // no  キーフレーム
    ImageUIData         scoreBoardCloseButtonRedData;   // スコアボードを閉じるボタン
};


