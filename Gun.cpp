//==================================
//
//����̏���[block.cpp]
//Auther:Chiba Haruki
//
//==================================

#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "Gun.h"


//============================
//�R���X�g���N�^
//============================
CInitGun::CInitGun(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\XFILE\\Gun\\Gun000.x";
}


//============================
//�f�X�g���N�^
//============================
CInitGun::~CInitGun()
{

}


//============================
//����������
//============================
HRESULT CInitGun::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos() = D3DXVECTOR3(200.0f, 0.0f, 100.0f); //�ʒu��������(�ʒu�𒲐��ł���j

	return S_OK;
}

//==========================
//�I������
//==========================
void CInitGun::Uninit()
{
	CObjectX::Uninit();
}

//========================
//�X�V����
//========================
void CInitGun::Update()
{
	
}

//======================
//�`�揈��
//======================
void CInitGun::Draw()
{
	CObjectX::Draw();
}


//========================
//�����𐶐�
//========================
CInitGun* CInitGun::Create(D3DXVECTOR3 pos)
{
	CInitGun* pCBlockX = new CInitGun(1); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//��񂪂��鎞
		if (pCBlockX != nullptr)
		{
			pCBlockX->GetPos() = pos; //�ʒu�𓯊�������
			pCBlockX->CObjectX::Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
			pCBlockX->SetType(INITGUN);
			//pCBlockX->Size();
			return pCBlockX; //����Ԃ�
		}
	}
	return nullptr; //����Ԃ�
}


//============================
//�R���X�g���N�^
//============================
CInitGun001::CInitGun001(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\XFILE\\Gun\\Gun001.x";
}


//============================
//�f�X�g���N�^
//============================
CInitGun001::~CInitGun001()
{

}


//============================
//����������
//============================
HRESULT CInitGun001::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos() = D3DXVECTOR3(200.0f, 0.0f, 100.0f); //�ʒu��������(�ʒu�𒲐��ł���j

	return S_OK;
}

//==========================
//�I������
//==========================
void CInitGun001::Uninit()
{
	CObjectX::Uninit();
}

//========================
//�X�V����
//========================
void CInitGun001::Update()
{
	GetRot().y = CManager::GetScene()->GetPlayerX()->GetRot().y - 1.6f;

	//DKey�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x;
		GetMove().x = CManager::GetScene()->GetPlayerX()->GetMove().x;
		//m_rot.y = CManager::GetScene()->GetPlayerX()->GetRot().y;
	}

	//AKey�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x;
		GetMove().x = CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPosPrts(5).y + 50.0f;
	GetPos().z = CManager::GetScene()->GetPlayerX()->GetPos().z+10;

	/*if (m_rot.y <= 3.5f)
	{
		m_rot.y += 0.01f;
	}*/

	CObjectX::Update();
}

//======================
//�`�揈��
//======================
void CInitGun001::Draw()
{
	CObjectX::Draw();
}


//========================
//�����𐶐�
//========================
CInitGun001* CInitGun001::Create(D3DXVECTOR3 pos)
{
	CInitGun001* pCBlockX = new CInitGun001(1); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//��񂪂��鎞
		if (pCBlockX != nullptr)
		{
			pCBlockX->GetPos() = pos; //�ʒu�𓯊�������
			pCBlockX->CObjectX::Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
			pCBlockX->SetType(INITGUN);
			//pCBlockX->Size();
			return pCBlockX; //����Ԃ�
		}
	}
	return nullptr; //����Ԃ�
}

