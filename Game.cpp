#include "Game.h"
#include "Common.h"
#include "FrameRateManager.h"
#include "EffectPlayManager.h"
#include "SoundPlayManager.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Game::Game()
    : keyOn         (false)
    , keyRelease    (false)
    , prevKeyOn     (false)
{
    // ������
    Initialize();
    // �ŏ��̃V�[���̐ݒ�
    nowScene = SceneBase::InitializeBase();
    // ���̃V�[���̏�����
    nextScene = NULL;

    // �V���O���g���N���X
    frameRateManager = FrameRateManager::GetInstance();
    effectPlayManager = EffectPlayManager::GetInstance();
    soundPlayManager = SoundPlayManager::GetInstance();

    // �Ǘ��N���X
    input = new Input();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Game::~Game()
{
    delete(nowScene);
}

/// <summary>
/// ���ۂ̃Q�[�����[�v
/// </summary>
void Game::Update()
{
    // ��ʂ̍폜
    ClearDrawScreen();

    // �t���[�����[�g�v������
    frameRateManager->Update();

    // ���݃V�[���̍X�V�E�`��
    nextScene = nowScene->UpdateScene();
    nowScene->Draw();

    // �t���[�����[�g�ҋ@����
    frameRateManager->SleepForFPS();

    // �`��𔽉f
    ScreenFlip();

    // Update���� return new ����Scene();���ꂽ�ꍇ
    if (nowScene != nextScene)
    {
        // �V�[����؂�ւ���
        ChangeScene();
    }
}

/// <summary>
/// �V�[���̐؂�ւ�
/// </summary>
void Game::ChangeScene()
{
    // ���݂̃V�[�����폜
    delete(nowScene);

    // ���݂̃V�[����؂�ւ�
    nowScene = nextScene;

    // �����֐����Ă�
    nowScene->Initialize();

    // ���̃V�[����������
    nextScene = NULL;
}

/// <summary>
/// ������
/// </summary>
void Game::Initialize()
{
}

/// <summary>
/// ���͏���
/// </summary>
void Game::UpdateKeyState()
{
    // �L�[�𗣂����u�Ԃ��Ƃ�
    if (keyOn)
    {
        if (CheckHitKey(KEY_INPUT_SPACE) == 0)
        {
            keyOn = false;
            keyRelease = true;
        }
    }
    else if (prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        keyRelease = false;
        keyOn = true;
    }
    if (CheckHitKey(KEY_INPUT_SPACE) == 1)
    {
        prevKeyOn = true;
    }
    else
    {
        prevKeyOn = false;
    }
}




