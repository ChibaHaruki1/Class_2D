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

//int CFade::nCountAlpha = 255;

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
	nCountAlpha = 255;
	m_Fade = FADE::FADE_IN;
	SetFileNamePass("data\\TEXTURE\\black.jpg");
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
	//頂点バッファの破棄
	if (GetBuffer() != nullptr)
	{
		GetBuffer()->Release();
		GetBuffer() = nullptr;
	}

	//CObject2D::Uninit();
}


//=======================
//背景の更新処理
//=======================
void CFade::Update()
{
	if (m_Fade == FADE::FADE_IN)
	{
		if (nCountAlpha >= MAX_FADE_SPEED)
		{
			nCountAlpha-= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定

		//白色から徐々に移す
	/*	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);*/

		//黒色から徐々に移す
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);

		//頂点バッファをアンロック
		GetBuffer()->Unlock();
	}

	else if (m_Fade == FADE::FADE_OUT)
	{
		if (nCountAlpha <= 255)
		{
			nCountAlpha+= MAX_FADE_SPEED;
		}

		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定

		//白色から徐々に移す
		/*pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountAlpha);*/

		//黒色から徐々に移す
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, nCountAlpha);

		//頂点バッファをアンロック
		GetBuffer()->Unlock();
	}
}


//=====================
//背景の描画処理
//=====================
void CFade::Draw()
{
	CObject2D::Draw();
}

void CFade::SetFade(FADE fade)
{
	m_Fade = fade;
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
