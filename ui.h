//==========================================
//
//UI�̃N���X�Ǘ��錾������t�@�C��[ui.h]
//Author:chiba haruki
//
//==========================================

#pragma once

//==========================================
//�C���N���[�h
#include "object3D.h"
#include <cstdio>


//======================================================
//UI�̃}�l�[�W���[�Ǘ��N���X
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CUI()override;							//�f�X�g���N�^
	HRESULT Init()override;					//����������
	void Uninit()override;					//�j������
	void Update()override;					//�X�V����
	void Draw()override;					//�`�揈��

	bool& GetDraw() { return m_bDraw; }     //�g���Ă��邩�ǂ����𔻒肷������擾

	static CUI* Create(CObject3D::TYPE_UI typeui); //��������

private:
	bool m_bDraw; //�g���Ă��邩�ǂ����𔻒肷��ϐ�
};


//======================================================
//���݂̔z�u�����I�u�W�F�N�g�̏ꏊ��UI���o���N���X�Ǘ�
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CCreateInObject()override;                         //�f�X�g���N�^
};


//======================================================
//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�������N���X�Ǘ�
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CTalkText()override;                         //�f�X�g���N�^
	HRESULT Init()override;                       //����������
	void Draw()override;                          //�`�揈��
};


//======================================================
//�Ď��J��������ł郌�[�U�[�N���X
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CLaserCamare()override;                         //�f�X�g���N�^
	HRESULT Init()override;                          //����������
	void Update()override;                           //�X�V����
	void Draw()override;                             //�`�揈��
};
