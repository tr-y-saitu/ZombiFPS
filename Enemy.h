#pragma once
#include "Common.h"

/// <summary>
/// �G�l�~�[(�]���r)
/// </summary>
class Enemy
{
public:
    /// <summary>
    /// �G�l�~�[�̏��
    /// </summary>
    enum EnemyState
    {
        None,       // ��~
        Walk,       // ����
        Run,        // ����
        Attack,     // �U��
    };

    /// <summary>
    /// �G�l�~�[�̃A�j���[�V�����^�C�v
    /// </summary>
    enum AnimationType
    {
        
    };

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Enemy();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Enemy();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

private:
    // �萔
    

    // �ϐ�
    VECTOR      position;               // ���W
    VECTOR      targetMoveDirection;    // ���f���������ׂ������̃x�N�g��
    float       angle;                  // ���f���������Ă�������̊p�x
    float       currentJumpPower;       // �x�������̑��x
    int         modelHandle;            // ���f���n���h��
    int         shadowHandle;           // �e�摜�n���h��
    //State     State;                  // ���

    int         currentPlayAnim;        // �Đ����Ă���A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       currentAnimCount;       // �Đ����Ă���A�j���[�V�����̍Đ�����
    int         prevPlayAnim;           // �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float       prevAnimCount;          // �O�̍Đ��A�j���[�V�����̍Đ�����
    float       animBlendRate;          // ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��
    bool        currentFrameMove;                 // ���̃t���[���œ��������ǂ���

};

