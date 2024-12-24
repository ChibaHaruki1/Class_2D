//===================================
//
//�w�i�̃v���g�^�C�v�錾[bg.h]
//Author:chiba haruki
//
//===================================

#pragma once

//===================================
//�C���N���[�h
#include "object2D.h"
#include "scene.h"


//==================================================================
//�w�i�̊Ǘ����N���X
class CManagerBg : public CObject2D
{
public:
	CManagerBg(int nPriority = DEFAULT_PRIORITY);
	~CManagerBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void  Update()override;
	void Draw()override;
	void DrawNoml()override;

	static CManagerBg* Create(CScene::MODE mode);
};


//==================================================================
//�^�C�g���w�i
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);
	~CTitleBg()override;
private:
	
};

//==================================================================
//���U���g�w�i
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);
	~CResultBg()override;
};


//==================================================================
//�Q�[���I�[�o�[�w�i
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);
	~CGameOverBg()override;
	void Update()override;
};


//==================================================================
//�V���b�v���̔w�i
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);
	~CShopScreen()override;
	HRESULT Init()override;
	void Update()override;

	static CShopScreen* Create();
};