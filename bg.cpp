//===================================
//
//背景の処理設定[bg.cpp]
//Author:chiba haruki
//
//===================================

//インクルード
#include "bg.h"
#include "rendererh.h"
#include "manager.h"
#include <time.h>

//グローバル変数宣言
int nCountCol = 255;

//==========================
//引数付きコンストラクタ
//==========================
CManagerBg::CManagerBg(int nPriority) : CObject2D(nPriority)
{
	m_aFileName = nullptr;
}


//======================
//コンストラクタ
//======================
CManagerBg::~CManagerBg()
{

}


//======================
//背景の初期化処理
//======================
HRESULT CManagerBg::Init()
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
void CManagerBg::Uninit(void)
{
	CObject2D::Uninit();
}


//=======================
//背景の更新処理
//=======================
void CManagerBg::Update()
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nCountCol);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//=====================
//背景の描画処理
//=====================
void CManagerBg::Draw()
{
	CObject2D::Draw();
}


//===================================
//オブジェクト生成
//===================================
CManagerBg* CManagerBg::Create(CScene::MODE mode)
{
	CManagerBg* pBg = nullptr; //基底クラスのポインター

	//タイトル時
	if (mode == CScene::MODE::MODE_TITLE)
	{
		pBg = new CTitleBg(0);
		pBg->m_aFileName = "data\\TEXTURE\\UI\\scene\\Title.png";
	}

	//リザルト時
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pBg = new CResultBg(3);
		pBg->m_aFileName = "data\\TEXTURE\\UI\\scene\\utyuu.png";
	}

	//死亡時
	else if (mode == CScene::MODE::MODE_GAMEOVER)
	{
		pBg = new CGameOverBg(3);
		pBg->m_aFileName = "data\\TEXTURE\\UI\\SCREEN\\GameOver.jpg";
	}

	//情報がある時
	if (pBg != nullptr)
	{
		//初期化が成功した時
		if (SUCCEEDED(pBg->Init()))
		{
			pBg->Lood(); //テクスチャの読み込み関数を呼ぶ
			return pBg;  //情報を返す
		}
	}

	return nullptr; //無を返す
}


//================================================================================================================================================
//タイトル背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CTitleBg::CTitleBg(int nPriority) : CManagerBg(nPriority)
{
	//m_aFileName = "data\\TEXTURE\\utyuu.png";
}


//======================
//コンストラクタ
//======================
CTitleBg::~CTitleBg()
{

}


//================================================================================================================================================
//リザルト背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CResultBg::CResultBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CResultBg::~CResultBg()
{

}

//================================================================================================================================================
//ゲームオーバー背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CGameOverBg::CGameOverBg(int nPriority) : CManagerBg(nPriority)
{
	m_fAlph = 255;
	m_nFrame = 0;
}


//======================
//コンストラクタ
//======================
CGameOverBg::~CGameOverBg()
{

}

//=================================
//更新処理
//=================================
void CGameOverBg::Update()
{
	m_nRandom = 1+rand() % 10; //乱数を生成
	m_nFrame++;                //フレームを増やす

	//フレームが規定数以上行った時
	if (m_nFrame >= 50)
	{
		//乱数が基底数以上だった時
		if (m_nRandom >= 1 && m_nRandom <= 3)
		{
			SetSIze(0.0f, SCREEN_WIDTH, 100.0f, SCREEN_HEIGHT + 100.0f); //大きさの設定
			m_fAlph = 255; //alpha値の初期化
			m_nFrame = 0;  //フレームの初期化
		}

		else if (m_nRandom >= 4 && m_nRandom <= 6)
		{
			SetSIze(0.0f, SCREEN_WIDTH, -100.0f, SCREEN_HEIGHT - 100.0f); //大きさの設定
			m_fAlph = 255; //alpha値の初期化
			m_nFrame = 0;  //フレームの初期化
		}

		else if (m_nRandom >= 7 && m_nRandom <= 8)
		{
			SetSIze(-200.0f, SCREEN_WIDTH - 200.0f, 0.0f, SCREEN_HEIGHT);
			m_fAlph = 155; //alpha値を下げる
			m_nFrame = 0;  //フレームの初期化
		}
		else
		{
			SetSIze(200.0f, SCREEN_WIDTH + 200.0f, 0.0f, SCREEN_HEIGHT);
			m_fAlph =  55; //alpha値を下げる
			m_nFrame = 0;  //フレームの初期化
		}
	}
	else if (m_nFrame >= 20)
	{
		SetSIze(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT); //大きさの設定
	}
	SetCol(m_fAlph, m_fAlph);                         //alpha値を設定する
}


//===========================================================================================================================================================
//SHOP時の背景の処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CShopScreen::CShopScreen(int nPriority) : CManagerBg(nPriority)
{
	m_aFileName = "data\\TEXTURE\\UI\\Screen\\Yellow.png";
}


//=======================
//デストラクタ
//=======================
CShopScreen::~CShopScreen()
{

}


//=======================
//初期化処理
//=======================
HRESULT CShopScreen::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT); //大きさを設定
	SetCol(50, 50);                                              //alpha値の設定

	return S_OK; //成功を返す
}


//========================
//更新処理
//========================
void CShopScreen::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}


//========================
//生成処理
//========================
CShopScreen* CShopScreen::Create()
{
	CShopScreen* pText = new CShopScreen(0);

	if (SUCCEEDED(pText->Init()))
	{
		if (pText != nullptr)
		{
			pText->Lood();
			return pText;
		}
	}
	return nullptr;
}
