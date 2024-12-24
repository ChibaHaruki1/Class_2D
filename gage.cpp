//===================================================================
//
//ゲージに関する処理[gage.cpp]
//Ajther:Haruki Chiba
//
//===================================================================

//===========================
//インクルード
#include "gage.h"
#include "manager.h"


//============================
//static変数の初期化

bool CFuelGage::m_bUse = false;

//=======================================================================================================================================================
//燃料ゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CFuelGage::CFuelGage(int nPriority) : CObject3D(nPriority)
{
	m_fSizeY = MAX_SIZEY;
	m_nAlpha = 0;
}

//===========================
//デストラクタ
//===========================
CFuelGage::~CFuelGage()
{
	m_bUse = false;
}

//===========================
//初期化処理
//===========================
HRESULT CFuelGage::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	CObject3D::SetSize(15.0f, m_fSizeY, 20.0f); //大きさを設定

	return S_OK;
}

//============================
//破棄処理
//============================
void CFuelGage::Uninit()
{
	CObject3D::Uninit();
}

//============================
//更新処理
//============================
void CFuelGage::Update()
{
	m_pos = D3DXVECTOR3(CManager::GetScene()->GetPlayerX()->GetPos().x - 50.0f,
		CManager::GetScene()->GetPlayerX()->GetPos().y + 80.0f,
		CManager::GetScene()->GetPlayerX()->GetPos().z);

	CObject3D::SetSizeY(15.0f, m_fSizeY, 20.0f); //大きさを設定
	CObject3D::SetCol(255, 255, 255, m_nAlpha);

	if (m_bUse == true)
	{
		if (m_nAlpha != 255)
		{
			m_nAlpha = 255;
		}

		if (m_fSizeY > 0)
		{
			m_fSizeY -= MAX_MAINAS_GAGESPEED;
		}
		else
		{
			m_fSizeY = 0.0f;
		}
	}
	else if (m_bUse == false)
	{
		if (m_nAlpha > 0)
		{
			m_nAlpha -= 5;
		}

		if (m_fSizeY < MAX_SIZEY)
		{
			m_fSizeY += MAX_MAINAS_GAGESPEED;
		}
	}

	//m_move = CManager::GetScene()->GetPlayerX()->GetMove();

	CObject3D::Update();
}


//============================
//描画処理
//============================
void CFuelGage::Draw()
{
	if (m_nAlpha > 5&& m_fSizeY>5)
	{
		CObject3D::Draw();
	}
}


//============================
//描画処理
//============================
void CFuelGage::DrawNoml()
{
	
}

//============================
//生成処理
//============================
CFuelGage* CFuelGage::Create()
{
	CFuelGage* pFuelGage = new CFuelGage();

	if (pFuelGage != nullptr)
	{
		if (SUCCEEDED(pFuelGage->Init()))
		{
			pFuelGage->m_aFileName= "data\\TEXTURE\\UI\\Gage\\RedGage000.png";
			pFuelGage->Lood();
			return pFuelGage;
		}
	}

	return nullptr;
}


//=======================================================================================================================================================
//ゲージmanager処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CManagerGage::CManagerGage(int nPriority) : CObject2D(nPriority)
{
	m_fHPSizeX = 400.0f;
	m_fBossHPSizeX = SCREEN_WIDTH;
	m_fSaveSizeX = 0.0f;
}

//===========================
//デストラクタ
//===========================
CManagerGage::~CManagerGage()
{

}

//===========================
//初期化処理
//===========================
HRESULT CManagerGage::Init()
{
	//初期化が成功するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
//背景の終了処理
//======================
void CManagerGage::Uninit(void)
{
	CObject2D::Uninit();
}


//=======================
//背景の更新処理
//=======================
void CManagerGage::Update()
{
	
}


//=====================
//背景の描画処理
//=====================
void CManagerGage::Draw()
{
	CObject2D::Draw();
}


//=====================
//背景の描画処理
//=====================
void CManagerGage::DrawNoml()
{

}


//===================================
//ゲージの生成
//===================================
CManagerGage* CManagerGage::Create(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr;

	//タイプがプレイヤーのHPの時
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGage(1);
		CreateLeave(type);
		CManager::GetInstance()->GetCreateObjectInstnace(FUELGAGE,0, pManagerGage->g_pos);
		pManagerGage->m_aFileName = "data\\TEXTURE\\UI\\Gage\\RedGage000.png";
	}

	//タイプがボスのHPの時
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGage(1);
		CreateLeave(type);
		pManagerGage->m_aFileName = "data\\TEXTURE\\UI\\Gage\\BossHpGage.png";
	}

	if (SUCCEEDED(pManagerGage->Init()))
	{
		pManagerGage->Lood();
		return pManagerGage;
	}

	return nullptr;
}

