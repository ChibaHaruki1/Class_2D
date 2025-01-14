//======================================
//
//パーツ毎の処理
//Auther: Haruki Chiba
//
//======================================


//======================================
//インクルード
#include "model_prts.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
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
//デストラクタ
//=======================
CModelPrts::~CModelPrts()
{

}


//======================
//初期化処理
//======================
HRESULT CModelPrts::Init()
{
	return S_OK;

}


//========================
//破棄処理
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
//更新処理
//========================
void CModelPrts::Update()
{

}


//========================
//描画処理
//========================
void CModelPrts::Draw(D3DXMATRIX MtxWolrd)
{
	if (m_bCreateGun == true)
	{
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

		D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent; //計算用マトリックス
		D3DMATERIAL9 matDef; //現在のマテリアルの保存用
		D3DXMATERIAL* pMat;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//-----向きを反映-----
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//-----位置を反映-----
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		if (m_pParentlPrts != nullptr)
		{
			mtxParent = m_pParentlPrts->GetWorldMtx();
		}
		else
		{
			mtxParent = MtxWolrd;

		}

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを収得
		pDevice->GetMaterial(&matDef);

		//materialポインターの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCount = 0; nCount < (int)m_nNumMat; nCount++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCount].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCount]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCount);

		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}


//
//
//
void CModelPrts::Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL* pMat)
{
	//CRenderer* pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	//HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);


	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);

	m_pMesh = pMesh;
	m_pBuffMat = pBufferMat;
	m_nNumMat = dw_NumMat;

	//マテリアルデータへのポインタを収得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nNumTexture = 0;

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//テクスチャファイルが存在する
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++;
		}
	}
}


//=========================
//生成
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
//サイズの取得
//==================
void CModelPrts::Size()
{
	int nNumVertex; //頂点数の格納
	DWORD dSIze; //頂点のフォーマットサイズ取得情報を保管する
	BYTE* pVtxByte; //頂点フォーマットの取得

	//頂点数を取得
	nNumVertex = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズ取得
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点メッシュのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//位置を代入するための変数
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

		//頂点フォーマットのサイズ分ポインタを進める
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

	//オブジェクトのサイズを計算する
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