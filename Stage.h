#pragma once
#include "Common.h"

class Player;
class Shutter;
class ModelDataManager;


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
    /// <summary>
    /// ���菈������ǂƏ��̃|���S���������o����
    /// </summary>
    /// <param name="CheckPosition">���肷����W</param>
    void AnalyzeWallAndFloor(const VECTOR& CheckPosition);

    /// <summary>
    /// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�������炸�炷�ʂ�Ԃ�
    /// </summary>
    /// <param name="player">�v���C���[</param>
    /// <param name="CheckPosition">�����蔻�肷����W</param>
    /// <returns>�␳����ړ��x�N�g��</returns>
    VECTOR CheckHitWithWall(Player& player, const VECTOR& CheckPosition);

    /// <summary>
    /// ���|���S���Ƃ̓����蔻����`�F�b�N���A�������炸�炷�ʂ�Ԃ�
    /// </summary>
    /// <param name="player">�v���C���[</param>
    /// <param name="CheckPosition">�����蔻�肷����W</param>
    /// <returns>�␳����ړ��x�N�g��</returns>
    VECTOR CheckHitWithFloor(Player& player, const VECTOR& CheckPosition);
    

    // �萔
    // �����蔻��
    static constexpr int    SelectCollisionEntire = -1;             // ���f���S�̂ɃR���W������K�p������
    static const int        MaxHitColl = 2048;                      // ��������R���W�����|���S���̍ő吔
    static constexpr float  DefaultSize = 800.0f;                   // ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
    static constexpr float  HitWidth = 200.0f;                      // �����蔻��J�v�Z���̔��a
    static constexpr float  HitHeight = 700.0f;                     // �����蔻��J�v�Z���̍���
    static constexpr int    HitTryNum = 16;                         // �ǉ����o�������̍ő厎�s��
    static constexpr float  HitSlideLength = 5.0f;                  // ��x�̕ǉ����o�������ŃX���C�h�����鋗��
    static constexpr float  NormalVecterMaximumValue = 0.000001f;   // �@����Y�����̍ő�l(��������p)
    static constexpr float  NormalVecterMinimumValue = -0.000001f;  // �@����Y�����̍ő�l(��������p)
    static constexpr float  CheckPositionOffset = 0.1f;             // �|���S���Ƃ̓����蔻�菈���̗]����
    // �X�e�[�^�X
    static constexpr VECTOR StageModelScale = { 0.1,0.1,0.1 };  // �X�e�[�W���f���̃X�P�[��


    // �ϐ�
    ModelDataManager*           modelDataManager;   // ���f���f�[�^���擾���邽�߂̃}�l�[�W���[

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

};

