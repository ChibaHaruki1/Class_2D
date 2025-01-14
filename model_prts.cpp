//======================================
//
//�p�[�c���̏���
//Auther: Haruki Chiba
//
//======================================


//======================================
//�C���N���[�h
#include "model_prts.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CModelPrts::CModelPrts()
{
	m_nIndexPrts = 0;
	m_nIndexModelPrts = 0;
	m_bCreateGun = true;
	m_nNumMat = 0;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_pParentlPrts = nullptr;
	for (int nCount = 0; nCount < MAX_MODEL_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = {};
	}
}


//=======================
//�f�X�g���N�^
//=======================
CModelPrts::~CModelPrts()
{

}


//======================
//����������
//======================
HRESULT CModelPrts::Init()
{
	return S_OK;

}


//========================
//�j������
//========================
void CModelPrts::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	m_nNumMat = 0;

	for (int nCntMat = 0; nCntMat < MAX_MODEL_TEXTURE; nCntMat++)
	{
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = nullptr;
		}
	}

	//if (this != nullptr)
	//{
	//	delete this;
	//	//this = nullptr;
	//}
}


//========================
//�X�V����
//========================
void CModelPrts::Update()
{

}


//========================
//�`�揈��
//========================
void CModelPrts::Draw(D3DXMATRIX MtxWolrd)
{
	if (m_bCreateGun == true)
	{
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

		D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent; //�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ��p
		D3DXMATERIAL* pMat;

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

		if (m_pParentlPrts != nullptr)
		{
			mtxParent = m_pParentlPrts->GetWorldMtx();
		}
		else
		{
			mtxParent = MtxWolrd;

		}

		//�}�g���b�N�X�ɑ��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A��������
		pDevice->GetMaterial(&matDef);

		//material�|�C���^�[�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCount = 0; nCount < (int)m_nNumMat; nCount++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCount].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCount]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCount);

		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}


//
//
//
void CModelPrts::Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL* pMat)
{
	//CRenderer* pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	//HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);


	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);

	m_pMesh = pMesh;
	m_pBuffMat = pBufferMat;
	m_nNumMat = dw_NumMat;

	//�}�e���A���f�[�^�ւ̃|�C���^������
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nNumTexture = 0;

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C�������݂���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++;
		}
	}
}


//=========================
//����
//=========================
CModelPrts* CModelPrts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat)
{
	CModelPrts* pModelPrts = new CModelPrts();

	if (pModelPrts != nullptr)
	{
		pModelPrts->Init();
		pModelPrts->m_pos = pos;
		pModelPrts->m_rot = rot;
		pModelPrts->Lood(m_aPrtsPass,pMesh,pBufferMat,dw_NumMat,pMat);
		pModelPrts->Size();
	}
	return pModelPrts;
}


//==================
//�T�C�Y�̎擾
//==================
void CModelPrts::Size()
{
	int nNumVertex; //���_���̊i�[
	DWORD dSIze; //���_�̃t�H�[�}�b�g�T�C�Y�擾����ۊǂ���
	BYTE* pVtxByte; //���_�t�H�[�}�b�g�̎擾

	//���_�����擾
	nNumVertex = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_���b�V���̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//�ʒu�������邽�߂̕ϐ�
		D3DXVECTOR3 mtx;

		mtx = *(D3DXVECTOR3*)pVtxByte;

		if (mtx.x > m_max.x)
		{
			m_max.x = mtx.x;
		}
		else if (mtx.x < m_min.x)
		{
			m_min.x = mtx.x;
		}

		if (mtx.y > m_max.y)
		{
			m_max.y = mtx.y;
		}
		else if (mtx.y < m_min.y)
		{
			m_min.y = mtx.y;
		}

		if (mtx.z > m_max.z)
		{
			m_max.z = mtx.z;
		}
		else if (mtx.z < m_min.z)
		{
			m_min.z = mtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxByte += dSIze;
	}

	if (m_min.y < 0)
	{
		if (m_max.y < m_min.y)
		{
			m_max.y = m_min.y * -1.0f;
		}
		m_min.y = 0;
	}

	//�I�u�W�F�N�g�̃T�C�Y���v�Z����
	m_ModelSize = m_max - m_min;
}


//
//
//
void CModelPrts::BindSize(D3DXVECTOR3& max, D3DXVECTOR3& min, D3DXVECTOR3& ModelSize)
{
	max = m_max;
	min = m_min;
	ModelSize = m_ModelSize;
}


//
//
//
void CModelPrts::SetParent(CModelPrts* pParent)
{
	m_pParentlPrts = pParent;
}