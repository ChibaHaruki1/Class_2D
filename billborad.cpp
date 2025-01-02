//========================================
//
//�r���{�[�h����[billboard.cpp]
//Auther:Haruki Chiba
//
//========================================

//�C���N���[�h
#include "billboard.h"
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"

//�}�N����`
#define MAX_BILLBOARD_SIZE_X (40.0f)
#define MAX_BILLBOARD_SIZE_Y (40.0f)

//=========================
//�R���X�g���N�^
//=========================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{
	
}


//=========================
//�f�X�g���N�^
//=========================
CBillboard::~CBillboard()
{

}


//=========================
//����������
//=========================
HRESULT CBillboard::Init()
{
	//���_�o�b�t�@�����Ɏ��s�����Ƃ�
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(40.0f, MAX_BILLBOARD_SIZE_Y, 0.0f);

	return S_OK;
}


//=========================
//�I������
//=========================
void CBillboard::Uninit()
{
	CObject3D::Uninit();
}


//=========================
//�X�V����
//=========================
void CBillboard::Update()
{
	
}


//=========================
//�`�揈��
//=========================
void CBillboard::Draw()
{
   CObject3D::Draw();
}

//=========================
//�r���{�[�h�̐���
//=========================
CBillboard* CBillboard::Create()
{
	CBillboard* pBillboard = new CBillboard(3);

	if (SUCCEEDED(pBillboard->Init()))
	{
		if (pBillboard != nullptr)
		{
			pBillboard->Lood();
			return pBillboard;
		}
	}

	return nullptr;
}