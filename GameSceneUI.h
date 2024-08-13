#pragma once
#include "SceneUIBase.h"

class Player;

/// <summary>
/// ゲームシーンのUI
/// </summary>
class GameSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSceneUI();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameSceneUI();
    
    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;
    
    /// <summary>
    /// 描画
    /// </summary>
    void Draw(Player& player);

private:

};


