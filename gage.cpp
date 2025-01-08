//===================================================================
//
//�Q�[�W�Ɋւ��鏈��[gage.cpp]
//Ajther:Haruki Chiba
//
//===================================================================

//===========================
//�C���N���[�h
#include "gage.h"
#include "manager.h"


//=======================================================================================================================================================
//�R���Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CFuelGage::CFuelGage(int nPriority) : CObject3D(nPriority)
{
	SetSizeY(MAX_SIZEY);
	SetAlpha(0);
	m_bUse = false;
}

//===========================
//�f�X�g���N�^
//===========================
CFuelGage::~CFuelGage()
{
	m_bUse = false;
}

//===========================
//����������
//===========================
HRESULT CFuelGage::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	CObject3D::SetSize(15.0f, GetSizeY(), 20.0f); //�傫����ݒ�

	return S_OK;
}

//============================
//�j������
//============================
void CFuelGage::Uninit()
{
	CObject3D::Uninit();
}

//============================
//�X�V����
//============================
void CFuelGage::Update()
{
	SetPos(D3DXVECTOR3(CManager::GetScene()->GetPlayerX()->GetPos().x - 50.0f,
		CManager::GetScene()->GetPlayerX()->GetPos().y + 80.0f,
		CManager::GetScene()->GetPlayerX()->GetPos().z));

	CObject3D::SetAdjustmentSizeY(15.0f, GetSizeY(), 20.0f); //�傫����ݒ�
	CObject3D::SetCol(255, 255, 255, GetAlpha());

	if (m_bUse == true)
	{
		if (GetAlpha() != 255)
		{
			SetAlpha(255);
		}

		if (GetSizeY() > 0)
		{
			GetSizeY() -= MAX_MAINAS_GAGESPEED;
		}
		else
		{
			SetSizeY(0.0f);
		}
	}
	else if (m_bUse == false)
	{
		if (GetAlpha() > 0)
		{
			GetAlpha() -= 5;
		}

		if (GetSizeY() < MAX_SIZEY)
		{
			GetSizeY() += MAX_MAINAS_GAGESPEED;
		}
	}

	//m_move = CManager::GetScene()->GetPlayerX()->GetMove();

	CObject3D::Update();
}


//============================
//�`�揈��
//============================
void CFuelGage::Draw()
{
	if (GetAlpha() > 5&& GetSizeY()>5)
	{
		CObject3D::Draw();
	}
}

//============================
//��������
//============================
CFuelGage* CFuelGage::Create()
{
	CFuelGage* pFuelGage = new CFuelGage();

	if (pFuelGage != nullptr)
	{
		if (SUCCEEDED(pFuelGage->Init()))
		{
			pFuelGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png");
			pFuelGage->Lood();
			return pFuelGage;
		}
	}

	return nullptr;
}


//=======================================================================================================================================================
//�Q�[�Wmanager����
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CManagerGage::CManagerGage(int nPriority) : CObject2D(nPriority)
{
	m_fHPSizeX = 400.0f;
	m_fBossHPSizeX = SCREEN_WIDTH;
	m_fSaveSizeX = 0.0f;
}

//===========================
//�f�X�g���N�^
//===========================
CManagerGage::~CManagerGage()
{

}

//===========================
//����������
//===========================
HRESULT CManagerGage::Init()
{
	//���������������邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
//�w�i�̏I������
//======================
void CManagerGage::Uninit(void)
{
	CObject2D::Uninit();
}


//=======================
//�w�i�̍X�V����
//=======================
void CManagerGage::Update()
{
	
}


//=====================
//�w�i�̕`�揈��
//=====================
void CManagerGage::Draw()
{
	CObject2D::Draw();
}


//===================================
//�Q�[�W�̐���
//===================================
CManagerGage* CManagerGage::Create(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr;

	//�^�C�v���v���C���[��HP�̎�
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGage(1);
		CreateLeave(type);
		CManager::GetInstance()->GetCreateObjectInstnace(TYPE::FUELGAGE,0, pManagerGage->GetPos());
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png");
	}

	//�^�C�v���{�X��HP�̎�
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGage(1);
		CreateLeave(type);
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BossHpGage.png");
	}

	if (SUCCEEDED(pManagerGage->Init()))
	{
		pManagerGage->Lood();
		return pManagerGage;
	}

	return nullptr;
}

