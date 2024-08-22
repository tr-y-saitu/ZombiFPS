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
void GameSceneUI::Draw(Player& player)
{
    // 銃の総弾数
    DrawFormatString(500, 800, DebugFontColor, "Ammo:%d", player.GetEquippedGunAmmo());

    // プレイヤーの所持金
    DrawFormatString(500, 900, DebugFontColor, "Money:%d", player.GetMoney());
}
