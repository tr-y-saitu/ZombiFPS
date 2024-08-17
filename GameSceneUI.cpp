#include "GameSceneUI.h"
#include "Player.h"
#include "ImageDataManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameSceneUI::GameSceneUI()
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
    vhsFilterImageHandle = imageDataManager->GetImageHandle(ImageDataManager::VHSFiltersImageData);
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
    // VHSフィルター画像を描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, 1, 0, vhsFilterImageHandle, true);

    // 銃の情報を描画
    DrawGunInformation(player);

    // プレイヤーの所持金
    DrawFormatString(500, 900, DebugFontColor, "Money:%d", player.GetMoney());

    // プレイヤーのインタラクトできる情報を描画
    DrawPlayerInteractState(player);

    // ウェーブステート描画
    DrawWaveState(waveState);
}

/// <summary>
/// 現在のウェーブステートを描画する
/// </summary>
/// <param name="waveState">現在のウェーブステート</param>
void GameSceneUI::DrawWaveState(int waveState)
{
    char waveStateString[256];
    sprintf_s(waveStateString, "%d", waveState++);
    DrawStringToHandle(100, 850, waveStateString, GetColor(200,0,0), outlastFontHandle);
}

/// <summary>
/// 銃の情報を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawGunInformation(Player& player)
{
    // 銃の弾薬を描画
    char gunInfo[256];
    sprintf_s(gunInfo, "%d/%d", player.GetEquippedGunAmmo(), player.GetEquippedBackUpAmmo());
    DrawStringToHandle(1600, 950, gunInfo, GetColor(200, 200, 200), vhsFontHandle);
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
        // シャッターの支払い料金を描画
        char shutterInfo[256];
        snprintf(shutterInfo, sizeof(shutterInfo), "[F]ｷｰﾃﾞﾄﾞｱｦﾋﾗｸ[ｺｽﾄ:%d]", player.GetInteractionCost());
        DrawStringCenterScreen(shutterInfo, 800, DebugFontColor, vhsJPFontHandle);

        break;

    case Player::InteractLocationState::PowerUpMachine:

        break;

    case Player::InteractLocationState::AmmoBox:

        break;
    default:
        break;
    }
}
