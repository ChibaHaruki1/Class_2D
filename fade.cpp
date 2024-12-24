//===================================
//
//�t�F�[�h�̏����ݒ�[bg.cpp]
//Author:chiba haruki
//
//===================================

//�}�N����`
#include "fade.h"
#include "rendererh.h"
#include "manager.h"

//int CFade::nCountCol = 255;

//======================
//�R���X�g���N�^
//======================
//CFade::CFade()
//{
//	
//}


//==========================
//�����t���R���X�g���N�^
//==========================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	nCountCol = 255;
	m_Fade = FADE_IN;
	m_aFileName = "data\\TEXTURE\\black.jpg";
}


//======================
//�R���X�g���N�^
//======================
CFade::~CFade()
{

}


//======================
//�w�i�̏���������
//======================
HRESULT CFade::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK; //������Ԃ�
}

//======================
//�w�i�̏I������
//======================
void CFade::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//CObject2D::Uninit();
}


//=======================
//�w�i�̍X�V����
//=======================
void CFade::Update()
{
	if (m_Fade == FADE_IN)
	{
		if (nCountCol >= MAX_FADE_SPEED)
		{
			nCountCol-= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�

		//���F���珙�X�Ɉڂ�
	/*	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);*/

		//���F���珙�X�Ɉڂ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}

	else if (m_Fade == FADE_OUT)
	{
		if (nCountCol <= 255)
		{
			nCountCol+= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�

		//���F���珙�X�Ɉڂ�
		/*pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);*/

		//���F���珙�X�Ɉڂ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}


//=====================
//�w�i�̕`�揈��
//=====================
void CFade::Draw()
{
	CObject2D::Draw();
}


//=====================
//�w�i�̕`�揈��
//=====================
void CFade::DrawNoml()
{

}

void CFade::SetFade(FADE fade)
{
	m_Fade = fade;
}



int CFade::GetCountCol()
{
	return nCountCol;
}


//===================================
//�I�u�W�F�N�g����
//===================================
CFade* CFade::Create()
{
	CFade* pFade = new CFade(0);
	if (SUCCEEDED(pFade->Init()))
	{
		if (pFade != nullptr)
		{
			pFade->Lood();
			return pFade;
		}
	}

	return nullptr;
}
