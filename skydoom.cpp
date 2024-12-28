//==================================
//
//��Q���̏���[block.cpp]
//Auther:Chiba Haruki
//
//==================================

#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "skydoom.h"


//============================
//�R���X�g���N�^
//============================
CSkyDoom::CSkyDoom(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = nullptr;
}


//============================
//�f�X�g���N�^
//============================
CSkyDoom::~CSkyDoom()
{

}


//============================
//����������
//============================
HRESULT CSkyDoom::Init()
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
void CSkyDoom::Uninit()
{
	CObjectX::Uninit();
}

//========================
//�X�V����
//========================
void CSkyDoom::Update()
{
	////�����̍X�V�i�����Ă���悤�Ɍ�����j
	//m_rot.x += 0.0001f;
	//m_rot.z += 0.0001f;

	//DKey�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetRot().y += 0.0001f; //�����������Ɠ��������ɌX��
		GetMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	//AKey�������ꂽ��
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetRot().y -= 0.0001f; //�����������Ɠ��������ɌX��
		GetMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPos().y; //�v���C���[�̂����Ə�ɓ��������遁���������Ɏ��R�Ɍ������
	GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x; //�v���C���[�̂����Ə�ɓ��������遁���������Ɏ��R�Ɍ������

	CObjectX::Update();

}

//======================
//�`�揈��
//======================
void CSkyDoom::Draw()
{
	CObjectX::Draw();
}


//========================
//�����𐶐�
//========================
CSkyDoom* CSkyDoom::Create(D3DXVECTOR3 pos,int nNumber)
{
	CSkyDoom* pCBlockX = new CSkyDoom(1); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//��񂪂��鎞
		if (pCBlockX != nullptr)
		{
			if (nNumber == 0)
			{
				pCBlockX->m_aFileName = "data\\XFILE\\StageObj\\SkyDoom.x";  //�F��
			}
			else if(nNumber==1)
			{
				pCBlockX->m_aFileName = "data\\XFILE\\StageObj\\SkyDoom001.x";  //�܂��
			}
			pCBlockX->GetPos() = pos; //�ʒu�𓯊�������
			pCBlockX->CObjectX::Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
			return pCBlockX; //����Ԃ�
		}
	}
	return nullptr; //����Ԃ�
}
