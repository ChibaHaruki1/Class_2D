//===================================
//
//�w�i�̏����ݒ�[bg.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//�C���N���[�h
#include "bg.h"
#include "rendererh.h"
#include "manager.h"
#include <time.h>


//==========================
//�����t���R���X�g���N�^
//==========================
CManagerBg::CManagerBg(int nPriority) : CObject2D(nPriority)
{
	nCountAlpha = 255;
}


//======================
//�R���X�g���N�^
//======================
CManagerBg::~CManagerBg()
{

}


//======================
//�w�i�̏���������
//======================
HRESULT CManagerBg::Init()
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
void CManagerBg::Uninit(void)
{
	CObject2D::Uninit();
}


//=======================
//�w�i�̍X�V����
//=======================
void CManagerBg::Update()
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}


//=====================
//�w�i�̕`�揈��
//=====================
void CManagerBg::Draw()
{
	CObject2D::Draw();
}


//===================================
//�I�u�W�F�N�g����
//===================================
CManagerBg* CManagerBg::Create(CScene::MODE mode)
{
	CManagerBg* pBg = nullptr; //���N���X�̃|�C���^�[

	//�^�C�g����
	if (mode == CScene::MODE::MODE_TITLE)
	{
		pBg = new CTitleBg(0);
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Title.png");
	}

	//���U���g��
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pBg = new CResultBg(3);
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\utyuu.png");
	}

	//���S��
	else if (mode == CScene::MODE::MODE_GAMEOVER)
	{
		pBg = new CGameOverBg(3);
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\SCREEN\\GameOver.jpg");
	}

	//��񂪂��鎞
	if (pBg != nullptr)
	{
		//������������������
		if (SUCCEEDED(pBg->Init()))
		{
			pBg->Lood(); //�e�N�X�`���̓ǂݍ��݊֐����Ă�
			return pBg;  //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//================================================================================================================================================
//�^�C�g���w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CTitleBg::CTitleBg(int nPriority) : CManagerBg(nPriority)
{
	//m_aFileName = "data\\TEXTURE\\utyuu.png";
}


//======================
//�R���X�g���N�^
//======================
CTitleBg::~CTitleBg()
{

}


//================================================================================================================================================
//���U���g�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CResultBg::CResultBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CResultBg::~CResultBg()
{

}

//================================================================================================================================================
//�Q�[���I�[�o�[�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CGameOverBg::CGameOverBg(int nPriority) : CManagerBg(nPriority)
{
	SetAlph(255);
}


//======================
//�R���X�g���N�^
//======================
CGameOverBg::~CGameOverBg()
{

}

//=================================
//�X�V����
//=================================
void CGameOverBg::Update()
{
	SetRandom(1 + rand() % 10); //�����𐶐�
	GetFrame()++;                //�t���[���𑝂₷

	//�t���[�����K�萔�ȏ�s������
	if (GetFrame() >= 50)
	{
		//��������ꐔ�ȏゾ������
		if (GetRandom() >= 1 && GetRandom() <= 3)
		{
			SetSIze(0.0f, SCREEN_WIDTH, 100.0f, SCREEN_HEIGHT + 100.0f); //�傫���̐ݒ�
			SetAlph(255);  //alpha�l�̏�����
			SetFrame(0);   //�t���[���̏�����
		}

		else if (GetRandom() >= 4 && GetRandom() <= 6)
		{
			SetSIze(0.0f, SCREEN_WIDTH, -100.0f, SCREEN_HEIGHT - 100.0f); //�傫���̐ݒ�
			SetAlph(255);  //alpha�l�̏�����
			SetFrame(0);   //�t���[���̏�����
		}

		else if (GetRandom() >= 7 && GetRandom() <= 8)
		{
			SetSIze(-200.0f, SCREEN_WIDTH - 200.0f, 0.0f, SCREEN_HEIGHT);
			SetAlph(155);  //alpha�l��������
			SetFrame(0);   //�t���[���̏�����
		}
		else
		{
			SetSIze(200.0f, SCREEN_WIDTH + 200.0f, 0.0f, SCREEN_HEIGHT);
			SetAlph(55);   //alpha�l��������
			SetFrame(0);   //�t���[���̏�����
		}
	}
	else if (GetFrame() >= 20)
	{
		SetSIze(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT); //�傫���̐ݒ�
	}
	SetCol(GetAlph(), GetAlph());                         //alpha�l��ݒ肷��
}


//===========================================================================================================================================================
//SHOP���̔w�i�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CShopScreen::CShopScreen(int nPriority) : CManagerBg(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Screen\\Yellow.png");
}


//=======================
//�f�X�g���N�^
//=======================
CShopScreen::~CShopScreen()
{

}


//=======================
//����������
//=======================
HRESULT CShopScreen::Init()
{
	//�������̗L���𔻒�
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT); //�傫����ݒ�
	SetCol(50, 50);                                              //alpha�l�̐ݒ�

	return S_OK; //������Ԃ�
}


//========================
//�X�V����
//========================
void CShopScreen::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}


//========================
//��������
//========================
CShopScreen* CShopScreen::Create()
{
	CShopScreen* pText = new CShopScreen(0);

	if (SUCCEEDED(pText->Init()))
	{
		if (pText != nullptr)
		{
			pText->Lood();
			return pText;
		}
	}
	return nullptr;
}
