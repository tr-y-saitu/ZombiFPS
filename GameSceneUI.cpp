#include "GameSceneUI.h"
#include "Player.h"
#include "ImageDataManager.h"
#include "GunPowerUpMachine.h"
#include "AmmoBox.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameSceneUI::GameSceneUI()
    : previousHitPoint                  (0)
    , redBarWidth                       (0)
    , redBarAnimationFrame              (0)
    , visibleAmmoLowWarningText         (false)
    , ammoLowWarningTextPreviousTime    (0)
    , endImageExpansion              (0.5f)
{
    // 画像管理クラス
    imageDataManager = ImageDataManager::GetInstance();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameSceneUI::~GameSceneUI()
{
}

/// <summary>
/// 初期化
/// </summary>
void GameSceneUI::Initialize()
{
    // 画像ハンドルの取得
    vhsFilterImageHandle                = imageDataManager->GetImageHandle(ImageDataManager::VHSFiltersImageData);
    crosshairImageHandle                = imageDataManager->GetImageHandle(ImageDataManager::CrosshairImageData);
    recImageHandle                      = imageDataManager->GetImageHandle(ImageDataManager::RECImageData);
    gunPowerUpMachineIconImageHandle    = imageDataManager->GetImageHandle(ImageDataManager::IconGunPowerUpMachine);
    ammoBoxIconImageHandle              = imageDataManager->GetImageHandle(ImageDataManager::IconAmmoBox);
    hitFilterImageHandle                = imageDataManager->GetImageHandle(ImageDataManager::HitFilter);
    badEndImageHandle                   = imageDataManager->GetImageHandle(ImageDataManager::BadEndImageData);

    // ウェーブ画像の取得
    waveImageDataList[EnemyWaveController::WaveState::Wave1]    = imageDataManager->GetImageHandle(ImageDataManager::Wave1ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave2]    = imageDataManager->GetImageHandle(ImageDataManager::Wave2ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave3]    = imageDataManager->GetImageHandle(ImageDataManager::Wave3ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave4]    = imageDataManager->GetImageHandle(ImageDataManager::Wave4ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave5]    = imageDataManager->GetImageHandle(ImageDataManager::Wave5ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave6]    = imageDataManager->GetImageHandle(ImageDataManager::Wave6ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave7]    = imageDataManager->GetImageHandle(ImageDataManager::Wave7ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave8]    = imageDataManager->GetImageHandle(ImageDataManager::Wave8ImageData);
    waveImageDataList[EnemyWaveController::WaveState::Wave9]    = imageDataManager->GetImageHandle(ImageDataManager::Wave9ImageData);
    waveImageDataList[EnemyWaveController::WaveState::WaveEnd]  = imageDataManager->GetImageHandle(ImageDataManager::WaveLastImageData);

}

/// <summary>
/// 更新
/// </summary>
void GameSceneUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void GameSceneUI::Draw(Player& player, int waveState)
{
    // ビデオ風の情報を描画
    DrawVHSInformation();

    // ウェーブステート描画
    DrawWaveState(waveState);

    // プレイヤーの情報を描画
    DrawPlayerInformation(player);

    // インタラクトオブジェクトのアイコンの描画
    DrawInteractIcon();
}

/// <summary>
/// プレイヤーの情報を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawPlayerInformation(Player& player)
{
    // 現在時間の描画
    DrawCurrentTime();

    // 銃の情報を描画
    DrawGunInformation(player);

    // プレイヤーの所持金
    DrawPlayerMoney(player);

    // プレイヤーのインタラクトできる情報を描画
    DrawPlayerInteractState(player);

    // プレイヤーの装備中の銃の名称を描画
    DrawEquippedGunName(player);

    // プレイヤーのヒットポイントを描画
    DrawPlayerHitPoint(player);

    // 銃のクロスヘア描画
    DrawCrosshair(player);

    // プレイヤーのリロード情報を描画
    DrawReloadInfomation(player);
}

/// <summary>
/// 現在のウェーブステートを描画する
/// </summary>
/// <param name="waveState">現在のウェーブステート</param>
void GameSceneUI::DrawWaveState(int waveState)
{
    /*char waveStateString[256];
    sprintf_s(waveStateString, "%d", waveState++);
    DrawStringToHandle(CurrentWaveStateDrawPositionX, CurrentWaveStateDrawPositionY,
        waveStateString, CurrentWaveStateFontColor, outlastFontHandle);*/

    // 現在のウェーブステートを描画
    DrawGraph(CurrentWaveStateDrawPositionX, CurrentWaveStateDrawPositionY,
        waveImageDataList[(EnemyWaveController::WaveState)waveState],
        true);
}

/// <summary>
/// 銃の情報を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawGunInformation(Player& player)
{
    // 銃の弾薬を描画
    char gunInfo[256];
    int color = FontColorVHS;

    // 総弾数が少ない場合、UIの色を変化させる
    int currentAmmo = player.GetEquippedGunAmmo();
    int maxAmmo     = player.GetEquippedGunMaxAmmo();

    // 総弾数が残り少ない場合
    if (currentAmmo <= AmmoLow)
    {
        // 総弾数が残り少ない場合「赤色」
        color = GetColor(255, 0, 0);

        // 残り少ないことを警告描画
        DrawLowAmmoWarning();
    }
    else if (currentAmmo < (maxAmmo / AmmoHalfRate))
    {
        // 総弾数が半分なら「黄色」
        color = GetColor(255, 255, 0);
    }

    // 総弾数を描画
    sprintf_s(gunInfo, "%d/%d", player.GetEquippedGunAmmo(), player.GetEquippedBackUpAmmo());
    DrawStringToHandle(GunInformationDrawPositionX, GunInformationDrawPositionY,
        gunInfo, color, vhsLargeFontHandle);

    // 予備弾薬が少なくなった時のアナウンス
    DrawLowBackUpAmmoWarning(player);
}

/// <summary>
/// 残弾数が少なくなったことを警告描画する
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawLowAmmoWarning()
{
    // 現在時間取得
    int currentTime = GetNowCount();

    if (currentTime - ammoLowWarningTextPreviousTime >= LowAmmoWarningTextBlinkInterval)
    {
        visibleAmmoLowWarningText = !visibleAmmoLowWarningText;
        ammoLowWarningTextPreviousTime = currentTime;
    }

    // 文字を描画
    if (visibleAmmoLowWarningText)
    {
        DrawStringCenterScreen("!!! No Ammo !!!", LowAmmoWarningTextDrawPositionY,
            GetColor(255,0,0), vhsLargeFontHandle);
    }
}

/// <summary>
/// 予備弾薬が少なくなった場合のアナウンス表示
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawLowBackUpAmmoWarning(Player& player)
{
    // 予備弾薬数が少なくなった場合
    if (player.GetEquippedBackUpAmmo() < 50)
    {
        // 弾薬箱のアイコンを描画
        VECTOR ammoBoxPosition;

        // ワールド座標からスクリーン座標へ変換
        ammoBoxPosition = ConvWorldPosToScreenPos(AmmoBox::InitializePosition);

        DrawRotaGraph(ammoBoxPosition.x, ammoBoxPosition.y, 1, 0, ammoBoxIconImageHandle, true);
    }
}

/// <summary>
/// プレイヤーのインタラクトできるステート情報を描画する
/// </summary>
/// <param name="player"></param>
void GameSceneUI::DrawPlayerInteractState(Player& player)
{
    switch (player.GetInteractLocationState())
    {
    case Player::InteractLocationState::None:
        // 処理なし
        break;

    case Player::InteractLocationState::Shutter:
        // シャッター情報を描画
        char shutterInfo[256];
        snprintf(shutterInfo, sizeof(shutterInfo), "[F]ｷｰ ﾄﾞｱｦﾋﾗｸ");
        DrawStringCenterScreen(shutterInfo, 800, DebugFontColor, vhsJPLargeFontHandle);

        // コストを描画
        DrawInteractionCost(player.GetInteractionCost());

        break;

    case Player::InteractLocationState::AmmoBox:
        // 弾薬補充箱の情報を描画
        char ammoBoxInfo[256];
        snprintf(ammoBoxInfo, sizeof(ammoBoxInfo), "[F]ｷｰﾃﾞﾀﾞﾝﾔｸﾎｼﾞｭｳ");
        DrawStringCenterScreen(ammoBoxInfo, 800, DebugFontColor, vhsJPLargeFontHandle);

        // コストを描画
        DrawInteractionCost(player.GetInteractionCost());

        break;

    case Player::InteractLocationState::GunPowerUpMachine:
        // 武器強化マシンの情報を描画
        char gunPowerUpMachineInfo[256];
        snprintf(gunPowerUpMachineInfo, sizeof(gunPowerUpMachineInfo), "[F]ｷｰﾃﾞﾌﾞｷｦｷｮｳｶ");
        DrawStringCenterScreen(gunPowerUpMachineInfo, 800, DebugFontColor, vhsJPLargeFontHandle);

        // コストを描画
        DrawInteractionCost(player.GetInteractionCost());

        break;

    default:
        break;
    }
}

/// <summary>
/// プレイヤーの所持金を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawPlayerMoney(Player& player)
{
    char moneyString[256];
    snprintf(moneyString, sizeof(moneyString), "$:%d", player.GetMoney());
    DrawStringToHandle(1600, 800, moneyString, DebugFontColor, vhsJPLargeFontHandle);
}

/// <summary>
/// プレイヤーのヒットポイントを描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawPlayerHitPoint(Player& player)
{
    // プレイヤーのHPが現在何割なのか確認
    float currentHitPoint = player.GetHitPoint();
    float hpRatio = player.GetHitPoint() / Player::HitPointMaxValue;

    // HP割合に応じてバーの幅を決定
    int barWidth = static_cast<int>(HitPointBarMaxWidth * hpRatio);

    // 減ったHPの幅を計算
    float lostHpRatio = (previousHitPoint - currentHitPoint) / Player::HitPointMaxValue;
    redBarWidth = static_cast<int>(HitPointBarMaxWidth * lostHpRatio);

    // 赤色バーの位置を計算
    int redBarPositionX = HitPointBarDrawPositionX + barWidth;

    // ヒットポイントバーの枠を描画
    DrawBox(HitPointBarDrawPositionX - HitPointBarFrameThickness,
        HitPointBarDrawPositionY - HitPointBarFrameThickness,
        HitPointBarDrawPositionX + HitPointBarMaxWidth + HitPointBarFrameThickness,
        HitPointBarDrawPositionY + HitPointBarHeight + HitPointBarFrameThickness,
        FontColorBlack, true);

    // ヒットポイントをバーとして表示
    DrawBox(HitPointBarDrawPositionX, HitPointBarDrawPositionY,
        HitPointBarDrawPositionX + barWidth, HitPointBarDrawPositionY + HitPointBarHeight,
        HitPointBarColor, true);

    // 赤色バーが存在する場合
    if (redBarWidth > 0)
    {
        // 赤色バーを描画
        DrawBox(redBarPositionX, HitPointBarDrawPositionY,
            redBarPositionX + redBarWidth, HitPointBarDrawPositionY + HitPointBarHeight,
            GetColor(255, 0, 0), true);

        // 20フレーム後に徐々に現在のHP位置に移動
        if (redBarAnimationFrame < 20)
        {
            // アニメーションフレームを増加
            redBarAnimationFrame++;
            float animationRatio = static_cast<float>(redBarAnimationFrame) / 20;
            int currentRedBarWidth = static_cast<int>(redBarWidth * (1.0f - animationRatio));

            // 現在のHP位置に移動中の赤色バーを描画
            DrawBox(HitPointBarDrawPositionX + barWidth - currentRedBarWidth, HitPointBarDrawPositionY,
                HitPointBarDrawPositionX + barWidth, HitPointBarDrawPositionY + HitPointBarHeight,
                GetColor(255, 0, 0), true);
        }
        else
        {
            // アニメーションが完了したら赤色バーの幅をリセット
            redBarWidth = 0;
            redBarAnimationFrame = 0;
        }

    }
    // ヒット時のフィルター画像を描画
    if (currentHitPoint != previousHitPoint && currentHitPoint < previousHitPoint)
    {
        DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, DefaultExpansion, DefaultAngle, hitFilterImageHandle, true);
    }

    // 前回のヒットポイントを更新
    previousHitPoint = currentHitPoint;

}

