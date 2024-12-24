//===================================
//
//地面の設定をする処理[particles.cpp]
//Author:chiba haruki
//
//===================================

#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//コンストラクタ
//============================
CParticles::CParticles(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 10.0f;
	m_aFileName = "data\\TEXTURE\\UI\\008.png";
	PosX = 0.0f;

	m_nRandom = 0;
	m_nLife = 0;
}


//============================
//デストラクタ
//============================
CParticles::~CParticles()
{

}


//============================
//ポリゴンの初期化処理
//============================
HRESULT CParticles::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;

	return S_OK;
}

//==========================
//ポリゴンの終了処理
//==========================
void CParticles::Uninit()
{
	CObject3D::Uninit();
}

//========================
//ポリゴンの更新処理
//========================
void CParticles::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);
	//SetCol(m_nRandom, 0, 0);
	
	m_nLife++;

	if (m_nLife >= MAX_PARTICLES_LIFE)
	{
		CObject3D::Release(); //自身の解放
		return; //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();
}

//======================
//ポリゴンの描画処理
//======================
void CParticles::Draw()
{
	//CObject3D::DrawEffect(); //基底クラスの描画処理を呼ぶ
	CObject3D::Draw();
}


//======================
//ポリゴンの描画処理
//======================
void CParticles::DrawNoml()
{

}


//========================
//床を生成
//========================
CParticles* CParticles::Create(D3DXVECTOR3 pos)
{
	CParticles* pPraticles = new CParticles(2); //動的確保

	if (SUCCEEDED(pPraticles->Init()))
	{
		if (pPraticles != nullptr)
		{
			pPraticles->m_pos = pos;
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}


//
//
//


//============================
//コンストラクタ
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 10.0f;
	m_aFileName = "data\\TEXTURE\\Circle003.png";
	PosX = 0.0f;

	m_nRandom = 0;
	m_nLife = 0;
}


//============================
//デストラクタ
//============================
CParticles001::~CParticles001()
{

}


//============================
//ポリゴンの初期化処理
//============================
HRESULT CParticles001::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;

	return S_OK;
}


//==========================
//ポリゴンの終了処理
//==========================
void CParticles001::Uninit()
{
	CObject3D::Uninit();
}


//========================
//ポリゴンの更新処理
//========================
void CParticles001::Update()
{
	SetSize(m_fSizeX, 0.0f, m_fSizeX);
	//SetCol(m_nRandom, 0, 0);

	m_nLife++;

	m_pos.y += 2.0f;

	if (m_nLife >= MAX_PARTICLES001_LIFE)
	{
		CObject3D::Release(); //自身の解放
		return; //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();
}


//======================
//ポリゴンの描画処理
//======================
void CParticles001::Draw()
{
	CObject3D::DrawEffect(); //基底クラスの描画処理を呼ぶ
	//CObject3D::Draw();
}


//======================
//ポリゴンの描画処理
//======================
void CParticles001::DrawNoml()
{

}


//========================
//床を生成
//========================
CParticles001* CParticles001::Create(D3DXVECTOR3 pos)
{
	CParticles001* pPraticles = new CParticles001(2); //動的確保

	if (SUCCEEDED(pPraticles->Init()))
	{
		if (pPraticles != nullptr)
		{
			pPraticles->m_pos = pos;
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}