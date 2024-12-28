//==================================
//
//障害物の処理[block.cpp]
//Auther:Chiba Haruki
//
//==================================

#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "skydoom.h"


//============================
//コンストラクタ
//============================
CSkyDoom::CSkyDoom(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = nullptr;
}


//============================
//デストラクタ
//============================
CSkyDoom::~CSkyDoom()
{

}


//============================
//初期化処理
//============================
HRESULT CSkyDoom::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//終了処理
//==========================
void CSkyDoom::Uninit()
{
	CObjectX::Uninit();
}

//========================
//更新処理
//========================
void CSkyDoom::Update()
{
	////向きの更新（動いているように見せる）
	//m_rot.x += 0.0001f;
	//m_rot.z += 0.0001f;

	//DKeyが押された時
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetRot().y += 0.0001f; //動いた方向と同じ向きに傾く
		GetMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	//AKeyが押された時
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetRot().y -= 0.0001f; //動いた方向と同じ向きに傾く
		GetMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPos().y; //プレイヤーのｙ軸と常に同期させる＝落ちた時に自然に見せれる
	GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x; //プレイヤーのｙ軸と常に同期させる＝落ちた時に自然に見せれる

	CObjectX::Update();

}

//======================
//描画処理
//======================
void CSkyDoom::Draw()
{
	CObjectX::Draw();
}


//========================
//建物を生成
//========================
CSkyDoom* CSkyDoom::Create(D3DXVECTOR3 pos,int nNumber)
{
	CSkyDoom* pCBlockX = new CSkyDoom(1); //動的確保

	//初期化に成功
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//情報がある時
		if (pCBlockX != nullptr)
		{
			if (nNumber == 0)
			{
				pCBlockX->m_aFileName = "data\\XFILE\\StageObj\\SkyDoom.x";  //宇宙
			}
			else if(nNumber==1)
			{
				pCBlockX->m_aFileName = "data\\XFILE\\StageObj\\SkyDoom001.x";  //曇り空
			}
			pCBlockX->GetPos() = pos; //位置を同期させる
			pCBlockX->CObjectX::Lood(); //Xファイルを読み込む関数を呼ぶ
			return pCBlockX; //情報を返す
		}
	}
	return nullptr; //無を返す
}
