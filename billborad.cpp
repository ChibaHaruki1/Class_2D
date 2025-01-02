//========================================
//
//ビルボード処理[billboard.cpp]
//Auther:Haruki Chiba
//
//========================================

//インクルード
#include "billboard.h"
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"

//マクロ定義
#define MAX_BILLBOARD_SIZE_X (40.0f)
#define MAX_BILLBOARD_SIZE_Y (40.0f)

//=========================
//コンストラクタ
//=========================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{
	
}


//=========================
//デストラクタ
//=========================
CBillboard::~CBillboard()
{

}


//=========================
//初期化処理
//=========================
HRESULT CBillboard::Init()
{
	//頂点バッファ生成に失敗したとき
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(40.0f, MAX_BILLBOARD_SIZE_Y, 0.0f);

	return S_OK;
}


//=========================
//終了処理
//=========================
void CBillboard::Uninit()
{
	CObject3D::Uninit();
}


//=========================
//更新処理
//=========================
void CBillboard::Update()
{
	
}


//=========================
//描画処理
//=========================
void CBillboard::Draw()
{
   CObject3D::Draw();
}

//=========================
//ビルボードの生成
//=========================
CBillboard* CBillboard::Create()
{
	CBillboard* pBillboard = new CBillboard(3);

	if (SUCCEEDED(pBillboard->Init()))
	{
		if (pBillboard != nullptr)
		{
			pBillboard->Lood();
			return pBillboard;
		}
	}

	return nullptr;
}