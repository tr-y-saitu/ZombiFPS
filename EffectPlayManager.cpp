#include "EffectPlayManager.h"

// ������
EffectPlayManager* EffectPlayManager::effectPlayManager = NULL;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectPlayManager::EffectPlayManager()
    : playingEffectHandle(0)
{
    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    //DirectX11�̃o�[�W�������w��
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effkseer_Init(20000) == -1)
    {
        DxLib_End();
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);

    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);

    //EffekseerSyncronizDxlib();

    // �g�p�G�t�F�N�g��ǂݍ���
    LoadEffect();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectPlayManager::~EffectPlayManager()
{
    // �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
}

/// <summary>
/// �G�t�F�N�g�̓ǂݍ���
/// </summary>
void EffectPlayManager::LoadEffect()
{
    // �G�t�F�N�g�̃��[�h

    // �G�t�F�N�g���X�g�ɏ�������

}

/// <summary>
/// �C���X�^���X���쐬
/// </summary>
void EffectPlayManager::CreateInstance()
{
    if (effectPlayManager == NULL)
    {
        effectPlayManager = new EffectPlayManager();
    }
}

/// <summary>
/// �G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^��n��
/// </summary>
/// <returns>EffectPlayManager�̃|�C���^</returns>
EffectPlayManager* EffectPlayManager::GetInstance()
{
    return effectPlayManager;
}

/// <summary>
/// �G�t�F�N�g�}�l�[�W���[�̍폜
/// </summary>
void EffectPlayManager::DeleteInstance()
{
    delete(effectPlayManager);
}

/// <summary>
/// ������
/// </summary>
void EffectPlayManager::Initialize()
{
    //// �Đ����̃G�t�F�N�g���폜����
    for (int i = playingList.size() - 1; i >= 0; i--)
    {
        // �Đ��������ׂ�
        if (!IsEffekseer3DEffectPlaying(playingList[i]))
        {
            StopEffekseer3DEffect(playingList[i]);      // ��~
            playingList.erase(playingList.begin() + i); // �폜
        }
    }
}

/// <summary>
/// �X�V
/// </summary>
void EffectPlayManager::Update()
{
    // �G�t�F�N�g���I��������A�Đ�������폜����
    for (int i = 0; i < playingList.size(); i++)
    {
        // �Đ��������ׂ�
        if (IsEffekseer3DEffectPlaying(playingList[i]) == NoPlay)
        {
            playingList.erase(playingList.begin());
        }
    }
}

/// <summary>
/// ���ݍĐ����̃G�t�F�N�g�����邩�ǂ���
/// </summary>
/// <returns>����:true  �Ȃ�:false</returns>
bool EffectPlayManager::IsAnyEffectPlaying()
{
    bool isPlaying = false;

    for (int i = 0; i < playingList.size(); i++)
    {
        // �Đ��������ׂ�
        if (IsEffekseer3DEffectPlaying(playingList[i]) == Play)
        {
            isPlaying = true;
        }
    }

    return isPlaying;
}

/// <summary>
/// �ǂݍ��񂾃G�t�F�N�g���X�g����Đ�
/// </summary>
/// <param name="effectType">�Đ�����G�t�F�N�g�̎��</param>
/// <param name="playPosition">�Đ�������W</param>
/// <param name="scale">���G�t�F�N�g�̕`��T�C�Y</param>
/// NOTE:��3�����́uscale�v�̓f�t�H���g�����@�f�t�H���g�l{1.0f,1.0f,1.0f}
///      1.0f���ǂݍ��ݎ��T�C�Y
void EffectPlayManager::PlayEffectList(EffectType effectType, VECTOR playPosition, VECTOR scale)
{
    // �Đ�����G�t�F�N�g��ݒ�
    playingEffectHandle = effectList[effectType];

    // �Đ�����G�t�F�N�g�̊g�嗦��ݒ�
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);

    // �G�t�F�N�g���Đ�
    PlayEffekseer3DEffect(playingEffectHandle);

    // �Đ������X�g�ɒǉ�
    playingList.push_back(playingEffectHandle);

    // �G�t�F�N�g�̕`����W��ݒ�
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, playPosition.x, playPosition.y, playPosition.z);
}

