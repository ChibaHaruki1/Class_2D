//=========================================================
//
//���I�̔j�ЃI�u�W�F�N�g�̏���[direction_obj.cpp]
//Auther:Haruki Chiba
//
//=========================================================

//============================
//�C���N���[�h
#include "main.h"
#include "direction_obj.h"
#include "manager.h"

//============================
//static�ϐ��̏�����
int CDebrisX::m_nDirectionCount = 0;

//============================
//�R���X�g���N�^
//============================
CDebrisX::CDebrisX(int nPriority) : CObjectX(nPriority)
{
	SetFileName("data\\XFILE\\DirectionObj\\Debris.x");
	m_nLife = 0;
}


//============================
//�f�X�g���N�^
//============================
CDebrisX::~CDebrisX()
{

}


//============================
//����������
//============================
HRESULT CDebrisX::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}


//==========================
//�I������
//==========================
void CDebrisX::Uninit()
{
	CObjectX::Uninit();
}


//========================
//�X�V����
//========================
void CDebrisX::Update()
{
	m_nLife++;

	if (m_nLife >= 30)
	{
		m_nLife = 0;
  		CObjectX::Release();
		//CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::DEBRIS, m_nDirectionCount);
		return;
	}

	CObjectX::Update();
}


//======================
//�`�揈��
//======================
void CDebrisX::Draw()
{
	CObjectX::Draw();
}


//=====================
//����
//=====================
CDebrisX* CDebrisX::Create(D3DXVECTOR3 pos)
{
	CDebrisX* m_pDebris3D = new CDebrisX();

	//�������ɐ���
	if (SUCCEEDED(m_pDebris3D->Init()))
	{
		//��񂪂��鎞
		if (m_pDebris3D != nullptr)
		{
			m_pDebris3D->GetPos() = pos; //�ʒu�𓯊�������
			m_pDebris3D->Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
			m_pDebris3D->SetType(DEBRIS);
			return m_pDebris3D; //����Ԃ�
		}
	}
	
	return nullptr;
}