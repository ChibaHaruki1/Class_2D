//=================================
//
//UIをつける処理[ui.cpp]
//Auther;HARUKI CHIBA
//
//=================================


//=================================
//インクルード
#include "ui.h"
#include "manager.h"


//============================
//コンストラクタ
//============================
CUI::CUI(int nPriority) : CObject3D(nPriority)
{
	
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
	//初期化が成功した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	
	return S_OK;       //成功を返す
}


//============================
//破棄処理
//============================
void CUI::Uninit()
{
	CObject3D::Uninit(); //破棄処理
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
	CObject3D::Draw(); //描画処理
}


//============================
//生成処理
//============================
CUI* CUI::Create(CObject3D::TYPE_UI typeui)
{
	CUI* pUI = nullptr; //基底クラスのポインター

	//タイプがくっつくの時
	if (typeui == CObject3D::TYPE_UI::CLING)
	{
		pUI = new CCreateInObject(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\effect000.jpg"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                   //テクスチャの読み込み
			return pUI;                                               //情報を返す
		}
	}

	//タイプが話すテキストの時
	else if (typeui == CObject3D::TYPE_UI::TALKTEXTR)
	{
		pUI = new CTalkText(0); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Text\\Talk.png"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                    //テクスチャの読み込み
			return pUI;                                                //情報を返す
		}
	}

	//タイプがレーザーの時
	else if (typeui == CObject3D::TYPE_UI::LASER)
	{
		pUI = new CLaserCamare(); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Laser000.png"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                  //テクスチャの読み込み
			return pUI;                                              //情報を返す
		}
	}

	return nullptr; //無を返す
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
	//初期化に成功した時
	if (FAILED(CUI::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	
	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ); //大きさの設定

	return S_OK;       //成功を返す
}


//============================
//描画処理
//============================
void CTalkText::Draw()
{
	CUI::Draw(); //描画処理
}


//=============================================================================================================================
//カメラから出るレーザーの処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CLaserCamare::CLaserCamare(int nPriority) : CUI(nPriority)
{

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
	//初期化に失敗した時
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ);               //大きさを設定
	SetRot(D3DXVECTOR3(0.0f, ADDJUST_ROTY, ADDJUST_ROTZ)); //向きを設定

	//位置を監視カメラの上部部分に設定する
	SetPos(D3DXVECTOR3(CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x, 
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y - ADDJUST_POSY,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z - ADDJUST_POSZ));

	return S_OK;       //成功を返す
}


//============================
//更新処理
//============================
void CLaserCamare::Update()
{
	//当たり判定
	if (CObject3D::CollisionPrtsPlayer(SIZEY, SIZEX, SIZEZ) == true)
	{
		SetRandom(1+ rand() % 2); //乱数の生成(範囲指定）

		//乱数が１の時
		if (GetRandom() == 1)
		{
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY, 0, D3DXVECTOR3(GetPos().x + ADDJUST_CREATE_POSZ, GetPos().y, 0.0f)); //敵の生成
			CObject3D::Release(); //自身の削除
			return;               //処理を抜ける
		}
	}

	////カメラの上部分の情報がなくなった時
	//if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) == nullptr)
	//{
	//	CObject3D::Release();
	//	return;
	//}
}


//============================
//描画処理
//============================
void CLaserCamare::Draw()
{
	CObject3D::DrawBillboard(); //描画処理
}