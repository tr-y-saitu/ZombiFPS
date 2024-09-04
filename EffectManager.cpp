#include "EffectManager.h"

// 初期化
EffectManager* EffectManager::effectManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
    : playingEffectHandle           (0)
    , muzzleFlashEffectHandle       (0)
{
    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    //DirectX11のバージョンを指定
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effkseer_Init(20000) == -1)
    {
        DxLib_End();
    }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);

    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);

    //EffekseerSyncronizDxlib();

    // 使用エフェクトを読み込み
    LoadEffect();
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
    // エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
}

/// <summary>
/// エフェクトの読み込み
/// </summary>
void EffectManager::LoadEffect()
{
    // エフェクトのロード
    muzzleFlashEffectHandle         = LoadEffekseerEffect("Data/Effect/Gun/MuzzleFlashEffect.efk",0.1f);
    bloodSplatterEffectHandle       = LoadEffekseerEffect("Data/Effect/Gun/BloodEffect.efk",0.5f);
    powerUpMuzzleFlashEffectHandle  = LoadEffekseerEffect("Data/Effect/Gun/GunPowerUpShootEffect.efk",0.2f);
    gunPowerUpEffectHandle          = LoadEffekseerEffect("Data/Effect/Gun/GunPowerUpEffect.efk",1.0f);

    // エフェクトリストに書き込み
    effectList[MuzzleFlashEffect] = muzzleFlashEffectHandle;
    effectList[BloodSplatter] = bloodSplatterEffectHandle;
}

/// <summary>
/// インスタンスを作成
/// </summary>
void EffectManager::CreateInstance()
{
    if (effectManager == NULL)
    {
        effectManager = new EffectManager();
    }
}

/// <summary>
/// エフェクトマネージャーのインスタンスのポインタを渡す
/// </summary>
/// <returns>EffectManagerのポインタ</returns>
EffectManager* EffectManager::GetInstance()
{
    return effectManager;
}

/// <summary>
/// エフェクトマネージャーの削除
/// </summary>
void EffectManager::DeleteInstance()
{
    delete(effectManager);
}

/// <summary>
/// 初期化
/// </summary>
void EffectManager::Initialize()
{
    // 処理なし
}

/// <summary>
/// シーンが切り替わった時の処理
/// </summary>
void EffectManager::OnChangedScene()
{
    // 再生中のエフェクトを削除する
    for (int i = playingList.size() - 1; i >= 0; i--)
    {
        // 再生中か調べる
        if (!IsEffekseer3DEffectPlaying(playingList[i]))
        {
            StopEffekseer3DEffect(playingList[i]);      // 停止
            playingList.erase(playingList.begin() + i); // 削除
        }
    }
}

/// <summary>
/// 更新
/// </summary>
void EffectManager::Update()
{
    // エフェクトが終了したら、再生中から削除する
    for (int i = 0; i < playingList.size(); i++)
    {
        // 再生中か調べる
        if (IsEffekseer3DEffectPlaying(playingList[i]) == NoPlay)
        {
            playingList.erase(playingList.begin());
        }
    }
}

/// <summary>
/// 現在再生中のエフェクトがあるかどうか
/// </summary>
/// <returns>ある:true  ない:false</returns>
/// HasPlayingEffect
bool EffectManager::HasPlayingEffect()
{
    bool isPlaying = false;

    for (int i = 0; i < playingList.size(); i++)
    {
        // 再生中か調べる
        if (IsEffekseer3DEffectPlaying(playingList[i]) == Play)
        {
            isPlaying = true;
        }
    }

    return isPlaying;
}

/// <summary>
/// 読み込んだエフェクトリストから再生
/// </summary>
/// <param name="effectType">再生するエフェクトの種類</param>
/// <param name="playPosition">再生する座標</param>
/// <param name="scale">※エフェクトの描画サイズ</param>
/// NOTE:第3引数の「scale」はデフォルト引数　デフォルト値{1.0f,1.0f,1.0f}
///      1.0fが読み込み時サイズ
/// TODO:すべての再生を行えるようにしたいが、リストの管理ができておらず未実装
void EffectManager::PlayEffectByEffectList(EffectType effectType, VECTOR playPosition, VECTOR scale)
{
    // 再生するエフェクトを設定
    playingEffectHandle = effectList[effectType];

    // 再生するエフェクトの拡大率を設定
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);

    // エフェクトを再生
    PlayEffekseer3DEffect(playingEffectHandle);

    // 再生中リストに追加
    playingList.push_back(playingEffectHandle);

    // エフェクトの描画座標を設定
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);
}

/// <summary>
/// マズルフラッシュエフェクト再生
/// </summary>
/// <param name="playPosition">再生座標</param>
void EffectManager::PlayMuzzleFlashEffect(VECTOR playPosition)
{
    playingEffectHandle = PlayEffekseer3DEffect(muzzleFlashEffectHandle);
    playingList.push_back(playingEffectHandle);
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);
}

/// <summary>
/// 再生中のエフェクトの座標を更新する
/// </summary>
/// <param name="newPosition"></param>
/// TODO:初めに再生された位置からエフェクト座標が更新されないため
///      マズルフラッシュなどは銃の位置に毎フレーム更新する
void EffectManager::UpdateMuzzleFlashEffect(VECTOR newPosition)
{
    // 再生中のマズルフラッシュエフェクトを検索
    for (int i = 0; i < playingList.size(); i++)
    {
        SetPosPlayingEffekseer3DEffect(playingList[i], newPosition.x, newPosition.y, newPosition.z);
        if (playingList[i] == powerUpMuzzleFlashEffectHandle)
        {
        }
    }
}

/// <summary>
/// 血しぶきのエフェクト再生
/// </summary>
/// <param name="playPosition">再生座標</param>
void EffectManager::PlayBloodSplatterEffect(VECTOR playPosition)
{
    // エフェクトの再生数
    int effectPlayCount = 0;

    // 現在再生中の血しぶきエフェクトを数える
    for (int i = 0; i < playingList.size(); i++)
    {
        if (playingList[i] == bloodSplatterEffectHandle)
        {
            if (IsEffekseer3DEffectPlaying(playingList[i]))
            {
                effectPlayCount++;
            }
        }
    }

    // 同時に再生できる血しぶきエフェクトを制限
    if (effectPlayCount >= 1)
    {
        return;
    }

    // 再生処理
    playingEffectHandle = PlayEffekseer3DEffect(bloodSplatterEffectHandle);
    playingList.push_back(playingEffectHandle);
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);

    // 再生速度の変更
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 4.0f);
}

/// <summary>
/// 強化済みの銃のマズルフラッシュエフェクトを再生する
/// </summary>
/// <param name="playPosition">再生座標</param>
void EffectManager::PlayGunPowerUpMuzzleFlashEffect(VECTOR playPosition)
{
    playingEffectHandle = PlayEffekseer3DEffect(powerUpMuzzleFlashEffectHandle);
    playingList.push_back(playingEffectHandle);
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);

    // 再生速度の変更
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 3.0f);
}

/// <summary>
/// 銃が強化された時のエフェクトを再生する
/// </summary>
/// <param name="playPosition">再生座標</param>
void EffectManager::PlayGunPowerUpEffect(VECTOR playPosition)
{
    // 座標を設定
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);
    playingEffectHandle = PlayEffekseer3DEffect(gunPowerUpEffectHandle);
    playingList.push_back(playingEffectHandle);

    // 再生速度の変更
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 0.5f);
}
