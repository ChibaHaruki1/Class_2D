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

//int CFade::nCountAlpha = 255;

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
	nCountAlpha = 255;
	m_Fade = FADE::FADE_IN;
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
	if (m_Fade == FADE::FADE_IN)
	{
		if (nCountAlpha >= MAX_FADE_SPEED)
		{
			nCountAlpha-= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�

		//���F���珙�X�Ɉڂ�
	/*	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);*/

		//���F���珙�X�Ɉڂ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}

	else if (m_Fade == FADE::FADE_OUT)
	{
		if (nCountAlpha <= 255)
		{
			nCountAlpha+= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�

		//���F���珙�X�Ɉڂ�
		/*pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);*/

		//���F���珙�X�Ɉڂ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);

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

void CFade::SetFade(FADE fade)
{
	m_Fade = fade;
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
