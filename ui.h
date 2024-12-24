//===================================
//
//UI�̃N���X�Ǘ��錾������t�@�C��[ui.h]
//Author:chiba haruki
//
//===================================

#ifndef _UI_H_  //���̃}�O����`������Ă��Ȃ���������
#define _UI_H_  //��d�C���N���[�h�h�~�̃}�N����`

#include "object3D.h"
#include <cstdio>

//���ݔz�u���Ă���I�u�W�F�N�g��UI������N���X
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);
	~CUI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

	float& GetSIzeX() { return m_fSizeX; }
	bool& GetDraw() { return m_bDraw; }

	static CUI* Create(CObject3D::TYPE_UI typeui);

private:
	float m_fSizeX;
	bool m_bDraw;
};


//���݂̔z�u�����I�u�W�F�N�g�̏ꏊ��UI���o���N���X�Ǘ�
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);
	~CCreateInObject()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
};


//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�������N���X�Ǘ�
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);
	~CTalkText()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;
};

//�Ď��J��������ł郌�[�U�[�N���X
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);
	~CLaserCamare()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void DrawNoml()override;

private:
	int m_nRandom;
};

#endif 
