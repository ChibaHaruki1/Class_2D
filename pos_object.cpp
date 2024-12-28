//=============================================
//
//位置に関する処理[pos_object.cpp]
//Auther:Haruki Chiba
//
//=============================================

#include "pos_object.h"
#include "rendererh.h"
#include "manager.h"


//======================================================================================================================
//                                                    startマーカー処理
//======================================================================================================================


//========================
//コンストラクタ
//========================
CStart::CStart(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = "data\\TEXTURE\\StartPos.x";
}


//========================
//デストラクタ
//========================
CStart::~CStart()
{

}


//========================
//初期化処理
//========================
HRESULT CStart::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	GetPos().x = 300;

	return S_OK;
}


//========================
//終了処理
//========================
void CStart::Uninit()
{
	CObjectX::Uninit();
}


//========================
//更新処理
//========================
void CStart::Update()
{

}


//========================
//描画処理
//========================
void CStart::Draw()
{
	CObjectX::Draw();
}


//=========================
//スタートマーカーの生成
//=========================
CStart* CStart::Create()
{
	CStart* pStart = new CStart(2);

	if (SUCCEEDED(pStart->Init()))
	{
		if (pStart != nullptr)
		{
			pStart->Lood();
			pStart->Size();
			pStart->SetType(START);
			return pStart;
		}
	}

	return nullptr;
}