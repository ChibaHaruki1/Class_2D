//===================================
//
//�n�ʂ̐ݒ�����鏈��[particles.cpp]
//Author:chiba haruki
//
//===================================

#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//�R���X�g���N�^
//============================
CParticles::CParticles(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 10.0f;
	m_aFileName = "data\\TEXTURE\\UI\\008.png";
	PosX = 0.0f;

	m_nRandom = 0;
	m_nLife = 0;
}


//============================
//�f�X�g���N�^
//============================
CParticles::~CParticles()
{

}


//============================
//�|���S���̏���������
//============================
HRESULT CParticles::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;

	return S_OK;
}

//==========================
//�|���S���̏I������
//==========================
void CParticles::Uninit()
{
	CObject3D::Uninit();
}

//========================
//�|���S���̍X�V����
//========================
void CParticles::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);
	//SetCol(m_nRandom, 0, 0);
	
	m_nLife++;

	if (m_nLife >= MAX_PARTICLES_LIFE)
	{
		CObject3D::Release(); //���g�̉��
		return; //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();
}

//======================
//�|���S���̕`�揈��
//======================
void CParticles::Draw()
{
	//CObject3D::DrawEffect(); //���N���X�̕`�揈�����Ă�
	CObject3D::Draw();
}


//======================
//�|���S���̕`�揈��
//======================
void CParticles::DrawNoml()
{

}


//========================
//���𐶐�
//========================
CParticles* CParticles::Create(D3DXVECTOR3 pos)
{
	CParticles* pPraticles = new CParticles(2); //���I�m��

	if (SUCCEEDED(pPraticles->Init()))
	{
		if (pPraticles != nullptr)
		{
			pPraticles->m_pos = pos;
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}


//
//
//


//============================
//�R���X�g���N�^
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 10.0f;
	m_aFileName = "data\\TEXTURE\\Circle003.png";
	PosX = 0.0f;

	m_nRandom = 0;
	m_nLife = 0;
}


//============================
//�f�X�g���N�^
//============================
CParticles001::~CParticles001()
{

}


//============================
//�|���S���̏���������
//============================
HRESULT CParticles001::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;

	return S_OK;
}


//==========================
//�|���S���̏I������
//==========================
void CParticles001::Uninit()
{
	CObject3D::Uninit();
}


//========================
//�|���S���̍X�V����
//========================
void CParticles001::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);
	//SetCol(m_nRandom, 0, 0);

	m_nLife++;

	m_pos.y += 2.0f;

	if (m_nLife >= MAX_PARTICLES001_LIFE)
	{
		CObject3D::Release(); //���g�̉��
		return; //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();
}


//======================
//�|���S���̕`�揈��
//======================
void CParticles001::Draw()
{
	CObject3D::DrawEffect(); //���N���X�̕`�揈�����Ă�
	//CObject3D::Draw();
}


//======================
//�|���S���̕`�揈��
//======================
void CParticles001::DrawNoml()
{

}


//========================
//���𐶐�
//========================
CParticles001* CParticles001::Create(D3DXVECTOR3 pos)
{
	CParticles001* pPraticles = new CParticles001(2); //���I�m��

	if (SUCCEEDED(pPraticles->Init()))
	{
		if (pPraticles != nullptr)
		{
			pPraticles->m_pos = pos;
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}