//=======================================================
//
//UI�����鏈��[ui.cpp]
//Auther;HARUKI CHIBA
//
//=======================================================

#include "ui.h"
#include "manager.h"
#include "create_enemy.h"


//============================
//�R���X�g���N�^
//============================
CUI::CUI(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 200.0f;
	m_bDraw = false;
}


//============================
//�f�X�g���N
//============================
CUI::~CUI()
{

}


//============================
//����������
//============================
HRESULT CUI::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}


//============================
//�j������
//============================
void CUI::Uninit()
{
	CObject3D::Uninit();
}


//============================
//�X�V����
//============================
void CUI::Update()
{

}


//============================
//�`�揈��
//============================
void CUI::Draw()
{
	CObject3D::Draw();
}


//============================
//�`�揈��
//============================
void CUI::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//============================
//��������
//============================
CUI* CUI::Create(CObject3D::TYPE_UI typeui)
{
	CUI* pUI = nullptr;

	if (typeui == CObject3D::TYPE_UI::INUI)
	{
		pUI = new CCreateInObject();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\effect000.jpg";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::TELEPHONPOLEUI)
	{
		pUI = new CCreateInObject();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\��.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::TALKTEXTR)
	{
		pUI = new CTalkText();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\Text\\Talk.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::LASER)
	{
		pUI = new CLaserCamare();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\Laser000.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}
	return nullptr;
}


//=============================================================================================================================
//����text�ɏ����o����I�u�W�F�N�g�̏ꏊ��UI�����鏈��
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CCreateInObject::CCreateInObject(int nPriority) : CUI(nPriority)
{
	
}


//============================
//�f�X�g���N
//============================
CCreateInObject::~CCreateInObject()
{

}


//============================
//����������
//============================
HRESULT CCreateInObject::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}


//============================
//�j������
//============================
void CCreateInObject::Uninit()
{
	CUI::Uninit();
}


//============================
//�X�V����
//============================
void CCreateInObject::Update()
{

}


//============================
//�`�揈��
//============================
void CCreateInObject::Draw()
{
	CUI::Draw();
}


//============================
//�`�揈��
//============================
void CCreateInObject::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//=============================================================================================================================
//����text�ɏ����o����I�u�W�F�N�g�̏ꏊ��UI�����鏈��
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CTalkText::CTalkText(int nPriority) : CUI(nPriority)
{

}


//============================
//�f�X�g���N
//============================
CTalkText::~CTalkText()
{

}


//============================
//����������
//============================
HRESULT CTalkText::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;
	CObject3D::SetSize(40.0f, 0.0f, 40.0f);

	return S_OK;
}


//============================
//�j������
//============================
void CTalkText::Uninit()
{
	CUI::Uninit();
}


//============================
//�X�V����
//============================
void CTalkText::Update()
{
	
}


//============================
//�`�揈��
//============================
void CTalkText::Draw()
{
	if (GetDraw() == true)
	{
		CUI::Draw();
	}
}


//============================
//�`�揈��
//============================
void CTalkText::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//=============================================================================================================================
//�J��������o�郌�[�U�[�̏���
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CLaserCamare::CLaserCamare(int nPriority) : CUI(nPriority)
{
	m_nRandom = 0;
}


//============================
//�f�X�g���N
//============================
CLaserCamare::~CLaserCamare()
{

}


//============================
//����������
//============================
HRESULT CLaserCamare::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}

	CObject3D::SetSize(80.0f, 20.0f, 20.0f); //�傫����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.54f, 1.54f); //������ݒ�

	//�ʒu���Ď��J�����̏㕔�����ɐݒ肷��
	m_pos = D3DXVECTOR3(CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y - 20.0f,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z - 35.0f);

	return S_OK;
}


//============================
//�j������
//============================
void CLaserCamare::Uninit()
{
	CUI::Uninit();
}


//============================
//�X�V����
//============================
void CLaserCamare::Update()
{
	if (CObject3D::CollisionPrtsPlayer(20.0f,80.0f,20.0f) == true)
	{
		m_nRandom = -400 + rand() % 800;
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMY,0, D3DXVECTOR3((float)-200, 0.0f, -50.0f));
		CObject3D::Release();
		return;
	}

	//�J�����̏㕔���̏�񂪂Ȃ��Ȃ�����
	if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) == nullptr)
	{
		CObject3D::Release();
		return;
	}
}


//============================
//�`�揈��
//============================
void CLaserCamare::Draw()
{
	//CUI::DrawNoml();
}


//============================
//�`�揈��
//============================
void CLaserCamare::DrawNoml()
{
	CObject3D::DrawNoml();
}