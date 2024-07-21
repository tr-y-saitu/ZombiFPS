#pragma once
#include "Common.h"

class PlayerStateBase;
class Gun;
class Input;
class PlayerCamera;

/// <summary>
/// �v���C���[
/// </summary>
class Player
{
public:
    enum State
    {
        None,   // �������Ă��Ȃ�
        Run,    // ����
        Jump,   // �W�����v
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
    void Update(Input& input,PlayerCamera& palyerCamera);

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �V��ɐڐG�������̏���
    /// </summary>
    void OnHitRoof();
    
    /// <summary>
    /// ���ɓ����������̏���
    /// </summary>
    void OnHitFloor();
    
    /// <summary>
    /// �������m�肵�����̏���
    /// </summary>
    void OnFall();


    // �Q�b�^�[�A�Z�b�^�[
    const VECTOR& GetPosition() const { return position; }
    bool GetIsMove() const { return isMove; }
    State GetState() const { return state; }
    float GetJumpPower() const { return currentJumpPower; }

private:
    // �萔
    static constexpr float	PlayAnimSpeed = 250.0f; // �A�j���[�V�������x
    static constexpr float	MoveSpeed = 30.0f;      // �ړ����x
    static constexpr float	AnimBlendSpeed = 0.1f;  // �A�j���[�V�����̃u�����h���ω����x
    static constexpr float	AngleSpeed = 0.2f;      // �p�x�ω����x
    static constexpr float	JumpPower = 100.0f;     // �W�����v��
    static constexpr float	Gravity = 3.0f;         // �d��
    static constexpr float	ShadowSize = 200.0f;    // �e�̑傫��
    static constexpr float	ShadowHeight = 700.0f;  // �e�������鍂��


    // �ϐ�
    VECTOR              position;       // ���W
    PlayerStateBase*    playerState;    // �v���C���[�̏��
    Gun*                gun;            // �e
    // �ړ����
    VECTOR              targetMoveDirection;    // ���f���������ׂ������̃x�N�g��
    float               angle;                  // ���f���������Ă�������̊p�x
    float               currentJumpPower;       // �x�������̑��x
    int                 modelHandle;            // ���f���n���h��
    int                 shadowHandle;           // �e�摜�n���h��
    State               state;                  // ���
    // �A�j���[�V�����֌W
    int         currentPlayAnim;        // �Đ����Ă���A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       currentAnimCount;       // �Đ����Ă���A�j���[�V�����̍Đ�����
    int         prevPlayAnim;           // �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       prevAnimCount;          // �O�̍Đ��A�j���[�V�����̍Đ�����
    float       animBlendRate;          // ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��
    bool        isMove;                 // ���̃t���[���œ��������ǂ���

    // ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
    void DisableRootFrameZMove();

    // �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
    bool UpdateMoveParameterWithPad(const Input& input, const PlayerCamera& camera, VECTOR& UpMoveVec, VECTOR& LeftMoveVec, VECTOR& MoveVec);

    // �ړ�����
    //void Move(const VECTOR& MoveVector, Stage& stage);

    void UpdateAngle();                                 // ��]����
    //void PlayAnim(AnimKind PlayAnim);                 // �V���ȃA�j���[�V�������Đ�����
    void UpdateAnimation();                             // �A�j���[�V��������
    //void DrawShadow(const Stage& stage);              // �e��`��


};

