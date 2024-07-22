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
void SoundManager::PlaySoundListSE(PlaySoundSE soundType)
{
    playingSoundHandle = soundListSE[soundType];
    playingList.push_back(playingSoundHandle);
    PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// 読み込んだサウンドリストからBGM再生
/// </summary>
/// <param name="soundType">再生したいBGMの種類</param>
void SoundManager::PlaySoundListBGM(PlaySoundBGM soundType)
{
    playingSoundHandle = soundListBGM[soundType];
    if (!CheckSoundMem(playingSoundHandle))
    {
        playingList.push_back(playingSoundHandle);
        PlaySoundMem(playingSoundHandle, DX_PLAYTYPE_LOOP, true);
    }
}

