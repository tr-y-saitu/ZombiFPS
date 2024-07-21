#pragma once
#include "Common.h"

class Player;


/// <summary>
/// �X�e�[�W
/// </summary>
class Stage
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Stage();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Stage();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �I��������
    /// </summary>
    void Finalize();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �����蔻��
    /// </summary>
    /// <param name="player">�v���C���[</param>
    /// <param name="checkPosition">�����蔻����������Ώ�</param>
    /// <param name="moveVector">�ړ�����</param>
    void IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector);

    // �Q�b�^�[
    int GetModelHandle() const { return modelHandle; }

private:
    // �萔
    static const int MaxHitColl = 2048;             // ��������R���W�����|���S���̍ő吔
    static constexpr float	DefaultSize = 800.0f;   // ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
    static constexpr float	HitWidth = 200.0f;      // �����蔻��J�v�Z���̔��a
    static constexpr float	HitHeight = 700.0f;     // �����蔻��J�v�Z���̍���
    static constexpr int	HitTryNum = 16;         // �ǉ����o�������̍ő厎�s��
    static constexpr float	HitSlideLength = 5.0f;  // ��x�̕ǉ����o�������ŃX���C�h�����鋗��

    // �ϐ�
    // ���f���֌W
    int                         modelHandle;        // ���f���n���h��
    MV1_COLL_RESULT_POLY_DIM    hitDim;             // �v���C���[���ӂ̓�����̃|���S���̏Փˌ���
    bool                        isCreatedHitDim;

    // �|���S��
    int                         wallNum;            // �ǃ|���S���̐�
    int                         floorNum;           // ���|���S���̐�
    MV1_COLL_RESULT_POLY*       wall[MaxHitColl];   // �ǃ|���S���Ƃ̐ڐG�����|���S���̃A�h���X��ۑ�����\����
    MV1_COLL_RESULT_POLY*       floor[MaxHitColl];  // ���|���S���Ƃ̐ڐG�����|���S���̃A�h���X��ۑ�����\����


    // ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
    void AnalyzeWallAndFloor(const VECTOR& CheckPosition);

    // �ǃ|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
    VECTOR CheckHitWithWall(Player& player, const VECTOR& CheckPosition);

    // ���|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
    VECTOR CheckHitWithFloor(Player& player, const VECTOR& CheckPosition);
};

