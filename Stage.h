#pragma once
#include "Common.h"

class Player;
class Shutter;


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
    VECTOR IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector);

    // �Q�b�^�[
    int GetModelHandle() const { return modelHandle; }

private:
    // �萔

    static const int MaxHitColl = 2048;             // ��������R���W�����|���S���̍ő吔
    static constexpr float	DefaultSize = 50.0f;    // ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
    static constexpr float	HitWidth = 40.0f;       // �����蔻��J�v�Z���̔��a
    static constexpr float	HitHeight = 200.0f;     // �����蔻��J�v�Z���̍���
    static constexpr int	HitTryNum = 16;         // �ǉ����o�������̍ő厎�s��
    static constexpr float	HitSlideLength = 5.0f;  // ��x�̕ǉ����o�������ŃX���C�h�����鋗��

    // �ϐ�
    // ���f���֌W Dim �� Dimensions (����)
    int                         modelHandle;        // ���f���n���h��
    MV1_COLL_RESULT_POLY_DIM    hitDim;             // �v���C���[���ӂ̓�����̃|���S���̏Փˌ���
    bool                        isCreatedHitDim;

    // �|���S��
    int                         wallNum;            // �ǃ|���S���̐�
    int                         floorNum;           // ���|���S���̐�
    MV1_COLL_RESULT_POLY*       wall[MaxHitColl];   // �ǃ|���S���Ƃ̐ڐG�����|���S���̃A�h���X��ۑ�����\����
    MV1_COLL_RESULT_POLY*       floor[MaxHitColl];  // ���|���S���Ƃ̐ڐG�����|���S���̃A�h���X��ۑ�����\����

    // �V���b�^�[(�h�A)
    Shutter* shutter;                               // �V���b�^�[(�h�A)

    /// <summary>
    /// ���o���ꂽ�|���S���̎�ނ𒲂וۑ�(�� or ��)
    /// </summary>
    /// <param name="CheckPosition">�����蔻����������|���S�����W</param>
    void AnalyzeWallAndFloor(const VECTOR& CheckPosition);

    /// <summary>
    /// �ǃ|���S���Ƃ̓����蔻��
    /// </summary>
    /// <param name="player">�v���C���[</param>
    /// <param name="CheckPosition">�����蔻�肵�����|���S�����W</param>
    /// <returns>�␳����ړ��x�N�g��</returns>
    VECTOR CheckHitWithWall(Player& player, const VECTOR& CheckPosition);

    /// <summary>
    /// ���|���S���Ƃ̓����蔻��
    /// </summary>
    /// <param name="player">�v���C���[</param>
    /// <param name="CheckPosition">�����蔻�肵�����|���S�����W</param>
    /// <returns>�␳����ړ��x�N�g��</returns>
    VECTOR CheckHitWithFloor(Player& player, const VECTOR& CheckPosition);
};

