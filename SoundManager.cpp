#include "SoundManager.h"

// 初期化
SoundManager* SoundManager::soundManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
SoundManager::SoundManager()
    : playingSoundHandle(0)
{
    // サウンドデータ読み込み
    LoadData();
}

/// <summary>
/// デストラクタ
/// </summary>
SoundManager::~SoundManager()
{
    DeleteSoundMem(pushuSE);
    DeleteSoundMem(titleSceneBGM);
    DeleteSoundMem(gameSceneBGM);
    DeleteSoundMem(clearSceneBGM);
}

/// <summary>
/// サウンドデータの読み込み
/// </summary>
void SoundManager::LoadData()
{
    // SE ///////////////////////////

    // システム
    soundListSE[ShutterOpenSE]              = LoadSoundMem("Data/Sound/SE/System/ShutterOpenSE.mp3");
    soundListSE[MoneyUseSE]                 = LoadSoundMem("Data/Sound/SE/System/MoneyUseSE.mp3");
    soundListSE[KeyStrokeSE]                = LoadSoundMem("Data/Sound/SE/System/KeystrokeSE.mp3");

    // プレイヤー
    soundListSE[PlayerDamageSE]             = LoadSoundMem("");
    soundListSE[PlayerWalkingSE]            = LoadSoundMem("Data/Sound/SE/Player/PlayerWalkingSE.mp3");
    soundListSE[PlayerRunSE]                = LoadSoundMem("Data/Sound/SE/Player/PlayerRunSE.mp3");
    soundListSE[OnHitEnemyAttackSE]         = LoadSoundMem("Data/Sound/SE/Player/OnHItEnemySE.mp3");

    // 銃
    soundListSE[SubmachineGunShootingSE]    = LoadSoundMem("Data/Sound/SE/Gun/SubmachineGunShootingSE1.mp3");
    soundListSE[GunReloadStartSE]           = LoadSoundMem("Data/Sound/SE/Gun/GunReloadStartSE.mp3");
    soundListSE[GunReloadEndSE]             = LoadSoundMem("Data/Sound/SE/Gun/GunReloadEndSE.mp3");
    soundListSE[EnemyHitSE]                 = LoadSoundMem("Data/Sound/SE/Gun/EnemyHitSE.mp3");
    soundListSE[MissShootingSE]             = LoadSoundMem("Data/Sound/SE/Gun/MissShootingSE.mp3");
    soundListSE[DryFireSE]                  = LoadSoundMem("Data/Sound/SE/Gun/DryFireSE.mp3");
    soundListSE[GunAimSE]                   = LoadSoundMem("Data/Sound/SE/Gun/GunAimSE.mp3");
    soundListSE[GunPowerUpShootSE]          = LoadSoundMem("Data/Sound/SE/Gun/GunPowerUpShootSE.mp3");

    // ゾンビ
    soundListSE[ZombieVoice1SE]             = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice1SE.mp3");
    soundListSE[ZombieVoice2SE]             = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice2SE.mp3");
    soundListSE[ZombieVoice3SE]             = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice3SE.mp3");
    soundListSE[ZombieAttackSE]             = LoadSoundMem("Data/Sound/SE/Zombie/ZonbieAttackSE.wav");

    // インタラクトオブジェクト
    soundListSE[RefillAmmoSE]               = LoadSoundMem("Data/Sound/SE/Object/RefillAmmo.mp3");
    soundListSE[GunPowerUpSE]               = LoadSoundMem("Data/Sound/SE/Object/GunPowerUpSE.mp3");

    // BGM ////////////////////////////////

    // タイトルシーンBGM
    soundListBGM[TitleSceneBGM]             = LoadSoundMem("Data/Sound/BGM/SceneBGM/TitleSceneBGM.mp3");
    ChangeVolumeSoundMem(VolumeBGM, soundListBGM[TitleSceneBGM]);

    // ゲームシーンBGM
    soundListBGM[GameSceneBGM]              = LoadSoundMem("Data/Sound/BGM/SceneBGM/GameSceneBGM.mp3");
    ChangeVolumeSoundMem(VolumeBGM, soundListBGM[GameSceneBGM]);

    // リザルトシーンBGM
    soundListBGM[ResultSceneBGM]            = LoadSoundMem("Data/Sound/BGM/SceneBGM/ResultSceneBGM.mp3");
    ChangeVolumeSoundMem(VolumeBGM, soundListBGM[ResultSceneBGM]);

    // プレイヤー
    soundListBGM[WalkingBGM]                = LoadSoundMem("Data/Sound/BGM/Player/WalkingBGM.mp3");
    soundListBGM[RunBGM]                    = LoadSoundMem("Data/Sound/BGM/Player/RunBGM.mp3");



}

/// <summary>
/// インスタンスの作成
/// </summary>
void SoundManager::CreateInstance()
{
    if (soundManager == NULL)
    {
        soundManager = new SoundManager();
    }
}

/// <summary>
/// サウンドマネージャークラスのインスタンスポインタを渡す
/// </summary>
SoundManager* SoundManager::GetInstance()
{
    return soundManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void SoundManager::DeleteInstance()
{
    delete(soundManager);
}

/// <summary>
/// 更新
/// </summary>
void SoundManager::Update()
{

}

/// <summary>
/// 再生中の音をすべて止める
/// </summary>
void SoundManager::StopAllSounds()
{
    // 再生中のサウンドを探す
    for (int i = playingList.size() - 1; i >= 0; i--)
    {
        if (CheckSoundMem(playingList[i]))
        {
            StopSoundMem(playingList[i]);               // 停止
        }
        playingList.erase(playingList.begin() + i);     // 削除
    }
}

/// <summary>
/// 読み込んだサウンドリストから効果音再生
/// </summary>
/// <param name="soundType">再生したい効果音の種類</param>
void SoundManager::PlaySoundListSE(SoundEffectType soundType)
{
    playingSoundHandle = soundListSE[soundType];
    playingList.push_back(playingSoundHandle);
    PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// 読み込んだサウンドリストから効果音再生（ループ再生したい効果音用）
/// </summary>
/// <param name="soundType">再生したい効果音の種類</param>
void SoundManager::PlaySoundListSETypeLoop(SoundEffectType soundType)
{
    playingSoundHandle = soundListSE[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_BACK, true);
    }
}

/// <summary>
/// 読み込んだサウンドリストから効果音再生（ループ再生したい効果音用）
/// </summary>
/// <param name="soundType">再生したいBGMの種類</param>
void SoundManager::PlaySoundListSETypeLoop(LoopSoundType soundType)
{
    playingSoundHandle = soundListBGM[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_LOOP, true);
    }
}

