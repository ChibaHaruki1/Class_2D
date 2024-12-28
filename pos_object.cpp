//=============================================
//
//�ʒu�Ɋւ��鏈��[pos_object.cpp]
//Auther:Haruki Chiba
//
//=============================================

#include "pos_object.h"
#include "rendererh.h"
#include "manager.h"


//======================================================================================================================
//                                                    start�}�[�J�[����
//======================================================================================================================


//========================
//�R���X�g���N�^
//========================
CStart::CStart(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\TEXTURE\\StartPos.x";
}


//========================
//�f�X�g���N�^
//========================
CStart::~CStart()
{

}


//========================
//����������
//========================
HRESULT CStart::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos().x = 300;

	return S_OK;
}


//========================
//�I������
//========================
void CStart::Uninit()
{
	CObjectX::Uninit();
}


//========================
//�X�V����
//========================
void CStart::Update()
{

}


//========================
//�`�揈��
//========================
void CStart::Draw()
{
	CObjectX::Draw();
}


//=========================
//�X�^�[�g�}�[�J�[�̐���
//=========================
CStart* CStart::Create()
{
	CStart* pStart = new CStart(2);

	if (SUCCEEDED(pStart->Init()))
	{
		if (pStart != nullptr)
		{
			pStart->Lood();
			pStart->Size();
			pStart->SetType(START);
			return pStart;
		}
	}

	return nullptr;
}