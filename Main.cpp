// �W�����C�u����
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "math.h"
// �ǉ��O�����C�u����
#include "DxLib.h"
#include "EffekseerForDXLib.h"
// ����w�b�_�[
// �V���O���g��
#include "FrameRateManager.h"
#include "ImageDataManager.h"
#include "ModleDataManager.h"
#include "EffectDataManager.h"
#include "SoundDataManager.h"
#include "EffectPlayManager.h"
#include "SoundPlayManager.h"

// �e�w�b�_�[
#include "Common.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // DX���C�u�����̕\�����@���E�B���h�E���[�h�ɕύX����B
#ifdef _DEBUG
    ChangeWindowMode(true);     // �E�B���h�E���[�h
#else
    ChangeWindowMode(false);    // �S��ʃ��[�h
#endif

    //�`���𗠉�ʂɕύX����B
    SetDrawScreen(DX_SCREEN_BACK);

    // �t���V�[���A���`�G�C���A�X��ݒ肷��
    SetFullSceneAntiAliasingMode(4, 2);  // 4x �A���`�G�C���A�V���O��ݒ�

    // �c�w���C�u��������������
    if (DxLib_Init() == -1)
    {
        DxLib_End();  // �G���[���N�����璼���ɏI��
    }

    // ��ʃ��[�h�̃Z�b�g
    SetGraphMode(ScreenWidth,ScreenHeight, ScreenColorBitNum);

    // �`���O���t�B�b�N�̈�̎w��
    SetDrawScreen(DX_SCREEN_BACK);

    // �V���O���g���N���X���C���X�^���X��
    FrameRateManager::CreateInstance();     // �t���[�����[�g
    ImageDataManager::CreateInstance();     // �摜�f�[�^
    ModleDataManager::CreateInstance();     // ���f���f�[�^
    EffectDataManager::CreateInstance();    // �G�t�F�N�g�f�[�^
    SoundDataManager::CreateInstance();     // ���f�[�^
    EffectPlayManager::CreateInstance();    // �G�t�F�N�g�Đ�
    SoundPlayManager::CreateInstance();     // ���Đ�

    // �Q�[���̃C���X�^���X���쐬
    Game game;

    // �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // �Q�[���̍X�V
        game.Update();


        // Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
        // �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
        if (ProcessMessage() < 0)
        {
            break;
        }
        // �����d�r�b�L�[��������Ă����烋�[�v���甲����
        else if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }
    }

    // Effekseer���I������B
    Effkseer_End();

    // �c�w���C�u�����̌�n��
    DxLib_End();

    // �\�t�g�̏I��
    return 0;
}
