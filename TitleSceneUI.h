#pragma once
#include "SceneUIBase.h"

/// <summary>
/// �^�C�g���V�[����UI
/// </summary>
class TitleSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TitleSceneUI();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleSceneUI();

    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

private:

};

