#include "Common.h"
#include "Input.h"
#include "ImageDataManager.h"
#include "ModelDataManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EnemyGroupController.h"
#include "EnemyWaveController.h"
#include "EnemyObjectPools.h"
#include "MaxAmmo.h"
#include "IncomeDouble.h"
#include "GameSceneUI.h"
#include "GameScene.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
    // ���͏���
    input                   = new Input();

    // �f�[�^�֘A
    

    // ���o�֘A
    effectManager = EffectManager::GetInstance();
    soundManager = SoundManager::GetInstance();

    // �����蔻��
    collisionManager        = CollisionManager::GetInstance();

    // �I�u�W�F�N�g�֘A
    stage                   = new Stage();
    player                  = new Player();
    playerCamera            = new PlayerCamera();
    enemyGroupController    = new EnemyGroupController();
    enemyWaveController     = new EnemyWaveController();
    enemyObjectPools        = new EnemyObjectPools();

    // �A�C�e���֘A
    maxAmmoItem             = new MaxAmmo();
    incomeDoubleItem        = new IncomeDouble();

    // UI�֘A
    gameSceneUI             = new GameSceneUI();

    // ������
    Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
    delete(stage);
    delete(player);
    delete(playerCamera);
    delete(enemyGroupController);
    delete(enemyWaveController);
    delete(enemyObjectPools);
    delete(maxAmmoItem);
    delete(incomeDoubleItem);
    delete(gameSceneUI);
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
    stage->Initialize();
    player->Initialize();
    playerCamera->Initialize();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <returns>���̃V�[���̃|�C���^</returns>
SceneBase* GameScene::UpdateScene()
{
    // �e�X�g�`��
    DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene", true);

    // �I�u�W�F�N�g�X�V
    input->Update();                                    // ���͏���
    player->Update(*input,*playerCamera,*stage);        // �v���C���[
    playerCamera->Update(*input, *player,*stage);       // �v���C���[�J�����̍X�V
    gameSceneUI->Update();                              // UI�̍X�V

    // ����̃V�[����Ԃ�
    return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
    stage->Draw();          // �X�e�[�W
    player->Draw(*stage);   // �v���C���[
    DrawUI();               // UI�̕`��
}

/// <summary>
/// UI�̕`��
/// </summary>
void GameScene::DrawUI()
{
    gameSceneUI->Draw();
}

/// <summary>
/// ���̍X�V
/// </summary>
void GameScene::UpdateSound()
{

}

/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void GameScene::UpdateEffect()
{

}