//===================================
//
//�X�R�A�̏���[score.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//�C���N���[�h
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CManagerScore::CManagerScore(int nPriority) : CObject2D(nPriority)
{
	m_nSocre = 0;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
}

//======================
//�f�X�g���N�^
//======================
CManagerScore::~CManagerScore()
{

}

//======================
//�X�R�A�̏���������
//======================
HRESULT CManagerScore::Init()
{
	//�������̔���
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^	

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
		pVtx[1].tex = D3DXVECTOR2(0.11f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.11f, 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();

	//�X�R�A�̔z�u����
	PosScore();

	return S_OK;
}

//======================
//�X�R�A�̏I������
//======================
void CManagerScore::Uninit()
{
	CObject2D::Uninit();
}

//=======================
//�X�R�A�̍X�V����
//=======================
void CManagerScore::Update()
{

}

//=====================
//�X�R�A�̕`�揈��
//=====================
void CManagerScore::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //�v���Z�X�N���X�̃C���X�^���X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();

	for (int nCutMPNumber = 0; nCutMPNumber < MAX_SCORE; nCutMPNumber++)
	{
		if (m_aScore[nCutMPNumber].bUse == true)
		{//�X�R�A���u�g�p����Ă���v

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutMPNumber * 4, 2);
		}
	}
}

//=======================
//�X�R�A�̈ʒu����
//=======================
void CManagerScore::SetScorepos(D3DXVECTOR3 pos)
{
	int nCutScore;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		if (m_aScore[nCutScore].bUse == false)
		{//�X�R�A���g�p����Ă��Ȃ�
			m_aScore[nCutScore].pos = pos;
			m_aScore[nCutScore].bUse = true; //�g�p���Ă����Ԃ�
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}

//=======================
//�X�R�A�̐ݒ菈��
//=======================
void CManagerScore::SetScore(int nScore)
{
	int g_aPosTexU[10];
	VERTEX_2D* pVtx;
	int nScare;
	int nDight = 1;//���Ǘ��p
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	m_nSocre = nScore;

	//�ɓ��N�̂��Q�l�ɂ��܂���
	for (nScare = 0; nScare < MAX_SCORE; nScare++)
	{
		nDight *= 10;
		g_aPosTexU[10 - nScare - 1] = (nScore % nDight * 10) / nDight;
	}

	//�e�N�X�`���̐ݒ�
	for (nScare = 0; nScare < MAX_SCORE; nScare++)
	{
		pVtx[0].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)) + (1.0f / 10.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)) + (1.0f / 10.0f), 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}

//==============================
//�X�R�A�����Z���鏈��
//==============================
void CManagerScore::AddScore(int nValue)
{
	if (CManager::GetObjectSet() != nullptr)
	{
		CManager::GetObjectSet()->GetClearScore() += nValue; //�X�R�A�̉��Z
	}
	SetScore(m_nSocre + nValue);                         //�e�N�X�`���̃X�R�A�����Z
}

//==============================
//�X�R�A�����Z���鏈��
//==============================
void CManagerScore::InitAddScore(int nValue)
{
	SetScore(m_nSocre + nValue);                         //�e�N�X�`���̃X�R�A�����Z
}

//=====================
//�X�R�A�̈ʒu
//=====================
void CManagerScore::PosScore()
{
	//�X�R�A�\��(�ʒu�̐ݒ�j
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		SetScorepos(D3DXVECTOR3(m_fPosX, 40.0f, 0.0f));
		m_fPosX = m_fPosX + 40.0f;
	}
}

//================
//�X�R�A�쐬
//================
CManagerScore* CManagerScore::Create(CScene::MODE mode, int Number)
{
	CManagerScore* pScore = nullptr;

	if (mode == CScene::MODE_GAME01)
	{
		pScore = new CResultScore(3);                                     //�p���N���X�œ��I�m��
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number001.png");  //�e�N�X�`���̃p�X�ݒ�
		pScore->m_fPosX = 900;                                            //�X�R�A�̈ʒu�𒲐�
	}

	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pScore = new CResultScore(3);                                     //�p���N���X�œ��I�m
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number002.png");  //�e�N�X�`���̃p�X��
		pScore->m_fPosX = 40;											  //�X�R�A�̈ʒu�𒲐�
	}

	//������������������
	if (SUCCEEDED(pScore->Init()))
	{
		if (pScore != nullptr)
		{
			pScore->Lood();
			pScore->InitAddScore(Number);
			return pScore;
		}
	}

	return nullptr;
}


//=======================================================================================================================
//�Q�[�����̃X�R�A����
//=======================================================================================================================

//======================
//�R���X�g���N�^
//======================
CGameScore::CGameScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//�f�X�g���N�^
//======================
CGameScore::~CGameScore()
{

}


//=======================================================================================================================
//���U���g�̃X�R�A����
//=======================================================================================================================

//======================
//�R���X�g���N�^
//======================
CResultScore::CResultScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//�f�X�g���N�^
//======================
CResultScore::~CResultScore()
{

}