//===================================
//残すゲージの生成
//===================================
CManagerGage* CManagerGage::CreateLeave(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr;

	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGageLeave(0);
		pManagerGage->m_aFileName = "data\\TEXTURE\\UI\\Gage\\RedGage001.png";
	}
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGageLeave(0);
		pManagerGage->m_aFileName = "data\\TEXTURE\\UI\\Gage\\BloackGage000.png";
	}

	if (SUCCEEDED(pManagerGage->Init()))
	{
		pManagerGage->Lood();
		return pManagerGage;

	}

	return nullptr;
}


//=======================================================================================================================================================
//プレイヤーのゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CPlayerHPGage::CPlayerHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX();
}

//===========================
//デストラクタ
//===========================
CPlayerHPGage::~CPlayerHPGage()
{

}


//===========================
//初期化処理
//===========================
HRESULT CPlayerHPGage::Init()
{
	//初期化が成功するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	CObject2D::SetSIze(0.0f, GetPlayerHPSizeX(), 40.0f, 70.0f); //大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう

	return S_OK;
}

//===========================
//更新処理
//===========================
void CPlayerHPGage::Update()
{
	//現在のHPゲージより高い時
	if (m_fSaveSizeX > GetPlayerHPSizeX())
	{
		m_fSaveSizeX -= 0.64f * 2.0f;        //元々のHPゲージを減らす
	}

	else if (m_fSaveSizeX <= GetPlayerHPSizeX())
	{
		m_fSaveSizeX = GetPlayerHPSizeX();   //現在のHPゲージと同期させる
	}

	CObject2D::SetSIze(0.0f, m_fSaveSizeX, MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //滑らかに減っているように見せる
}


//=======================================================================================================================================================
//ボスのゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CBossHPGage::CBossHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //HPを同期させる
}

//===========================
//デストラクタ
//===========================
CBossHPGage::~CBossHPGage()
{

}


//===========================
//初期化処理
//===========================
HRESULT CBossHPGage::Init()
{
	//初期化が成功するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	//SetCol(100,100); //alpha値を設定
	CObject2D::SetSIze(0.0f, GetBossHPSizeX(), (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう
	return S_OK; //成功を返す
}


//===========================
//更新処理
//===========================
void CBossHPGage::Update()
{
	//現在のHPゲージより高い時
	if (m_fSaveSizeX > GetBossHPSizeX())
	{//減らされた分だけ減らす
		m_fSaveSizeX -= 0.64f * 2.0f;           //元々のHPゲージを減らす
	}
	else if (m_fSaveSizeX <= GetBossHPSizeX())
	{
		m_fSaveSizeX = GetBossHPSizeX(); //現在のHPゲージと同期させる
	}

	CObject2D::SetSIze(0.0f, m_fSaveSizeX, (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //滑らかに減っているように見せる
}


//=======================================================================================================================================================
//プレイヤーのHPゲージを残す処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CPlayerHPGageLeave::CPlayerHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX();
}

//===========================
//デストラクタ
//===========================
CPlayerHPGageLeave::~CPlayerHPGageLeave()
{

}


//===========================
//初期化処理
//===========================
HRESULT CPlayerHPGageLeave::Init()
{
	//初期化が成功するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	CObject2D::SetSIze(0.0f, GetPlayerHPSizeX(), MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう

	return S_OK;
}


//=======================================================================================================================================================
//ボスのHPゲージを残す処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CBossHPGageLeave::CBossHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //HPを同期させる
}

//===========================
//デストラクタ
//===========================
CBossHPGageLeave::~CBossHPGageLeave()
{

}


//===========================
//初期化処理
//===========================
HRESULT CBossHPGageLeave::Init()
{
	//初期化が成功するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	//SetCol(100, 100); //alpha値を設定
	CObject2D::SetSIze(0.0f, GetBossHPSizeX(), (SCREEN_HEIGHT - 40.0f), SCREEN_HEIGHT); //大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう

	return S_OK;
}