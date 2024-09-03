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
    int shutterOpenSE           = LoadSoundMem("Data/Sound/SE/System/ShutterOpenSE.mp3");
    int moneyUseSE              = LoadSoundMem("Data/Sound/SE/System/MoneyUseSE.mp3");
    soundListSE[ShutterOpenSE]  = shutterOpenSE;
    soundListSE[MoneyUseSE]     = moneyUseSE;

    // プレイヤー
    // TODO:現段階で必要最低限の音を入れたため、のちに実装予定
    int playerDamageSE              = LoadSoundMem("");
    int playerWalkingSE             = LoadSoundMem("Data/Sound/SE/Player/PlayerWalkingSE.mp3");
    int playerRunSE                 = LoadSoundMem("Data/Sound/SE/Player/PlayerRunSE.mp3");
    soundListSE[PlayerDamageSE]     = playerDamageSE;
    soundListSE[PlayerWalkingSE]    = playerWalkingSE;
    soundListSE[PlayerRunSE]        = playerRunSE;

    // 銃
    int submachineGunShootingSE = LoadSoundMem("Data/Sound/SE/Gun/SubmachineGunShootingSE1.mp3");
    int gunReloadStartSE        = LoadSoundMem("Data/Sound/SE/Gun/GunReloadStartSE.mp3");
    int gunReloadEndSE          = LoadSoundMem("Data/Sound/SE/Gun/GunReloadEndSE.mp3");
    int enemyHitSE              = LoadSoundMem("Data/Sound/SE/Gun/EnemyHitSE.mp3");
    int missShootingSE          = LoadSoundMem("Data/Sound/SE/Gun/MissShootingSE.mp3");
    int dryFireSE               = LoadSoundMem("Data/Sound/SE/Gun/DryFireSE.mp3");
    soundListSE[SubmachineGunShootingSE]    = submachineGunShootingSE;
    soundListSE[GunReloadStartSE]           = gunReloadStartSE;
    soundListSE[GunReloadEndSE]             = gunReloadEndSE;
    soundListSE[EnemyHitSE]                 = enemyHitSE;
    soundListSE[MissShootingSE]             = missShootingSE;
    soundListSE[DryFireSE]                  = dryFireSE;

    // ゾンビ
    int zombieVoice1SE = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice1SE.mp3");
    int zombieVoice2SE = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice2SE.mp3");
    int zombieVoice3SE = LoadSoundMem("Data/Sound/SE/Zombie/ZombieVoice3SE.mp3");
    soundListSE[ZombieVoice1SE] = zombieVoice1SE;
    soundListSE[ZombieVoice2SE] = zombieVoice2SE;
    soundListSE[ZombieVoice3SE] = zombieVoice3SE;

    // BGM ////////////////////////////////

    // プレイヤー
    int walkingBGM              = LoadSoundMem("Data/Sound/BGM/Player/WalkingBGM.mp3");
    int runBGM                  = LoadSoundMem("Data/Sound/BGM/Player/RunBGM.mp3");
    soundListBGM[WalkingBGM]    = walkingBGM;
    soundListBGM[RunBGM]        = runBGM;



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
/// 読み込んだサウンドリストからBGM再生
/// </summary>
/// <param name="soundType">再生したいBGMの種類</param>
void SoundManager::PlaySoundListBGM(LoopSoundType soundType)
{
    playingSoundHandle = soundListBGM[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_LOOP, true);
    }
}

