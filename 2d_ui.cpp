//===================================
//
//�Q���̂t�h�̏����ݒ�[2d_ui.cpp]
//Author:chiba haruki
//
//===================================

//�C���N���[�h
#include "2d_ui.h"
#include "rendererh.h"
#include "manager.h"


//==========================
//�����t���R���X�g���N�^
//==========================
CNowCreateUI::CNowCreateUI(int nPriority) : CObject2D(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CNowCreateUI::~CNowCreateUI()
{

}


//======================
//�w�i�̏���������
//======================
HRESULT CNowCreateUI::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f,100.0f, 0.0f,100.0f);

	return S_OK; //������Ԃ�
}


//======================
//�w�i�̏I������
//======================
void CNowCreateUI::Uninit()
{
	CObject2D::Uninit();
}


//=======================
//�w�i�̍X�V����
//=======================
void CNowCreateUI::Update()
{
	
}


//=====================
//�w�i�̕`�揈��
//=====================
void CNowCreateUI::Draw()
{
	CObject2D::Draw();
}


//===========================================================================================================================================================
//���j���[UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CShopMenu::CShopMenu(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\Menyu001.png");
}


//=======================
//�f�X�g���N�^
//=======================
CShopMenu::~CShopMenu()
{

}


//=======================
//����������
//=======================
HRESULT CShopMenu::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, 600.0f, 0.0f, 700.0f);

	return S_OK; //������Ԃ�
}


//========================
//�j������
//========================
void CShopMenu::Uninit()
{
	CObject2D::Uninit();
}


//========================
//�X�V����
//========================
void CShopMenu::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//�`�揈��
//========================
void CShopMenu::Draw()
{
	CObject2D::Draw();
}


//========================
//��������
//========================
CShopMenu* CShopMenu::Create()
{
	CShopMenu* pText = new CShopMenu(0);

	if (SUCCEEDED(pText->Init()))
	{
		if (pText != nullptr)
		{
			pText->Lood();
			return pText;
		}
	}

	return nullptr;
}


//===========================================================================================================================================================
//���j���[UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CBuyText::CBuyText(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\buy001.png");
}


//=======================
//�f�X�g���N�^
//=======================
CBuyText::~CBuyText()
{

}


//=======================
//����������
//=======================
HRESULT CBuyText::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, 600.0f, 0.0f, SCREEN_HEIGHT);
	SetCol(200, 200);

	return S_OK; //������Ԃ�
}


//========================
//�j������
//========================
void CBuyText::Uninit()
{
	CObject2D::Uninit();
}


//========================
//�X�V����
//========================
void CBuyText::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//�`�揈��
//========================
void CBuyText::Draw()
{
	CObject2D::Draw();
}


//========================
//��������
//========================
CBuyText* CBuyText::Create()
{
	CBuyText* pText = new CBuyText(0);

	if (SUCCEEDED(pText->Init()))
	{
		if (pText != nullptr)
		{
			pText->Lood();
			return pText;
		}
	}

	return nullptr;
}


//===========================================================================================================================================================
//�I������UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CSelectGage::CSelectGage(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage.png");
	m_fSizeX = 0.0f;
	m_fSize1X = 600.0f;
	m_fSizeY = 50.0f;
	m_fSize1Y = 150.0f;
}


//=======================
//�f�X�g���N�^
//=======================
CSelectGage::~CSelectGage()
{

}


//=======================
//����������
//=======================
HRESULT CSelectGage::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, m_fSizeX, 0.0f,m_fSizeY);
	SetCol(100, 100);

	return S_OK; //������Ԃ�
}


//========================
//�j������
//========================
void CSelectGage::Uninit()
{
	CObject2D::Uninit();
}


//========================
//�X�V����
//========================
void CSelectGage::Update()
{
	CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//�`�揈��
//========================
void CSelectGage::Draw()
{
	CObject2D::Draw();
}


//========================
//��������
//========================
CSelectGage* CSelectGage::Create()
{
	CSelectGage* pSelectGage = new CSelectGage(3);

	if (SUCCEEDED(pSelectGage->Init()))
	{
		if (pSelectGage != nullptr)
		{
			pSelectGage->Lood();
			return pSelectGage;
		}
	}

	return nullptr;
}


//===========================================================================================================================================================
//�I������UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CSelectGage001::CSelectGage001(int nPriority) : CSelectGage(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage001.png");

}


//=======================
//�f�X�g���N�^
//=======================
CSelectGage001::~CSelectGage001()
{

}


//=======================
//����������
//=======================
HRESULT CSelectGage001::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, GetSizeX(), 0.0f, GetSizeY());
	//SetCol(100, 100);
	//SetCol(100.0f,100.0f);

	return S_OK; //������Ԃ�
}


//========================
//�j������
//========================
void CSelectGage001::Uninit()
{
	CObject2D::Uninit();
}


//========================
//�X�V����
//========================
void CSelectGage001::Update()
{
	//CObject2D::SetSIze(GetSizeX(), GetSize1X(), GetSizeY(), GetSize1Y());
}

//========================
//�`�揈��
//========================
void CSelectGage001::Draw()
{
	CObject2D::Draw();
}


//========================
//��������
//========================
CSelectGage001* CSelectGage001::Create()
{
	CSelectGage001* pSelectGage = new CSelectGage001(3);

	if (SUCCEEDED(pSelectGage->Init()))
	{
		if (pSelectGage != nullptr)
		{
			pSelectGage->Lood();
			return pSelectGage;
		}
	}

	return nullptr;
}