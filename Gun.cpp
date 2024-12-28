//==================================
//
//武器の処理[block.cpp]
//Auther:Chiba Haruki
//
//==================================

#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "Gun.h"


//============================
//コンストラクタ
//============================
CInitGun::CInitGun(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\XFILE\\Gun\\Gun000.x";
}


//============================
//デストラクタ
//============================
CInitGun::~CInitGun()
{

}


//============================
//初期化処理
//============================
HRESULT CInitGun::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos() = D3DXVECTOR3(200.0f, 0.0f, 100.0f); //位置を初期化(位置を調整できる）

	return S_OK;
}

//==========================
//終了処理
//==========================
void CInitGun::Uninit()
{
	CObjectX::Uninit();
}

//========================
//更新処理
//========================
void CInitGun::Update()
{
	
}

//======================
//描画処理
//======================
void CInitGun::Draw()
{
	CObjectX::Draw();
}


//========================
//建物を生成
//========================
CInitGun* CInitGun::Create(D3DXVECTOR3 pos)
{
	CInitGun* pCBlockX = new CInitGun(1); //動的確保

	//初期化に成功
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//情報がある時
		if (pCBlockX != nullptr)
		{
			pCBlockX->GetPos() = pos; //位置を同期させる
			pCBlockX->CObjectX::Lood(); //Xファイルを読み込む関数を呼ぶ
			pCBlockX->SetType(INITGUN);
			//pCBlockX->Size();
			return pCBlockX; //情報を返す
		}
	}
	return nullptr; //無を返す
}


//============================
//コンストラクタ
//============================
CInitGun001::CInitGun001(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\XFILE\\Gun\\Gun001.x";
}


//============================
//デストラクタ
//============================
CInitGun001::~CInitGun001()
{

}


//============================
//初期化処理
//============================
HRESULT CInitGun001::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos() = D3DXVECTOR3(200.0f, 0.0f, 100.0f); //位置を初期化(位置を調整できる）

	return S_OK;
}

//==========================
//終了処理
//==========================
void CInitGun001::Uninit()
{
	CObjectX::Uninit();
}

//========================
//更新処理
//========================
void CInitGun001::Update()
{
	GetRot().y = CManager::GetScene()->GetPlayerX()->GetRot().y - 1.6f;

	//DKeyが押された時
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x;
		GetMove().x = CManager::GetScene()->GetPlayerX()->GetMove().x;
		//m_rot.y = CManager::GetScene()->GetPlayerX()->GetRot().y;
	}

	//AKeyが押された時
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x;
		GetMove().x = CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPosPrts(5).y + 50.0f;
	GetPos().z = CManager::GetScene()->GetPlayerX()->GetPos().z+10;

	/*if (m_rot.y <= 3.5f)
	{
		m_rot.y += 0.01f;
	}*/

	CObjectX::Update();
}

//======================
//描画処理
//======================
void CInitGun001::Draw()
{
	CObjectX::Draw();
}


//========================
//建物を生成
//========================
CInitGun001* CInitGun001::Create(D3DXVECTOR3 pos)
{
	CInitGun001* pCBlockX = new CInitGun001(1); //動的確保

	//初期化に成功
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//情報がある時
		if (pCBlockX != nullptr)
		{
			pCBlockX->GetPos() = pos; //位置を同期させる
			pCBlockX->CObjectX::Lood(); //Xファイルを読み込む関数を呼ぶ
			pCBlockX->SetType(INITGUN);
			//pCBlockX->Size();
			return pCBlockX; //情報を返す
		}
	}
	return nullptr; //無を返す
}