//===================================
//�c���Q�[�W�̐���
//===================================
CManagerGage* CManagerGage::CreateLeave(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr;

	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGageLeave(0);
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage001.png");
	}
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGageLeave(0);
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BloackGage000.png");
	}

	if (SUCCEEDED(pManagerGage->Init()))
	{
		pManagerGage->Lood();
		return pManagerGage;

	}

	return nullptr;
}


//=======================================================================================================================================================
//�v���C���[�̃Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CPlayerHPGage::CPlayerHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX();
}

//===========================
//�f�X�g���N�^
//===========================
CPlayerHPGage::~CPlayerHPGage()
{

}


//===========================
//����������
//===========================
HRESULT CPlayerHPGage::Init()
{
	//���������������邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	CObject2D::SetSIze(0.0f, GetPlayerHPSizeX(), 40.0f, 70.0f); //�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�

	return S_OK;
}

//===========================
//�X�V����
//===========================
void CPlayerHPGage::Update()
{
	//���݂�HP�Q�[�W��荂����
	if (m_fSaveSizeX > GetPlayerHPSizeX())
	{
		m_fSaveSizeX -= 0.64f * 2.0f;        //���X��HP�Q�[�W�����炷
	}

	else if (m_fSaveSizeX <= GetPlayerHPSizeX())
	{
		m_fSaveSizeX = GetPlayerHPSizeX();   //���݂�HP�Q�[�W�Ɠ���������
	}

	CObject2D::SetSIze(0.0f, m_fSaveSizeX, MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //���炩�Ɍ����Ă���悤�Ɍ�����
}


//=======================================================================================================================================================
//�{�X�̃Q�[�W�̏���
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CBossHPGage::CBossHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //HP�𓯊�������
}

//===========================
//�f�X�g���N�^
//===========================
CBossHPGage::~CBossHPGage()
{

}


//===========================
//����������
//===========================
HRESULT CBossHPGage::Init()
{
	//���������������邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//SetCol(100,100); //alpha�l��ݒ�
	CObject2D::SetSIze(0.0f, GetBossHPSizeX(), (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�
	return S_OK; //������Ԃ�
}


//===========================
//�X�V����
//===========================
void CBossHPGage::Update()
{
	//���݂�HP�Q�[�W��荂����
	if (m_fSaveSizeX > GetBossHPSizeX())
	{//���炳�ꂽ���������炷
		m_fSaveSizeX -= 0.64f * 2.0f;           //���X��HP�Q�[�W�����炷
	}
	else if (m_fSaveSizeX <= GetBossHPSizeX())
	{
		m_fSaveSizeX = GetBossHPSizeX(); //���݂�HP�Q�[�W�Ɠ���������
	}

	CObject2D::SetSIze(0.0f, m_fSaveSizeX, (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //���炩�Ɍ����Ă���悤�Ɍ�����
}


//=======================================================================================================================================================
//�v���C���[��HP�Q�[�W���c������
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CPlayerHPGageLeave::CPlayerHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX();
}

//===========================
//�f�X�g���N�^
//===========================
CPlayerHPGageLeave::~CPlayerHPGageLeave()
{

}


//===========================
//����������
//===========================
HRESULT CPlayerHPGageLeave::Init()
{
	//���������������邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	CObject2D::SetSIze(0.0f, GetPlayerHPSizeX(), MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�

	return S_OK;
}


//=======================================================================================================================================================
//�{�X��HP�Q�[�W���c������
//=======================================================================================================================================================

//===========================
//�R���X�g���N�^
//===========================
CBossHPGageLeave::CBossHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //HP�𓯊�������
}

//===========================
//�f�X�g���N�^
//===========================
CBossHPGageLeave::~CBossHPGageLeave()
{

}


//===========================
//����������
//===========================
HRESULT CBossHPGageLeave::Init()
{
	//���������������邩����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	//SetCol(100, 100); //alpha�l��ݒ�
	CObject2D::SetSIze(0.0f, GetBossHPSizeX(), (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //�傫�������炩���ߌ��߂Ȃ��ƈ�u��ʂɃt���X�N���[���ŏo�Ă��܂�

	return S_OK;
}