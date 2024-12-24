//===================================
//
//�w�i�̃v���g�^�C�v�錾[bg.h]
//Author:chiba haruki
//
//===================================

#pragma once

//======================================
//�C���N���[�h
#include "main.h"
#include "object2D.h"


//==================================================================
//����낤�Ƃ��Ă���I�u�W�F�N�g��UI�N���X
class CNowCreateUI : public CObject2D
{
public:
	CNowCreateUI(int nPriority = DEFAULT_PRIORITY);
	~CNowCreateUI()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CNowCreateUI* Create(int Number);
};

//==================================================================
//�X�̃��j���[�ꗗUI�N���X
class CShopMenu : public CObject2D
{
public:
	CShopMenu(int nPriority = DEFAULT_PRIORITY);
	~CShopMenu()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CShopMenu* Create();
};

//==================================================================
//BuyText�\��UI�N���X
class CBuyText : public CObject2D
{
public:
	CBuyText(int nPriority = DEFAULT_PRIORITY);
	~CBuyText()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CBuyText* Create();

};

//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage : public CObject2D
{
public:
	CSelectGage(int nPriority = DEFAULT_PRIORITY);
	~CSelectGage()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	float& GetSizeX() { return m_fSizeX; }
	float& GetSize1X() { return m_fSize1X; }
	float& GetSizeY() { return m_fSizeY; }
	float& GetSize1Y() { return m_fSize1Y; }

	static CSelectGage* Create();

private:
	float m_fSizeX;
	float m_fSize1X;
	float m_fSizeY;
	float m_fSize1Y;
};

//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage001 : public CSelectGage
{
public:
	CSelectGage001(int nPriority = DEFAULT_PRIORITY);
	~CSelectGage001()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CSelectGage001* Create();
};