#include "Common.h"
#include "FrameRateManager.h"

// ������
FrameRateManager* FrameRateManager::frameRateManager = NULL;

// �R�X�g���N�^
FrameRateManager::FrameRateManager()
    : fpsCountStartTime     (0)
    , nowFpsCount           (0)
    , deltaTime             (0)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FrameRateManager::~FrameRateManager()
{
    // �����Ȃ�
}

/// <summary>
/// �C���X�^���X���쐬
/// </summary>
void FrameRateManager::CreateInstance()
{
    if (frameRateManager == NULL)
    {
        frameRateManager = new FrameRateManager();
    }
}

/// <summary>
/// �t���[�����[�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��Ԃ�
/// </summary>
/// <returns>�C���X�^���X�̂���A�h���X</returns>
FrameRateManager* FrameRateManager::GetInstance()
{
    return frameRateManager;
}

/// <summary>
/// �C���X�^���X�̍폜
/// </summary>
void FrameRateManager::DeleteInstance()
{
    delete(frameRateManager);
}

/// <summary>
/// �X�V
/// </summary>
void FrameRateManager::Update()
{
    // 1�t���[���ڂȂ玞�����L��
    if (nowFpsCount == 0)
    {
        fpsCountStartTime = GetNowCount();	//��ƂȂ鎞�Ԃ����߂�
    }
    // 60�t���[���ڂȂ畽�ς��v�Z����
    if (nowFpsCount == (float)SetFPS)
    {
        int nowTime = GetNowCount();		//���̎��Ԃ�ݒ�
        deltaTime = 1000.f / ((nowTime - fpsCountStartTime) / (float)SetFPS);	//�P�t���[���ɂ����������Ԃ��v�Z
        nowFpsCount = 0;					//�t���[���̃J�E���g��������
    }
    else
    {
        nowFpsCount++;
    }
}

/// <summary>
/// �ҋ@����
/// </summary>
void FrameRateManager::SleepForFPS()
{
    //������������
    int _tookTime = GetNowCount() - fpsCountStartTime;
    //�҂ׂ�����
    int _waitTime = nowFpsCount * 1000 / SetFPS - _tookTime;

    //�҂ׂ����ԑҋ@����
    if (_waitTime > 0)
    {
        Sleep(_waitTime);
    }
}