/// <summary>
/// リロード情報を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void  GameSceneUI::DrawReloadInfomation(Player& player)
{
    // リロード中であるか
    if (player.GetIsReload())
    {
        // リロードの進行状況を取得
        int reloadTime = player.GetReloadTime();               // 現在のリロードタイマーの値
        int reloadTimeFrame = Player::ReloadTimeFrame;         // リロードに必要なフレーム数

        // リロード進行状況の割合を計算
        float reloadProgress = static_cast<float>(reloadTime) / reloadTimeFrame;

        // リロードバーの描画
        int barX = (ScreenWidth - ReloadBarWidth) / 2;      // 描画X位置
        int barY = (ScreenHeight - ReloadBarHeight) / 2;    // 描画Y位置

        // 現在のリロード進行状況に応じた描画するバーの幅
        int progressBarWidth = static_cast<int>(ReloadBarWidth * reloadProgress);

        // バーの背景（空の状態）
        DrawBox(barX, barY, barX + ReloadBarWidth, barY + ReloadBarHeight, GetColor(0,0,0), TRUE); // 赤色の背景

        // リロード進行中のバー（進捗を表す部分）
        DrawBox(barX, barY, barX + progressBarWidth, barY + ReloadBarHeight, GetColor(200, 200, 200), TRUE); // 緑色の進捗バー

        // リロード情報の描画
        DrawStringCenterScreen("ﾘﾛｰﾄﾞｼﾃｲﾏｽ", ReloadInfomationDrawPositionY, DebugFontColor, vhsJPLargeFontHandle);
    }
}

