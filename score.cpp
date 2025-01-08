//===================================
//
//スコアの処理[score.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//インクルード
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
//======================
CManagerScore::CManagerScore(int nPriority) : CObject2D(nPriority)
{
	m_nSocre = 0;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
}

//======================
//デストラクタ
//======================
CManagerScore::~CManagerScore()
{

}

//======================
//スコアの初期化処理
//======================
HRESULT CManagerScore::Init()
{
	//初期化の判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
		pVtx[1].tex = D3DXVECTOR2(0.11f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.11f, 1.0f);

		pVtx += 4; //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	GetBuffer()->Unlock();

	//スコアの配置処理
	PosScore();

	return S_OK;
}

//======================
//スコアの終了処理
//======================
void CManagerScore::Uninit()
{
	CObject2D::Uninit();
}

//=======================
//スコアの更新処理
//=======================
void CManagerScore::Update()
{

}

//=====================
//スコアの描画処理
//=====================
void CManagerScore::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //プロセスクラスのインスタンス生成
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Draw();

	for (int nCutMPNumber = 0; nCutMPNumber < MAX_SCORE; nCutMPNumber++)
	{
		if (m_aScore[nCutMPNumber].bUse == true)
		{//スコアが「使用されている」

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutMPNumber * 4, 2);
		}
	}
}

//=======================
//スコアの位置処理
//=======================
void CManagerScore::SetScorepos(D3DXVECTOR3 pos)
{
	int nCutScore;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	for (nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		if (m_aScore[nCutScore].bUse == false)
		{//スコアが使用されていない
			m_aScore[nCutScore].pos = pos;
			m_aScore[nCutScore].bUse = true; //使用している状態へ
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	GetBuffer()->Unlock();
}

//=======================
//スコアの設定処理
//=======================
void CManagerScore::SetScore(int nScore)
{
	int g_aPosTexU[10];
	VERTEX_2D* pVtx;
	int nScare;
	int nDight = 1;//桁管理用
	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	m_nSocre = nScore;

	//伊藤君のを参考にしました
	for (nScare = 0; nScare < MAX_SCORE; nScare++)
	{
		nDight *= 10;
		g_aPosTexU[10 - nScare - 1] = (nScore % nDight * 10) / nDight;
	}

	//テクスチャの設定
	for (nScare = 0; nScare < MAX_SCORE; nScare++)
	{
		pVtx[0].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)) + (1.0f / 10.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aPosTexU[nScare] * (1.0f / 10.0f)) + (1.0f / 10.0f), 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	GetBuffer()->Unlock();
}

//==============================
//スコアを減算する処理
//==============================
void CManagerScore::AddScore(int nValue)
{
	if (CManager::GetObjectSet() != nullptr)
	{
		CManager::GetObjectSet()->GetClearScore() += nValue; //スコアの加算
	}
	SetScore(m_nSocre + nValue);                         //テクスチャのスコアを加算
}

//==============================
//スコアを減算する処理
//==============================
void CManagerScore::InitAddScore(int nValue)
{
	SetScore(m_nSocre + nValue);                         //テクスチャのスコアを加算
}

//=====================
//スコアの位置
//=====================
void CManagerScore::PosScore()
{
	//スコア表示(位置の設定）
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		SetScorepos(D3DXVECTOR3(m_fPosX, 40.0f, 0.0f));
		m_fPosX = m_fPosX + 40.0f;
	}
}

//================
//スコア作成
//================
CManagerScore* CManagerScore::Create(CScene::MODE mode, int Number)
{
	CManagerScore* pScore = nullptr;

	if (mode == CScene::MODE_GAME01)
	{
		pScore = new CResultScore(3);                                     //継承クラスで動的確保
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number001.png");  //テクスチャのパス設定
		pScore->m_fPosX = 900;                                            //スコアの位置を調整
	}

	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pScore = new CResultScore(3);                                     //継承クラスで動的確
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number002.png");  //テクスチャのパス設
		pScore->m_fPosX = 40;											  //スコアの位置を調整
	}

	//初期化が成功した時
	if (SUCCEEDED(pScore->Init()))
	{
		if (pScore != nullptr)
		{
			pScore->Lood();
			pScore->InitAddScore(Number);
			return pScore;
		}
	}

	return nullptr;
}


//=======================================================================================================================
//ゲーム中のスコア処理
//=======================================================================================================================

//======================
//コンストラクタ
//======================
CGameScore::CGameScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//デストラクタ
//======================
CGameScore::~CGameScore()
{

}


//=======================================================================================================================
//リザルトのスコア処理
//=======================================================================================================================

//======================
//コンストラクタ
//======================
CResultScore::CResultScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//デストラクタ
//======================
CResultScore::~CResultScore()
{

}