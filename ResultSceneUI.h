#pragma once
#include "SceneUIBase.h"

/// <summary>
/// ���U���g�V�[����UI
/// </summary>
class ResultSceneUI : public SceneUIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ResultSceneUI();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ResultSceneUI();

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


