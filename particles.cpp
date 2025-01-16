//==========================================
//
//�p�[�e�B�N���̏���[particles.cpp]
//Author:chiba haruki
//
//==========================================


//==========================================
//�C���N���[�h
#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//�R���X�g���N�^
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	SetSizeX(10.0f);
	SetFileNamePass("data\\TEXTURE\\Circle003.png");
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
	SetRot(D3DXVECTOR3(1.5f, 0.0f, 0.0f));

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
	SetSize(GetSizeX(), 0.0f, GetSizeX());
	//SetCol(m_nRandom, 0, 0);

	GetLife()++;

	GetPos().y += 2.0f;

	if (GetLife() >= MAX_PARTICLES001_LIFE)
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
			pPraticles->SetPos(pos);
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}