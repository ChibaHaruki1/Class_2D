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
	CManagerBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerBg()override;						   //�f�X�g���N�^
	HRESULT Init()override;						   //����������
	void Uninit()override;						   //�j������
	void  Update()override;						   //�X�V����
	void Draw()override;						   //�`�揈��

	static CManagerBg* Create(CScene::MODE mode);  //��������

private:
	int nCountAlpha; //alpha�l��ۊǂ���p�̕ϐ�
};


//==================================================================
//�^�C�g���w�i
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);    //�R���X�g���N�^
	~CTitleBg()override;                           //�f�X�g���N�^
};

//==================================================================
//���U���g�w�i
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);   //�R���X�g���N�^
	~CResultBg()override;                          //�f�X�g���N�^
};


//==================================================================
//�Q�[���I�[�o�[�w�i
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CGameOverBg()override;                         //�f�X�g���N�^
	void Update()override;                          //�X�V����
};


//==================================================================
//�V���b�v���̔w�i
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CShopScreen()override;                         //�f�X�g���N�^
	HRESULT Init()override;                         //����������
	void Update()override;                          //�X�V����

	static CShopScreen* Create();                   //��������
};