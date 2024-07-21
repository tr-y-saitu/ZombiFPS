#include "Player.h"
#include "Shutter.h"
#include "Stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage()
{
    // ������
    Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
    // �I������
    Finalize();
}

/// <summary>
/// ������
/// </summary>
void Stage::Initialize()
{
    // �X�e�[�W���f���̓ǂݍ���
    modelHandle = MV1LoadModel("Data/Stage/BO2Map.mv1");
    MV1SetScale(modelHandle, VGet(4, 4, 4));
    
    // ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
    MV1SetupCollInfo(modelHandle, -1);
    
    // �e�X�g
    MV1SetPosition(modelHandle,VGet(0,0,0));

    isCreatedHitDim = false;
}

/// <summary>
/// �I��������
/// </summary>
void Stage::Finalize()
{
    // �X�e�[�W���f���̌�n��
    MV1DeleteModel(modelHandle);
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }
}

/// <summary>
/// �`��
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �X�e�[�W�Ƃ̓����蔻��
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="checkPosition">�����蔻������������W</param>
/// <param name="moveVector"></param>
void Stage::IsHitCollision(Player& player, const VECTOR& checkPosition, const VECTOR& moveVector)
{
    // ���o�����v���C���[�̎��͂̃|���S�������J������
    if (isCreatedHitDim)
    {
        MV1CollResultPolyDimTerminate(hitDim);
        isCreatedHitDim = false;
    }

    VECTOR FixedPos = checkPosition;

    // �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
    // ( ���o����͈͈͂ړ��������l������ )
    hitDim = MV1CollCheck_Sphere(modelHandle, -1, checkPosition, DefaultSize + VSize(moveVector));

    // ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
    AnalyzeWallAndFloor(checkPosition);

    // �ǃ|���S���Ƃ̓����蔻�菈��
    // �ǃ|���S���Ƃ̓�������`�F�b�N���A�ړ��x�N�g����␳����
    FixedPos = CheckHitWithWall(player, FixedPos);

    // ���|���S���Ƃ̓����蔻��
    // ���|���S���Ƃ̓�������`�F�b�N���A�ړ��x�N�g����␳����
    FixedPos = CheckHitWithFloor(player, FixedPos);

    //return FixedPos;
}


void Stage::AnalyzeWallAndFloor(const VECTOR& CheckPosition)
{
    // �ǃ|���S���Ə��|���S���̐�������������
    wallNum = 0;
    floorNum = 0;

    // ���o���ꂽ�|���S���̐������J��Ԃ�
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        // �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
        if (hitDim.Dim[i].Normal.y < 0.000001f && hitDim.Dim[i].Normal.y > -0.000001f)
        {
            // �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
            if (hitDim.Dim[i].Position[0].y > CheckPosition.y + 1.0f ||
                hitDim.Dim[i].Position[1].y > CheckPosition.y + 1.0f ||
                hitDim.Dim[i].Position[2].y > CheckPosition.y + 1.0f)
            {
                // �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
                if (wallNum < MaxHitColl)
                {
                    // �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
                    wall[wallNum] = &hitDim.Dim[i];

                    // �ǃ|���S���̐������Z����
                    wallNum++;
                }
            }
        }
        else
        {
            // �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
            if (floorNum < MaxHitColl)
            {
                // �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
                floor[floorNum] = &hitDim.Dim[i];

                // ���|���S���̐������Z����
                floorNum++;
            }
        }
    }
}

VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& CheckPosition)
{
    VECTOR FixedPos = CheckPosition;

    // �ǂ̐������������瑁�����^�[��
    if (wallNum == 0)
    {
        return FixedPos;
    }

    // �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
    for (int k = 0; k < HitTryNum; k++)
    {
        // ������\���̂���ǃ|���S����S�Č���
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
            auto Poly = wall[i];

            // �v���C���[�Ɠ������Ă���Ȃ�
            if (HitCheck_Capsule_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), HitWidth, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
            {
                // �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
                // �ړ���̈ʒu���X�V�i�ړ���̏ꏊ��␳�j
                FixedPos = VAdd(FixedPos, VScale(Poly->Normal, HitSlideLength));

                // �ړ������ǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
                for (int j = 0; j < wallNum; j++)
                {
                    // �������Ă����烋�[�v�𔲂���
                    Poly = wall[j];
                    if (HitCheck_Capsule_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), HitWidth, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
                if (isHitWall == false)
                {
                    break;
                }
            }
        }

        // �S���̃|���S���ŉ����o�������݂�O��
        // �S�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����烋�[�v���甲����
        if (isHitWall == false)
        {
            break;
        }
    }

    return FixedPos;
}


VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& CheckPosition)
{
    VECTOR FixedPos = CheckPosition;

    // ���̐������������瑁�����^�[��
    if (floorNum == 0)
    {
        return FixedPos;
    }

    // �����������ǂ����̃t���O��������
    bool IsHitFloor = false;

    // �W�����v�����㏸���̏ꍇ�͏����𕪊�
    if (player.GetState() == Player::State::Jump
        && player.GetJumpPower() > 0.0f)
    {
        // �V��ɓ����Ԃ��鏈�����s��
        // ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ���������
        float MinY = 0.0f;

        // ���|���S���̐������J��Ԃ�
        for (int i = 0; i < floorNum; i++)
        {
            // i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
            auto Poly = floor[i];

            // ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
            HITRESULT_LINE LineRes;					// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
            LineRes = HitCheck_Line_Triangle(FixedPos, VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

            // �ڐG���Ă��Ȃ������牽�����Ȃ�
            if (LineRes.HitFlag == TRUE)
            {
                // ���Ƀ|���S���ɓ������Ă��āA�����܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
                if (!(IsHitFloor == true && MinY < LineRes.Position.y))
                {
                    // �|���S���ɓ��������t���O�𗧂Ă�
                    IsHitFloor = true;

                    // �ڐG�����x���W��ۑ�����
                    MinY = LineRes.Position.y;
                }
            }
        }

        // �ڐG�����|���S���������
        if (IsHitFloor == true)
        {
            // �ڐG�����ꍇ�̓v���C���[�̂x���W��ڐG���W�����ɍX�V
            FixedPos.y = MinY - HitHeight;
            player.OnHitRoof();
        }
    }
    else
    {
        // ���~�����W�����v���ł͂Ȃ��ꍇ�̏���
        // ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
        float MaxY = 0.0f;

        // ���|���S���̐������J��Ԃ�
        for (int i = 0; i < floorNum; i++)
        {
            // i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
            auto Poly = floor[i];

            // �W�����v�����ǂ����ŏ����𕪊�
            HITRESULT_LINE LineRes;					// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
            if (player.GetState() == Player::State::Jump)
            {
                // �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
                LineRes = HitCheck_Line_Triangle(VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), VAdd(FixedPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
            }
            else
            {
                // �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
                LineRes = HitCheck_Line_Triangle(VAdd(FixedPos, VGet(0.0f, HitHeight, 0.0f)), VAdd(FixedPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
            }

            // �������Ă��Ȃ������牽�����Ȃ�
            if (LineRes.HitFlag == TRUE)
            {
                // ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
                if (!(IsHitFloor == true && MaxY > LineRes.Position.y))
                {
                    // �|���S���ɓ��������t���O�𗧂Ă�
                    IsHitFloor = true;

                    // �ڐG�����x���W��ۑ�����
                    MaxY = LineRes.Position.y;
                }
            }
        }

        // ���|���S���ɓ����������ǂ����ŏ����𕪊�
        if (IsHitFloor == true)
        {
            // ���������ꍇ
            // �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
            FixedPos.y = MaxY;

            // ���ɓ���������
            player.OnHitFloor();
        }
        else
        {
            // ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
            player.OnFall();
        }
    }

    return FixedPos;
}