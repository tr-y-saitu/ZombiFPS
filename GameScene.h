#pragma once
#include "SceneBase.h"
#include "GameSceneUI.h"

/// <summary>
///  �Q�[���V�[��
/// </summary>
class GameScene : public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GameScene();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// �V�[���̃A�b�v�f�[�g
    /// </summary>
    /// <returns>���̃V�[���̃|�C���^</returns>
    SceneBase* UpdateScene() override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;

    /// <summary>
    /// UI�̕`��
    /// </summary>
    void DrawUI() override;

    /// <summary>
    /// �T�E���h�̍X�V
    /// </summary>
    void UpdateSound();

    /// <summary>
    /// �G�t�F�N�g�̍X�V
    /// </summary>
    void UpdateEffect();

private:
    // �萔

    // �ϐ�
    GameSceneUI gameSceneUI;        // �Q�[���V�[���p��UI

};


