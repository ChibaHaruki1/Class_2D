//=======================================================
//
//UIをつける処理[ui.cpp]
//Auther;HARUKI CHIBA
//
//=======================================================

#include "ui.h"
#include "manager.h"
#include "create_enemy.h"


//============================
//コンストラクタ
//============================
CUI::CUI(int nPriority) : CObject3D(nPriority)
{
	m_fSizeX = 200.0f;
	m_bDraw = false;
}


//============================
//デストラク
//============================
CUI::~CUI()
{

}


//============================
//初期化処理
//============================
HRESULT CUI::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}


//============================
//破棄処理
//============================
void CUI::Uninit()
{
	CObject3D::Uninit();
}


//============================
//更新処理
//============================
void CUI::Update()
{

}


//============================
//描画処理
//============================
void CUI::Draw()
{
	CObject3D::Draw();
}


//============================
//描画処理
//============================
void CUI::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//============================
//生成処理
//============================
CUI* CUI::Create(CObject3D::TYPE_UI typeui)
{
	CUI* pUI = nullptr;

	if (typeui == CObject3D::TYPE_UI::INUI)
	{
		pUI = new CCreateInObject();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\effect000.jpg";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::TELEPHONPOLEUI)
	{
		pUI = new CCreateInObject();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\箱.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::TALKTEXTR)
	{
		pUI = new CTalkText();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\Text\\Talk.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}

	else if (typeui == CObject3D::TYPE_UI::LASER)
	{
		pUI = new CLaserCamare();
		if (SUCCEEDED(pUI->Init()))
		{
			if (pUI != nullptr)
			{
				pUI->m_aFileName = "data\\TEXTURE\\UI\\Laser000.png";
				pUI->CObject3D::Lood();
				return pUI;
			}
		}
	}
	return nullptr;
}


//=============================================================================================================================
//現在textに書き出せるオブジェクトの場所にUIをつける処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CCreateInObject::CCreateInObject(int nPriority) : CUI(nPriority)
{
	
}


//============================
//デストラク
//============================
CCreateInObject::~CCreateInObject()
{

}


//============================
//初期化処理
//============================
HRESULT CCreateInObject::Init()
{
	//頂点バッファ生成
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}


//============================
//破棄処理
//============================
void CCreateInObject::Uninit()
{
	CUI::Uninit();
}


//============================
//更新処理
//============================
void CCreateInObject::Update()
{

}


//============================
//描画処理
//============================
void CCreateInObject::Draw()
{
	CUI::Draw();
}


//============================
//描画処理
//============================
void CCreateInObject::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//=============================================================================================================================
//現在textに書き出せるオブジェクトの場所にUIをつける処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CTalkText::CTalkText(int nPriority) : CUI(nPriority)
{

}


//============================
//デストラク
//============================
CTalkText::~CTalkText()
{

}


//============================
//初期化処理
//============================
HRESULT CTalkText::Init()
{
	//頂点バッファ生成
	if (FAILED(CUI::Init()))
	{
		return E_FAIL;
	}

	m_rot.x = 1.5f;
	CObject3D::SetSize(40.0f, 0.0f, 40.0f);

	return S_OK;
}


//============================
//破棄処理
//============================
void CTalkText::Uninit()
{
	CUI::Uninit();
}


//============================
//更新処理
//============================
void CTalkText::Update()
{
	
}


//============================
//描画処理
//============================
void CTalkText::Draw()
{
	if (GetDraw() == true)
	{
		CUI::Draw();
	}
}


//============================
//描画処理
//============================
void CTalkText::DrawNoml()
{
	//CObject3D::DrawNoml();
}


//=============================================================================================================================
//カメラから出るレーザーの処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CLaserCamare::CLaserCamare(int nPriority) : CUI(nPriority)
{
	m_nRandom = 0;
}


//============================
//デストラク
//============================
CLaserCamare::~CLaserCamare()
{

}


//============================
//初期化処理
//============================
HRESULT CLaserCamare::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}

	CObject3D::SetSize(80.0f, 20.0f, 20.0f); //大きさを設定
	m_rot = D3DXVECTOR3(0.0f, 0.54f, 1.54f); //向きを設定

	//位置を監視カメラの上部部分に設定する
	m_pos = D3DXVECTOR3(CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y - 20.0f,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z - 35.0f);

	return S_OK;
}


//============================
//破棄処理
//============================
void CLaserCamare::Uninit()
{
	CUI::Uninit();
}


//============================
//更新処理
//============================
void CLaserCamare::Update()
{
	if (CObject3D::CollisionPrtsPlayer(20.0f,80.0f,20.0f) == true)
	{
		m_nRandom = -400 + rand() % 800;
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMY,0, D3DXVECTOR3((float)-200, 0.0f, -50.0f));
		CObject3D::Release();
		return;
	}

	//カメラの上部分の情報がなくなった時
	if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) == nullptr)
	{
		CObject3D::Release();
		return;
	}
}


//============================
//描画処理
//============================
void CLaserCamare::Draw()
{
	//CUI::DrawNoml();
}


//============================
//描画処理
//============================
void CLaserCamare::DrawNoml()
{
	CObject3D::DrawNoml();
}