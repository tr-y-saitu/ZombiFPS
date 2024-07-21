#pragma once
#include "SceneBase.h"

class Input;
class ImageDataManager;
class ModleDataManager;
class EffectDataManager;
class SoundDataManager;
class EffectPlayManager;
class SoundPlayManager;
class CollisionManager;
class Stage;
class Player;
class PlayerCamera;
class EnemyGroupController;
class EnemyWaveController;
class EnemyObjectPools;
class MaxAmmo;
class IncomeDouble;
class GameSceneUI;

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
    // ���͏���
    Input*              input;              // ���͔��菈��

    // �f�[�^�֘A
    ImageDataManager*   imageDataManager;   // �摜�f�[�^
    ModleDataManager*   modleDataManager;   // ���f���f�[�^
    EffectDataManager*  effectDataManager;  // �G�t�F�N�g�f�[�^
    SoundDataManager*   soundDataManager;   // �T�E���h�f�[�^
    
    // ���o�֘A
    EffectPlayManager*  effectPlayManager;  // �G�t�F�N�g�Đ��p
    SoundPlayManager*   soundPlayManager;   // �T�E���h�Đ��p

    // �I�u�W�F�N�g�֘A
    CollisionManager*   collisionManager;   // �����蔻��
    Stage*              stage;              // �X�e�[�W
    Player*             player;             // �v���C���[
    PlayerCamera*       playerCamera;       // �v���C���[��p�J����
    
    // �G�l�~�[�֘A
    EnemyGroupController*   enemyGroupController;   // �G�l�~�[�̌Q��
    EnemyWaveController*    enemyWaveController;    // �G�l�~�[�̃E�F�[�u�Ǘ�
    EnemyObjectPools*       enemyObjectPools;       // �G�l�~�[�̃I�u�W�F�N�g�v�[��

    // �A�C�e���֘A
    MaxAmmo*                maxAmmoItem;            // �e��}�b�N�X�A�C�e��
    IncomeDouble*           incomeDoubleItem;       // �|�C���g�Q�{�A�C�e��

    // UI�֘A
    GameSceneUI*        gameSceneUI;        // �Q�[���V�[���p��UI

};


