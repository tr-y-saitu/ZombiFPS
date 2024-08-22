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
    // 画像ハンドルの取得
    vhsFilterImageHandle    = imageDataManager->GetImageHandle(ImageDataManager::VHSFiltersImageData);
    crosshairImageHandle    = imageDataManager->GetImageHandle(ImageDataManager::CrosshairImageData);
    recImageHandle          = imageDataManager->GetImageHandle(ImageDataManager::RECImageData);
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
}

/// <summary>
/// プレイヤーの情報を描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawPlayerInformation(Player& player)
{
    // 銃の情報を描画
    DrawGunInformation(player);

    // プレイヤーの所持金
    DrawPlayerMoney(player);

    // プレイヤーのインタラクトできる情報を描画
    DrawPlayerInteractState(player);

    // プレイヤーの装備中の銃の名称を描画
    DrawEquippedGunName(player);

    // 銃のクロスヘア描画
    DrawCrosshair(player);
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
    DrawStringToHandle(1600, 950, gunInfo, GetColor(200, 200, 200), vhsLargeFontHandle);
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
/// プレイヤーの銃のクロスヘアの描画
/// </summary>
/// <param name="player">プレイヤー</param>
void GameSceneUI::DrawCrosshair(Player& player)
{
    // クロスヘア描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf, 1, 0, crosshairImageHandle, true);
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
        DrawStringToHandle(1600, 850, "MP5", DebugFontColor, vhsJPLargeFontHandle);
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
