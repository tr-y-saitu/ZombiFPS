#pragma once
#include "Common.h"

class PlayerStateBase;
class Gun;
class Input;
class PlayerCamera;
class Stage;
class ModelDataManager;

/// <summary>
/// �v���C���[
/// </summary>
class Player
{
public:
    /// <summary>
    /// �v���C���[�̏��
    /// </summary>
    enum class State : int
    {
        None,   // �������Ă��Ȃ�
        Walk,   // ����
        Run,    // ����
        Jump,   // �W�����v
    };

    /// <summary>
    /// �A�j���[�V�����^�C�v
    /// </summary>
    enum class AnimationType : int
    {
        None = 8,   // �������Ă��Ȃ�
        Wolk = 8,   // ����
        Stop = 8,   // ��~
        Run,        // ����
        Jump,       // �W�����v
    };

    /// <summary>
    /// �������Ă���e�̎��
    /// </summary>
    enum  class GunType : int
    {
        AssaultRifle,       // �A�T���g���C�t��
        BattleRifle,        // �o�g�����C�t��
        SubmachineGun,      // �T�u�}�V���K��
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Player();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Player();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="input">���͏��</param>
    /// <param name="stage">�X�e�[�W</param>
    void Update(const Input& input, Stage& stage);

    /// <summary>
    /// �`��
    /// </summary>
    void Draw(const Stage& stage);

    /// <summary>
    /// �v���C���[�J�����̍X�V
    /// </summary>
    /// <param name="input">���͏��</param>
    /// <param name="stage">�X�e�[�W</param>
    void UpdatePlayerCamera(const Input& input,Stage& stage);

    /// <summary>
    /// �V��ɐڐG�������̏���
    /// </summary>
    void OnHitRoof();

    /// <summary>
    /// ���ɓ����������̏���
    /// </summary>
    void OnHitFloor();

    // �Q�b�^�[�A�Z�b�^�[
    const VECTOR& GetPosition() const { return position; }
    bool GetCurrentFrameMove() const { return currentFrameMove; }
    State GetState() const { return state; }
    float GetCurrentJumpPower() const { return currentJumpPower; }

private:
    /// <summary>
    /// ���[�g�t���[����Z�������̈ړ��p�����[�^�𖳌��ɂ���
    /// </summary>
    void DisableRootFrameZMove();

    /// <summary>
    /// �ړ��x�N�g���̍X�V
    /// </summary>
    /// <param name="input">���͏��</param>
    /// <param name="upModveVector">������x�N�g��</param>
    /// <param name="leftMoveVector">�������x�N�g��</param>
    /// <param name="currentFrameMoveVector">�ړ��x�N�g��</param>
    void UpdateMoveVector(const Input& input, VECTOR& upModveVector,
        VECTOR& leftMoveVector, VECTOR& currentFrameMoveVector);

    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="MoveVector">�ړ��x�N�g��</param>
    /// <param name="stage">�X�e�[�W</param>
    void Move(const VECTOR& MoveVector, Stage& stage);

    /// <summary>
    /// ��]����
    /// </summary>
    void UpdateAngle();

    /// <summary>
    /// �A�j���[�V������V�����Đ�����
    /// </summary>
    /// <param name="type">�A�j���[�V�����̎��</param>
    void PlayAnimation(AnimationType type);

    /// <summary>
    /// �A�j���[�V��������
    /// </summary>
    void UpdateAnimation();


    //---------------------------------------------------------------------------------//
    //                                      �萔                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  PlayAnimationSpeed   = 0.5f;     // �A�j���[�V�������x
    static constexpr float  MoveSpeed       = 0.5f;     // �ړ����x
    static constexpr float  AnimationBlendSpeed  = 0.1f;     // �A�j���[�V�����̃u�����h���ω����x
    static constexpr float  AngleSpeed      = 0.2f;     // �p�x�ω����x
    static constexpr float  JumpPower       = 100.0f;   // �W�����v��
    static constexpr float  Gravity         = 3.0f;     // �d��
    static constexpr float  ShadowSize      = 200.0f;   // �e�̑傫��
    static constexpr float  ShadowHeight    = 700.0f;   // �e�������鍂��
    static constexpr float  FallUpPower     = 20.0f;    // ���𓥂݊O�������̃W�����v��
    static constexpr float  MoveLimitY      = 5.0f;     // Y���̈ړ�����
    static constexpr VECTOR PlayerScale     = { 0.05f,0.05f,0.05f };    // �v���C���[�̃X�P�[��
    static constexpr VECTOR ZeroVector      = { 0.0f,0.0f,0.0f };       // �[���x�N�g��

    //---------------------------------------------------------------------------------//
    //                                      �ϐ�                                       //
    //---------------------------------------------------------------------------------//
    // ���[�h�֌W
    ModelDataManager*   modelDataManager; // ���f���f�[�^�}�l�[�W���[
    
    // ��{���
    PlayerCamera*       playerCamera;       // �v���C���[��p�̃J����(FPS���_�J����)
    VECTOR              position;           // ���W
    PlayerStateBase*    playerState;        // �v���C���[�̏��
    Gun*                gun;                // �e

    // �ړ����
    VECTOR      targetMoveDirection;        // ���f���������ׂ������̃x�N�g��
    float       currentJumpPower;           // �x�������̑��x
    int         modelHandle;                // ���f���n���h��
    State       state;                      // ���

    // �A�j���[�V�����֌W
    int         currentPlayAnimation;       // �Đ����Ă���A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       currentAnimationCount;      // �Đ����Ă���A�j���[�V�����̍Đ�����
    int         previousPlayAnimation;      // �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       previousAnimationCount;     // �O�̍Đ��A�j���[�V�����̍Đ�����
    float       animationBlendRate;         // ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��
    bool        currentFrameMove;           // ���̃t���[���œ��������ǂ���
    bool        pressMoveButton;            // �ړ��p�̃{�^�������͂���Ă��邩


};

