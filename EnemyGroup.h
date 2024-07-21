#pragma once
#include "Boids.h"
#include "Enemy.h"
#include "Pathfinding.h"


class Boids;
class Enemy;
class Pathfinding;

/// <summary>
/// �G�l�~�[�̏W����
/// </summary>
class EnemyGroup
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyGroup();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyGroup();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

private:
    // �萔

    // �ϐ�
    vector<Enemy>   enemys;         // �G�l�~�[(�]���r)
    Boids           boids;          // �W���v�Z�p
    Pathfinding     Pathfinding;    // ���`�T���p

};

