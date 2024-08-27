#include "TutorialScene.h"
#include "TutorialSceneUI.h"
#include "EffectManager.h"
#include "ImageDataManager.h"
#include "Input.h"
#include "ModelDataManager.h"
#include "SceneCamera.h"
#include "SoundManager.h"
#include "GameScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
TutorialScene::TutorialScene()
    : isKeyOn                   (false)
    , isKeyRelease              (false)
    , isPreviousKeyOn           (false)
    , currentTutorialState      (MoveTutorial)
{
    // リソース管理
    imageDataManager = ImageDataManager::GetInstance();
    modelDataManager = ModelDataManager::GetInstance();

    // 演出関連
    soundManager    = SoundManager::GetInstance();
    effectManager   = EffectManager::GetInstance();

    // 入力関連
    input           = new Input();

    // カメラ
    sceneCamera     = new SceneCamera();

    // UI
    tutorialSceneUI = new TutorialSceneUI();

    // 初期化
    Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialScene::~TutorialScene()
{
    delete(input);
    delete(sceneCamera);
}

/// <summary>
/// 初期化
/// </summary>
void TutorialScene::Initialize()
{
    // 画像ハンドルの所得
    tutorialImageHandleList[MoveTutorial]           = imageDataManager->GetImageHandle(ImageDataManager::MoveTutorialImageData);
    tutorialImageHandleList[ShotTutorial]           = imageDataManager->GetImageHandle(ImageDataManager::ShotTutorialImageData);
    tutorialImageHandleList[InteractTutorial]       = imageDataManager->GetImageHandle(ImageDataManager::InteractTutorialImageData);
    tutorialImageHandleList[EnemyTutorial]          = imageDataManager->GetImageHandle(ImageDataManager::EnemyTutorialImageData);
    tutorialImageHandleList[AmmoShutterTutorial]    = imageDataManager->GetImageHandle(ImageDataManager::AmmoShutterTutorialImageData);
    tutorialImageHandleList[GunPowerUpTutorial]     = imageDataManager->GetImageHandle(ImageDataManager::GunPowerUpTutorialImageData);
}

/// <summary>
/// シーンの更新
/// </summary>
/// <returns>次のシーンのポインタ</returns>
SceneBase* TutorialScene::UpdateScene()
{
    // キーの入力判定
    UpdateKeyState();

    // スペースキーが入力されたらシーン推移
    if (isKeyRelease)
    {
        // キー入力音を再生
        soundManager->PlaySoundListSE(SoundManager::KeyStrokeSE);

        // キーは離れていません
        isKeyRelease = false;

        // 次のチュートリアルステートへ更新
        currentTutorialState = static_cast<TutorialState>(static_cast<int>(currentTutorialState) + 1);
    }

    // Nキーが入力されたらチュートリアル終了
    if (CheckHitKey(KEY_INPUT_N))
    {
        // キー入力音を再生
        soundManager->PlaySoundListSE(SoundManager::KeyStrokeSE);

        // チュートリアルステートを終了
        currentTutorialState = TutorialEnd;
    }

    // チュートリアルが終了していればシーン切り替え
    if (currentTutorialState == TutorialEnd)
    {
        // ゲームシーンに推移
        return new GameScene();
    }

    // 現在のシーンを返す
    return this;
}

/// <summary>
/// 音の更新
/// </summary>
void TutorialScene::UpdateSound()
{

}

/// <summary>
/// 描画
/// </summary>
void TutorialScene::Draw()
{
    // 現在のチュートリアル画像を描画
    DrawRotaGraph(ScreenWidthHalf, ScreenHeightHalf,
        DefaultExpansion, DefaultAngle,
        tutorialImageHandleList[currentTutorialState], true);

    // UIの描画
    DrawUI();
}

/// <summary>
/// UIの描画
/// </summary>
void TutorialScene::DrawUI()
{
    tutorialSceneUI->Draw(currentTutorialState);
}

/// <summary>
/// 入力更新
/// </summary>
void TutorialScene::UpdateKeyState()
{
    // キー入力すでにされている場合
    if (isKeyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            isKeyOn = false;          // キーが入力されていない
            isKeyRelease = true;      // キーが離れた
        }
    }
    else if (isPreviousKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        // キーは長押しされていない && 前フレームで入力なし && キーが押された
        isKeyRelease = false;   // キーは離れていない
        isKeyOn = true;         // キーが押された
    }

    // キー入力されたら
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        isPreviousKeyOn = true;   // このフレームではキーが押された
    }
    else
    {
        isPreviousKeyOn = false;  // このフレームでキーは押されなかった
    }
}

