//===================================
//
//フェードの処理設定[bg.cpp]
//Author:chiba haruki
//
//===================================

//マクロ定義
#include "fade.h"
#include "rendererh.h"
#include "manager.h"

//int CFade::nCountCol = 255;

//======================
//コンストラクタ
//======================
//CFade::CFade()
//{
//	
//}


//==========================
//引数付きコンストラクタ
//==========================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	nCountCol = 255;
	m_Fade = FADE_IN;
	m_aFileName = "data\\TEXTURE\\black.jpg";
}


//======================
//コンストラクタ
//======================
CFade::~CFade()
{

}


//======================
//背景の初期化処理
//======================
HRESULT CFade::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK; //成功を返す
}

//======================
//背景の終了処理
//======================
void CFade::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//CObject2D::Uninit();
}


//=======================
//背景の更新処理
//=======================
void CFade::Update()
{
	if (m_Fade == FADE_IN)
	{
		if (nCountCol >= MAX_FADE_SPEED)
		{
			nCountCol-= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定

		//白色から徐々に移す
	/*	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);*/

		//黒色から徐々に移す
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}

	else if (m_Fade == FADE_OUT)
	{
		if (nCountCol <= 255)
		{
			nCountCol+= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定

		//白色から徐々に移す
		/*pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);*/

		//黒色から徐々に移す
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountCol);

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}
}


//=====================
//背景の描画処理
//=====================
void CFade::Draw()
{
	CObject2D::Draw();
}


//=====================
//背景の描画処理
//=====================
void CFade::DrawNoml()
{

}

void CFade::SetFade(FADE fade)
{
	m_Fade = fade;
}



int CFade::GetCountCol()
{
	return nCountCol;
}


//===================================
//オブジェクト生成
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