/// <summary>
/// プレイヤーの銃のクロスヘアの描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawCrosshair(Player& player)
{
    // エイム時は描画しない
    if (player.GetCurrentAimState() == Player::AimState::None)
    {
        // クロスヘア描画
        DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, 1, 0, crosshairImageHandle, true);
    }
}

/// <summary>
/// プレイヤーの装備中の銃の名称を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawEquippedGunName(Player& player)
{
    switch (player.GetCurrentGunType())
    {
    case Player::GunType::AssaultRifle:

        break;

    case Player::GunType::BattleRifle:

        break;

    case Player::GunType::SubmachineGun:
        DrawStringToHandle(1600, 850, "XP5", DebugFontColor, vhsJPLargeFontHandle);
        break;
    default:
        break;
    }
}

/// <summary>
/// ビデオ風の情報を画面に描画
/// </summary>
void GameSceneUI::DrawVHSInformation()
{
    // VHSフィルター画像を描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, 1, 0, vhsFilterImageHandle, true);

    // 録画文字を描画
    DrawRotaGraph(150, 100, 1, 0, recImageHandle, true);
}

/// <summary>
/// オブジェクトのインタラクト費用を描画
/// </summary>
/// <param name="interactionCost">インタラクト費用</param>
void GameSceneUI::DrawInteractionCost(int interactionCost)
{
    // 文字列に値を結合
    char text[256];
    snprintf(text, sizeof(text), "[ｺｽﾄ:%d]", interactionCost);

    // 画面の中央に描画
    DrawStringCenterScreen(text, InteractLocationCostDrawPositionY, DebugFontColor, vhsJPLargeFontHandle);
}

