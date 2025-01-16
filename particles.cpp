//==========================================
//
//パーティクルの処理[particles.cpp]
//Author:chiba haruki
//
//==========================================


//==========================================
//インクルード
#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//コンストラクタ
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	SetSizeX(10.0f);
	SetFileNamePass("data\\TEXTURE\\Circle003.png");
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
	SetRot(D3DXVECTOR3(1.5f, 0.0f, 0.0f));

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
	SetSize(GetSizeX(), 0.0f, GetSizeX());
	//SetCol(m_nRandom, 0, 0);

	GetLife()++;

	GetPos().y += 2.0f;

	if (GetLife() >= MAX_PARTICLES001_LIFE)
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
			pPraticles->SetPos(pos);
			pPraticles->CObject3D::Lood();
			return pPraticles;
		}
	}

	return nullptr;
}