#pragma once
#include "SceneBase.h"
#include "TitleScene.h"

class FrameRateManager;
class EffectPlayManager;
class SoundPlayManager;
class Input;

/// <summary>
/// �Q�[���S�̂̊Ǘ�
/// </summary>
class Game final
{
public:
    enum SceneState
    {
        SceneTitle,     // �^�C�g��
        SceneGame,      // �Q�[��
        SceneResult     // ���U���g
    };
    
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Game();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Game();

    /// <summary>
    /// ���ۂ̃Q�[�����[�v
    /// </summary>
    void Update();

    /// <summary>
    /// �V�[���̐؂�ւ�
    /// </summary>
    void ChangeScene();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// ���͏���
    /// </summary>
    void UpdateKeyState();

private:
    // ���s�p�V�[��
    SceneBase* nowScene;                    // ���݂̃V�[��
    SceneBase* nextScene;                   // ���̃V�[��

    // �Ǘ��N���X
    FrameRateManager* frameRateManager;     // �t���[�����[�g����
    EffectPlayManager* effectPlayManager;   // �G�t�F�N�g�Ǘ�
    SoundPlayManager* soundPlayManager;     // �T�E���h�Ǘ�
    Input* input;                           // ���͏���

    // �L�[����
    bool    keyOn;                          // �L�[���͂���Ă��邩
    bool    keyRelease;                     // �L�[���͂����ꂽ��
    bool    prevKeyOn;                      // �O�t���[���ŃL�[���͂���������
};

