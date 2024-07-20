#include "SoundPlayManager.h"

// 初期化
SoundPlayManager* SoundPlayManager::soundPlayManager = NULL;

/// <summary>
/// コンストラクタ
/// </summary>
SoundPlayManager::SoundPlayManager()
    : playingSoundHandle(0)
{
    // サウンドデータ読み込み
    LoadData();
}

/// <summary>
/// デストラクタ
/// </summary>
SoundPlayManager::~SoundPlayManager()
{
    DeleteSoundMem(pushuSE);
    DeleteSoundMem(titleSceneBGM);
    DeleteSoundMem(gameSceneBGM);
    DeleteSoundMem(clearSceneBGM);
}

/// <summary>
/// サウンドデータの読み込み
/// </summary>
void SoundPlayManager::LoadData()
{
    // 効果音
    pushuSE = LoadSoundMem("data/sound/Common/pushuSE.mp3");
    soundListSE[PUSH_SE] = pushuSE;
    // BGM
    titleSceneBGM = LoadSoundMem("data/sound/TitleScene/TitleSceneBGM1.mp3");
    gameSceneBGM = LoadSoundMem("data/sound/GameScene/GameSceneBMG1.mp3");
    clearSceneBGM = LoadSoundMem("data/sound/ClearScene/ClearSceneBGM.mp3");
    clearFinishBGM = LoadSoundMem("data/sound/ClearScene/gameClearSE.mp3");
    soundListBGM[TITLE_SCENE_BGM] = titleSceneBGM;
    soundListBGM[GAME_SCENE_BGM] = gameSceneBGM;
    soundListBGM[CLEAR_SCENE_BGM] = clearSceneBGM;
    soundListBGM[CLEAR_FINISH_BGM] = clearFinishBGM;
}

/// <summary>
/// インスタンスの作成
/// </summary>
void SoundPlayManager::CreateInstance()
{
    if (soundPlayManager == NULL)
    {
        soundPlayManager = new SoundPlayManager();
    }
}

/// <summary>
/// サウンドマネージャークラスのインスタンスポインタを渡す
/// </summary>
SoundPlayManager* SoundPlayManager::GetInstance()
{
    return soundPlayManager;
}

/// <summary>
/// インスタンスの削除
/// </summary>
void SoundPlayManager::DeleteInstance()
{
    delete(soundPlayManager);
}

/// <summary>
/// 更新
/// </summary>
void SoundPlayManager::Update()
{

}

/// <summary>
/// 再生中の音をすべて止める
/// </summary>
void SoundPlayManager::StopAllSounds()
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
void SoundPlayManager::PlaySoundListSE(PlaySoundSE soundType)
{
    playingSoundHandle = soundListSE[soundType];
    playingList.push_back(playingSoundHandle);
    PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// 読み込んだサウンドリストからBGM再生
/// </summary>
/// <param name="soundType">再生したいBGMの種類</param>
void SoundPlayManager::PlaySoundListBGM(PlaySoundBGM soundType)
{
    playingSoundHandle = soundListBGM[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_LOOP, true);
    }
}