/// <summary>
/// インタラクトできるオブジェクトのアイコンを描画
/// </summary>
void GameSceneUI::DrawInteractIcon()
{
    // アイコン画像をビルボードで描画 // 
    // 上下にゆらゆら移動させながら描画

    // 弾薬補充箱
    VECTOR ammoBoxIconPosition = VAdd(AmmoBox::InitializePosition, AmmoBoxIconDrawOffset);
    ammoBoxIconPosition.y += UpdateIconOffset();    // 上下にずらす量を加算

    // ビルボード描画
    DrawBillboard3D(ammoBoxIconPosition,
        IconDrawCenterXRate, IconDrawCenterYRate,
        IconSize, IconAngle, ammoBoxIconImageHandle, true);

    // 銃強化マシン
    VECTOR gunMachinePosition = VAdd(GunPowerUpMachine::InitializePosition, GunPowerUpMachineIconDrawOffset);
    gunMachinePosition.y += UpdateIconOffset();     // 上下にずらす量を加算

    // ビルボード描画
    DrawBillboard3D(gunMachinePosition,
        IconDrawCenterXRate, IconDrawCenterYRate,
        IconSize, IconAngle, gunPowerUpMachineIconImageHandle, true);
}

/// <summary>
/// アイコン画像のずらし量計算
/// </summary>
float GameSceneUI::UpdateIconOffset()
{
    // フレームカウントを更新
    frameCount++;

    // sinを使用し、0～1の値を返し続ける
    return IconOffsetRange * sin(IconOffsetCycle * frameCount);
}

/// <summary>
/// バッドエンドの演出更新
/// </summary>
/// <returns>演出が終了したかどうか</returns>
bool GameSceneUI::UpdateBadEnd()
{
    bool badEndFinished = false;

    // バッドエンド演出が開始されていない場合
    if (!endStarted)
    {
        // 開始時間を記録
        endTimer = GetNowCount();    // 現在時間を取得
        endStarted = true;
    }

    // 経過時間を計測
    int currentTime = GetNowCount();
    int elapsedTime = currentTime - endTimer;

    // 時間によって画像を拡大する
    if (elapsedTime < BadEndTime)
    {
        // 最大拡大率を越えないようにする
        if (endImageExpansion <= BadEndMaximumExpansion)
        {
            // 画像の拡大率を時間に応じて変化
            endImageExpansion = BadEndImageExpansionSpeed + (elapsedTime / BadEndTime);
        }
    }
    else
    {
        // 終了時間を越えたら演出終了
        badEndFinished = true;
    }

    // バッドエンド画像を描画する
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf,
        endImageExpansion,
        DefaultAngle, badEndImageHandle, true);


    return badEndFinished;
}

/// <summary>
/// グッドエンドの演出更新
/// </summary>
/// <returns>演出が終了したかどうか</returns>
bool GameSceneUI::UpdateGoodEnd()
{
    return 1;
}
