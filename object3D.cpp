//=========================================
//
//3D�I�u�W�F�N�g�̏���[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================

#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����������������
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nAlpha = 255;
	m_nFrame = 0;
	m_nRandom = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_aFileName = nullptr;
	//g_pBuffMatGun = {};
}


//=====================
//�f�X�g���N�^
//=====================
CObject3D::~CObject3D()
{

}


//=====================
//����������
//=====================
HRESULT CObject3D::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	//������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================================
//�r���{�[�h���̏������ݒ�
//=====================================
HRESULT CObject3D::BillboardInit()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	//������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}


//==================
//�I������
//==================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}


//==================
//�X�V����
//==================
void CObject3D::Update()
{
	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V�i����������j
	m_pos.x += (0.0f - m_move.x) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_pos.y += (0.0f - m_move.y) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_pos.z += (0.0f - m_move.z) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
}


//==================
//�T�C�Y�̐ݒ�
//==================
void CObject3D::SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X*0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X*0.5f, -SIZE_Y, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================
//�T�C�Y�̐ݒ�
//==================
void CObject3D::SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(0.0f, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, -SIZE_Y, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================
//�T�C�Y�̐ݒ�
//==================
void CObject3D::SetSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, 0.0f, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X - SIZE_X * 0.5f, 0.0f, SIZE_Z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===================================================
//�F�̐ݒ菈��
//===================================================
void CObject3D::SetCol(int Red, int Green, int Blue,int& Alpha)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//===================================================
//�e�N�X�`���̑傫����ݒ肳����
//===================================================
void CObject3D::SetTexture(float SizeX, float Size1X)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV���W�ɒ��Ӂi����P�D�O���j
	pVtx[1].tex = D3DXVECTOR2(SizeX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Size1X, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//================================
//�e�p�[�c���̓����蔻�菈���i�I���j
//================================
bool CObject3D::CollisionPrtsPlayer(float X, float Y, float Z)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < CObjectX::MAX_PRTS - 1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)*1.2f) == true)
		{
			return true; //����
		}
	}
	return false; //���s
}

//================================
//�e�p�[�c���̓����蔻�菈��
//================================
bool CObject3D::CollisionPrts1Left(float X, float Y, float Z)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < CCharacter::NUM_RIGHTPRTS; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 2), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 2)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 10), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 10)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}

	//����
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(0), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0)) == true)
	{
		return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}
	return false;
}

//================================
//�e�p�[�c���̓����蔻�菈��
//================================
bool CObject3D::CollisionPrts1Right(float X, float Y, float Z)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < CCharacter::NUM_RIGHTPRTS; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 2), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 2)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount + 10), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount + 10)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}

	//����
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(0), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0)) == true)
	{
		return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}
	return false;
}


//==================
//�`�揈��
//==================
void CObject3D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===========================
//�r���{�[�h�`�揈��
//===========================
void CObject3D::DrawNoml()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾�擾�p;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//===========================
//�G�t�F�N�g���̕`�揈��
//===========================
void CObject3D::DrawEffect()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X


	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾�擾�p;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//a�u�����f�B�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================
//�G�t�F�N�g���̕`�揈��
//===========================
void CObject3D::DrawEffect1()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ɐݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//a�u�����f�B�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=====================
//�ʒu�̐ݒ菈��
//=====================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//===================================
//�e�N�X�`���t�@�C���̓ǂݍ���
//===================================
HRESULT CObject3D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL;
	}
	return S_OK;
}