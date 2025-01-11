//================================
//
//�J��������[camera.cpp]
//Auther:Haruki Chiba
//
//================================

//�C���N���[�h
#include "camera.h"
#include "object.h"
#include "rendererh.h"
#include "manager.h"
#include "player.x.h"

//�}�N����`
#define MAX_ROTSPEED (0.01f) //�J�����̉�]�̑����𒲐�����
#define MAX_CAMERASPEED (1.0f) //�J�����̈ړ��̑����𒲐�

//========================
//�R���X�g���N�^
//========================
CCamera::CCamera()
{
	m_fDistance = 300;
	CountCamera = 10.0f;
	pInputKeyBoard1 = nullptr;

	m_fAdjustmentPosZ = 1000;
}


//========================
//�f�X�g���N�^
//========================
CCamera::~CCamera()
{

}


//========================
//����������
//========================
HRESULT CCamera::Init()
{
	pInputKeyBoard1 = CManager::GetKeyBorad(); //�L�[�{�[�h�̏����l������

	/*switch (CManager::GetScene()->GetMode())
	{
	case CScene::MODE_GAME01:
		m_fAdjustmentPosZ = 600;
		break;
	case CScene::MODE_GAME02:
		m_fAdjustmentPosZ = 1000;
		break;
	}*/

	m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f); //���_�𒲐�
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);////�����_�����f���ɐݒ�
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSavePosV = m_posV;

	return S_OK;
}


//========================
//�I������
//========================
void CCamera::Uninit()
{

}


//========================
//�X�V����
//========================
void CCamera::Update()
{
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Y) == true)
	{//���_�����i�������j�ɂȂ�
		m_posV.y += MAX_CAMERASPEED;
		CountCamera += MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_N) == true)
	{//���_����i�傫���j�Ȃ�
		m_posV.y -= MAX_CAMERASPEED;
		CountCamera -= MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Z) == true)
	{//���_�����ɓ���
		rot.y += MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fDistance;
		m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fDistance;

	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_C) == true)
	{//���_���E�ɓ���
		rot.y -= MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fDistance;
		m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fDistance;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_T) == true)
	{//�����_�����i�������j�ɂȂ�
		m_posR.y += MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_B) == true)
	{//�����_����i�傫���j�Ȃ�
		m_posR.y -= MAX_CAMERASPEED;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_Q) == true)
	{//�����_�����Ɍ���
		rot.y -= MAX_ROTSPEED;
		m_posR.x = m_posV.x + sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(rot.y) * m_fDistance;
	}
	if (pInputKeyBoard1->GetKeyboardPress(DIK_E) == true)
	{//�����_���E�Ɍ���
		rot.y += MAX_ROTSPEED;
		m_posR.x = m_posV.x + sinf(rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(rot.y) * m_fDistance;
	}

	if (pInputKeyBoard1->GetKeyboardPress(DIK_V) == true)
	{
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�J�������v���C���[�ɂ�����
	m_posR.x = CManager::GetScene()->GetPlayerX()->GetPos().x;
	m_posR.y = CManager::GetScene()->GetPlayerX()->GetPos().y;
	m_posR.z = CManager::GetScene()->GetPlayerX()->GetPos().z;

	m_posV.x = CManager::GetScene()->GetPlayerX()->GetPos().x;
	m_posV.y = CManager::GetScene()->GetPlayerX()->GetPos().y + m_fSavePosV.y + CountCamera;
	m_posV.z = CManager::GetScene()->GetPlayerX()->GetPos().z;

	//�J�������̂��v���C���[�ɍ��킹�ē���(���ڃ��f���̒l��������ƃJ������]�������I�ɐ��ʂɖ߂���邽�߁j
	m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) * m_fAdjustmentPosZ;
	m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) * m_fAdjustmentPosZ;
}


//========================
//�J�����̐ݒ�i�`��j
//========================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice= pRenderer->GetDevice(); //�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)CMain::SCREEN_WIDTH / (float)CMain::SCREEN_HEIGHT, 10.0f, 4000.0f);

	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)CMain::SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 10.0f, 2000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}