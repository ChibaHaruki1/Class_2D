//============================================
//
//�r���{�[�h�N���X�Ǘ�[billboard.h]
//Auther:Haruki Chiba
//
//============================================

#pragma once

//============================================
//�C���N���[�h
#include "object3D.h"

//==================================================================
//�r���{�[�h����
class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CBillboard()override;						   //�f�X�g���N�^
	HRESULT Init()override;						   //����������
	void Uninit()override;						   //�j������
	void Update()override;						   //�X�V����
	void Draw()override;						   //�`�揈��

	static CBillboard* Create();                   //��������
};

