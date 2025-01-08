//===================================
//
//２ｄのＵＩの処理設定[2d_ui.cpp]
//Author:chiba haruki
//
//===================================

//インクルード
#include "2d_ui.h"
#include "rendererh.h"
#include "manager.h"


//==========================
//引数付きコンストラクタ
//==========================
CNowCreateUI::CNowCreateUI(int nPriority) : CObject2D(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CNowCreateUI::~CNowCreateUI()
{

}


//======================
//背景の初期化処理
//======================
HRESULT CNowCreateUI::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f,100.0f, 0.0f,100.0f);

	return S_OK; //成功を返す
}


//======================
//背景の終了処理
//======================
void CNowCreateUI::Uninit()
{
	CObject2D::Uninit();
}


//=======================
//背景の更新処理
//=======================
void CNowCreateUI::Update()
{
	
}


//=====================
//背景の描画処理
//=====================
void CNowCreateUI::Draw()
{
	CObject2D::Draw();
}


//===========================================================================================================================================================
//メニューUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CShopMenu::CShopMenu(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\Menyu001.png");
}


//=======================
//デストラクタ
//=======================
CShopMenu::~CShopMenu()
{

}


//=======================
//初期化処理
//=======================
HRESULT CShopMenu::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f, 600.0f, 0.0f, 700.0f);

	return S_OK; //成功を返す
}


//========================
//破棄処理
//========================
void CShopMenu::Uninit()
{
	CObject2D::Uninit();
}


//========================
//更新処理
//========================
void CShopMenu::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//描画処理
//========================
void CShopMenu::Draw()
{
	CObject2D::Draw();
}


//========================
//生成処理
//========================
CShopMenu* CShopMenu::Create()
{
	CShopMenu* pText = new CShopMenu(0);

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


//===========================================================================================================================================================
//メニューUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CBuyText::CBuyText(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\buy001.png");
}


//=======================
//デストラクタ
//=======================
CBuyText::~CBuyText()
{

}


//=======================
//初期化処理
//=======================
HRESULT CBuyText::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f, 600.0f, 0.0f, SCREEN_HEIGHT);
	SetCol(200, 200);

	return S_OK; //成功を返す
}


//========================
//破棄処理
//========================
void CBuyText::Uninit()
{
	CObject2D::Uninit();
}


//========================
//更新処理
//========================
void CBuyText::Update()
{
	//CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//描画処理
//========================
void CBuyText::Draw()
{
	CObject2D::Draw();
}


//========================
//生成処理
//========================
CBuyText* CBuyText::Create()
{
	CBuyText* pText = new CBuyText(0);

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


//===========================================================================================================================================================
//選択時のUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CSelectGage::CSelectGage(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage.png");
	m_fSizeX = 0.0f;
	m_fSize1X = 600.0f;
	m_fSizeY = 50.0f;
	m_fSize1Y = 150.0f;
}


//=======================
//デストラクタ
//=======================
CSelectGage::~CSelectGage()
{

}


//=======================
//初期化処理
//=======================
HRESULT CSelectGage::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f, m_fSizeX, 0.0f,m_fSizeY);
	SetCol(100, 100);

	return S_OK; //成功を返す
}


//========================
//破棄処理
//========================
void CSelectGage::Uninit()
{
	CObject2D::Uninit();
}


//========================
//更新処理
//========================
void CSelectGage::Update()
{
	CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y);
}

//========================
//描画処理
//========================
void CSelectGage::Draw()
{
	CObject2D::Draw();
}


//========================
//生成処理
//========================
CSelectGage* CSelectGage::Create()
{
	CSelectGage* pSelectGage = new CSelectGage(3);

	if (SUCCEEDED(pSelectGage->Init()))
	{
		if (pSelectGage != nullptr)
		{
			pSelectGage->Lood();
			return pSelectGage;
		}
	}

	return nullptr;
}


//===========================================================================================================================================================
//選択時のUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CSelectGage001::CSelectGage001(int nPriority) : CSelectGage(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage001.png");

}


//=======================
//デストラクタ
//=======================
CSelectGage001::~CSelectGage001()
{

}


//=======================
//初期化処理
//=======================
HRESULT CSelectGage001::Init()
{
	//初期化の有無を判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(0.0f, GetSizeX(), 0.0f, GetSizeY());
	//SetCol(100, 100);
	//SetCol(100.0f,100.0f);

	return S_OK; //成功を返す
}


//========================
//破棄処理
//========================
void CSelectGage001::Uninit()
{
	CObject2D::Uninit();
}


//========================
//更新処理
//========================
void CSelectGage001::Update()
{
	//CObject2D::SetSIze(GetSizeX(), GetSize1X(), GetSizeY(), GetSize1Y());
}

//========================
//描画処理
//========================
void CSelectGage001::Draw()
{
	CObject2D::Draw();
}


//========================
//生成処理
//========================
CSelectGage001* CSelectGage001::Create()
{
	CSelectGage001* pSelectGage = new CSelectGage001(3);

	if (SUCCEEDED(pSelectGage->Init()))
	{
		if (pSelectGage != nullptr)
		{
			pSelectGage->Lood();
			return pSelectGage;
		}
	}

	return nullptr;
}