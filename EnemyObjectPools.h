#pragma once


#include "Common.h"
#include "Enemy.h"

class Enemy;

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g�v�[��
/// </summary>
class EnemyObjectPools
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyObjectPools();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyObjectPools();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

private:
    // �萔
    static constexpr int EnemyTotalNum = 100;   // �G�l�~�[�̑�����

    // �ϐ�
    Enemy   activeEnemy[EnemyTotalNum];         // �g�p���G�l�~�[
    Enemy   nonActiveEenmy[EnemyTotalNum];      // �g�p���Ă��Ȃ��G�l�~�[


};

