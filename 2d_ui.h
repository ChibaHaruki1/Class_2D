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
	CNowCreateUI(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CNowCreateUI()override;                         //�f�X�g���N�^
	HRESULT Init()override;                          //����������
	void Uninit()override;                           //�j������
	void Update()override;                           //�X�V����
	void Draw()override;                             //�`�揈��
};

//==================================================================
//�X�̃��j���[�ꗗUI�N���X
class CShopMenu : public CObject2D
{
public:
	CShopMenu(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CShopMenu()override;						  //�f�X�g���N�^
	HRESULT Init()override;						  //����������
	void Uninit()override;						  //�j������
	void  Update()override;						  //�X�V����
	void Draw()override;						  //�`�揈��

	static CShopMenu* Create();                   //��������
};

//==================================================================
//BuyText�\��UI�N���X
class CBuyText : public CObject2D
{
public:
	CBuyText(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CBuyText()override;						 //�f�X�g���N�^
	HRESULT Init()override;						 //����������
	void Uninit()override;						 //�j������
	void  Update()override;						 //�X�V����
	void Draw()override;						 //�`�揈��

	static CBuyText* Create();                   //��������

};

//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage : public CObject2D
{
public:
	CSelectGage(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CSelectGage()override;							//�f�X�g���N�^
	HRESULT Init()override;							//����������
	void Uninit()override;							//�j������
	void  Update()override;							//�X�V����
	void Draw()override;							//�`�揈��

	float& GetSizeX() { return m_fSizeX; }          //�I���Q�[�W��X���̑傫���̎擾
	float& GetSizeY() { return m_fSizeY; }          //�I���Q�[�W��y���̑傫�����擾
	float& GetSize1X() { return m_fSize1X; }        //�I���Q�[�W001��x���̑傫���̎擾
	float& GetSize1Y() { return m_fSize1Y; }        //�I���Q�[�W001��y���̑傫���̎擾

	static CSelectGage* Create();                   //��������

private:
	float m_fSizeX;    //�I���Q�[�W��X���̑傫��
	float m_fSizeY;    //�I���Q�[�W��y���̑傫��
	float m_fSize1X;   //�I���Q�[�W001��x���̑傫��
	float m_fSize1Y;   //�I���Q�[�W001��y���̑傫��
};

//==================================================================
//�I�Ԏ���UI�N���X
class CSelectGage001 : public CSelectGage
{
public:
	CSelectGage001(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CSelectGage001()override;						   //�f�X�g���N�^
	HRESULT Init()override;							   //����������
	void Uninit()override;							   //�j������
	void  Update()override;							   //�X�V����
	void Draw()override;							   //�`�揈��

	static CSelectGage001* Create();                   //��������
};