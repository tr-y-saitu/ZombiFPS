#include "GameSceneUI.h"
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameSceneUI::GameSceneUI()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameSceneUI::~GameSceneUI()
{
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
    // 銃の総弾数
    DrawFormatString(500, 800, DebugFontColor, "Ammo:%d", player.GetEquippedGunAmmo());

    // 銃の予備弾薬
    DrawFormatString(500, 1000, DebugFontColor, "BackUp:%d", player.GetEquippedBackUpAmmo(), true);

    // プレイヤーの所持金
    DrawFormatString(500, 900, DebugFontColor, "Money:%d", player.GetMoney());

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
    DrawStringToHandle(100, 900, waveStateString, GetColor(200,0,0), outlastFontHandle,DebugFontColor,waveState);
}
