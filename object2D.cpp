//=========================================
//
//２Ｄオブジェクトの処理[object.cpp]
//Auther:Chiba Haruki
//
//=========================================

#include "main.h"
#include "object2D.h"
#include "rendererh.h"
#include "manager.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "collision.h"
#include "score.h"

//LPDIRECT3DTEXTURE9 m_pTexture = nullptr; //テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr; //頂点バッファのポインタ
 
//=====================
//コンストラクタ
//=====================
//CObject2D::CObject2D()
//{
//	m_pTexture = nullptr;
//	m_pVtxBuff = nullptr;
//	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）
//	g_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
//	g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する
//	g_fAngle = 0;
//	g_fLength = 0;
//	m_nLife = 0;
//	m_bUse = false;
//	//pInputKeyBoard = nullptr;
//}


//=============================
//引数付きコンストラクタ
//=============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する
	m_nRandom = 0;
	m_nFrame = 0;
	m_bUse = false;
	m_aFileName = nullptr;
	m_nAlph = 0;
}


//=====================
//デストラクタ
//=====================
CObject2D::~CObject2D()
{

}


//=====================
//初期化処理
//=====================
HRESULT CObject2D:: Init()
{
	CRenderer *pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	//頂点座標の設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================
//終了処理（破棄）
//=====================
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}


//=====================
//更新処理
//=====================
void CObject2D::Update ()
{
	
}

//=====================
//描画処理
//=====================
void CObject2D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //プロセスクラスのインスタンス生成
	LPDIRECT3DDEVICE9 pDevice = nullptr; //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//==================
//サイズの設定
//==================
void CObject2D::SetSIze(float SIZE_X, float SIZE1_X, float SIZE_Y, float SIZE1_Y)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SIZE1_X, SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SIZE_X, SIZE1_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SIZE1_X, SIZE1_Y, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================
//サイズの設定
//==================
void CObject2D::SetCol(int Alph, int Alph1)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, Alph);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, Alph);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, Alph1);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, Alph1);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===============================
//テクスチャの読み込み処理
//===============================
HRESULT CObject2D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=========================
//テクスチャ生成
//=========================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}
