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
    void Update(const Input& input, PlayerCamera& playerCamera, Stage& stage);

    /// <summary>
    /// �`��
    /// </summary>
    void Draw(const Stage& stage);

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
    bool GetIsMove() const { return isMove; }
    State GetState() const { return state; }
    float GetJumpPower() const { return currentJumpPower; }

private:
    /// <summary>
    /// ���[�g�t���[����Z�������̈ړ��p�����[�^�𖳌��ɂ���
    /// </summary>
    void DisableRootFrameZMove();

    /// <summary>
    /// ���͏��ɉ������ړ��p�����[�^��ݒ肷��
    /// </summary>
    /// <param name="input">���͏��</param>
    /// <param name="playerCamera">�v���C���[��p�J����</param>
    /// <param name="UpMoveVec">������x�N�g��</param>
    /// <param name="LeftMoveVec">�������x�N�g��</param>
    /// <param name="MoveVec">�ړ��x�N�g��</param>
    /// <returns>�ړ����Ă��邩�ǂ���</returns>
    bool UpdateMoveParameterWithPad(const Input& input, const PlayerCamera& playerCamera,
        VECTOR& UpMoveVec, VECTOR& LeftMoveVec, VECTOR& MoveVec);

    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="MoveVector">�ړ��x�N�g��</param>
    /// <param name="stage">�X�e�[�W</param>
    void Move(const VECTOR& MoveVector, Stage& stage);

    /// <summary>
    /// �v���C���[�J��������]�������v���C���[���f������]������
    /// </summary>
    /// <param name="playerCamera">�v���C���[�J����</param>
    void UpdateAngle(const PlayerCamera& playerCamera);

    /// <summary>
    /// �A�j���[�V������V�����Đ�����
    /// </summary>
    /// <param name="type">�A�j���[�V�����̎��</param>
    void PlayAnim(AnimationType type);

    /// <summary>
    /// �A�j���[�V��������
    /// </summary>
    void UpdateAnimation();

    /// <summary>
    /// �e��`�悷��
    /// </summary>
    /// <param name="stage">�X�e�[�W</param>
    void DrawShadow(const Stage& stage);



    //---------------------------------------------------------------------------------//
    //                                      �萔                                       //
    //---------------------------------------------------------------------------------//
    static constexpr float  PlayAnimSpeed   = 0.5f;     // �A�j���[�V�������x
    static constexpr float  MoveSpeed       = 0.5f;     // �ړ����x
    static constexpr float  AnimBlendSpeed  = 0.1f;     // �A�j���[�V�����̃u�����h���ω����x
    static constexpr float  AngleSpeed      = 0.2f;     // �p�x�ω����x
    static constexpr float  JumpPower       = 100.0f;   // �W�����v��
    static constexpr float  Gravity         = 3.0f;     // �d��
    static constexpr float  ShadowSize      = 200.0f;   // �e�̑傫��
    static constexpr float  ShadowHeight    = 700.0f;   // �e�������鍂��
    static constexpr float  FallUpPower     = 20.0f;    // ���𓥂݊O�������̃W�����v��
    static constexpr float  MoveLimitY      = 5.0f;     // Y���̈ړ�����
    static constexpr VECTOR PlayerScale     = { 0.05f,0.05f,0.05f };    // �v���C���[�̃X�P�[��

    //---------------------------------------------------------------------------------//
    //                                      �ϐ�                                       //
    //---------------------------------------------------------------------------------//
    // ���[�h�֌W
    ModelDataManager* modelDataManager; // ���f���f�[�^�}�l�[�W���[
    
    // ��{���
    VECTOR              position;       // ���W
    PlayerStateBase*    playerState;    // �v���C���[�̏��
    Gun*                gun;            // �e

    // �ړ����
    VECTOR      targetMoveDirection;    // ���f���������ׂ������̃x�N�g��
    float       angle;                  // ���f���������Ă�������̊p�x
    float       currentJumpPower;       // �x�������̑��x
    int         modelHandle;            // ���f���n���h��
    int         shadowHandle;           // �e�摜�n���h��
    State       state;                  // ���

    // �A�j���[�V�����֌W
    int         currentPlayAnim;        // �Đ����Ă���A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       currentAnimCount;       // �Đ����Ă���A�j���[�V�����̍Đ�����
    int         prevPlayAnim;           // �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       prevAnimCount;          // �O�̍Đ��A�j���[�V�����̍Đ�����
    float       animBlendRate;          // ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��
    bool        isMove;                 // ���̃t���[���œ��������ǂ���



};

