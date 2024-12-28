//==================================================================
//
//ステージに配置するオブジェクトの処理の処理[statge_obj.cpp]
//Auther:Chiba Haruki
//
//==================================================================

//===========================
//インクルード
#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "stage_obj.h"
#include <string>

std::string u8TelephonPoleText = u8"電柱の情報設定"; //日本語対応
std::string u8TelephonPoleNumberText = u8"番目の"; //日本語対応

//===========================
//static変数の初期化
int CStageObj::m_nTelephonPoleCount = 0;

//============================
//コンストラクタ
//============================
CStageObj::CStageObj(int nPriority) : CObjectX(nPriority)
{
	m_aFileName = nullptr;
	m_pFile = nullptr;
}


//============================
//デストラクタ
//============================
CStageObj::~CStageObj()
{

}


//============================
//初期化処理
//============================
HRESULT CStageObj::Init()
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
void CStageObj::Uninit()
{
	if (m_pFile != nullptr)
	{
		m_pFile = nullptr;
	}
	CObjectX::Uninit();
}

//========================
//更新処理
//========================
void CStageObj::Update()
{
	CObjectX::Update();
}

//======================================
//テキストファイルに書き込む処理
//======================================
void CStageObj::TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ)
{
	m_pFile = fopen("data\\TEXT\\OBJECT\\TelephonPole.txt", "a"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}

	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		m_nTelephonPoleCount++;
		fprintf(m_pFile, "%s", "\n\n"); //数字を書き込む
		fprintf(m_pFile, "%s", "#=====================================\n"); //数字を書き込む
		fprintf(m_pFile, "%s", "#"); //数字を書き込む
		fprintf(m_pFile, "%d", m_nTelephonPoleCount); //数字を書き込む
		fprintf(m_pFile, "%s", u8TelephonPoleNumberText.data()); //数字を書き込む
		fprintf(m_pFile, "%s", u8TelephonPoleText.data()); //文字を書き込む(全角文字)
		fprintf(m_pFile, "%s", "\n"); //改行を行う
		fprintf(m_pFile, "%s", "#=====================================\n"); //数字を書き込む
		fprintf(m_pFile, "%s", "TELEPHONPOLESET\n"); //数字を書き込む
		fprintf(m_pFile, "%s", "		POS = "); //「POS」の文字を書き込む
		fprintf(m_pFile, "%.1f ", m_fPosX); //「位置」の文字を書き込む(少数点第１まで)
		fprintf(m_pFile, "%.1f ", m_fPosY); //「位置」の文字を書き込む(少数点第１まで)
		fprintf(m_pFile, "%.1f ", m_fPosZ); //「位置」の文字を書き込む(少数点第１まで)
		fprintf(m_pFile, "%s", "\n"); //改行を行う
		fprintf(m_pFile, "%s", "END_TELEPHONPOLESET\n"); //文字を書き込む
		//fprintf(m_pFile, "%s", "END_SCRIPT\n"); //文字を書き込む
		fclose(m_pFile); //ファイルを閉じる
	}
}

//======================
//描画処理
//======================
void CStageObj::Draw()
{
	CObjectX::Draw();
}

//========================
//建物を生成
//========================
CStageObj* CStageObj::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CStageObj* pStageObj = nullptr; //基底クラスのポインター初期化

	//タイプが電柱の時
	if (type == CObjectX::TELEPHONPOLE)
	{
		pStageObj = new CTelephonPole(3);
		//情報がある時
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\telephone_pole.x";
			pStageObj->SetType(TELEPHONPOLE);
		}
	}

	//タイプが監視カメラの上部分の時
	else if (type == CObjectX::SURVEILLANCECAMERAUP)
	{
		pStageObj = new CSurveillanceCameraUP(3);
		//情報がある時
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\surveillance_cameraUP.x";
		}
	}

	//タイプが監視カメラの下部分の時
	else if (type == CObjectX::SURVEILLANCECAMERADOWN)
	{
		pStageObj = new CSurveillanceCameraDown(3);
		//情報がある時
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\surveillance_cameraDown.x";
		}
	}

	//タイプが監視カメラの下部分の時
	else if (type == CObjectX::SHOP)
	{
		pStageObj = new CShop(3);
		//情報がある時
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\Shop.x";
		}
	}

	//タイプが壊れた家の時
	else if (type == CObjectX::BREAKHOUSE)
	{
		pStageObj = new CBreakHouse(3);
		//情報がある時
		if (pStageObj != nullptr)
		{
			pStageObj->m_aFileName = "data\\XFILE\\StageObj\\BreakHouse000.x";
		}
	}

	if (pStageObj != nullptr)
	{
		//初期化に成功
		if (SUCCEEDED(pStageObj->Init()))
		{
			pStageObj->GetPos() = pos; //位置を同期させる
			pStageObj->CObjectX::Lood(); //Xファイルを読み込む関数を呼ぶ
			pStageObj->Size();
			pStageObj->SetType(SHOP);
			return pStageObj; //情報を返す
		}
	}

	return nullptr; //無を返す
}


//==========================================================================================================================
//電柱の処理
//==========================================================================================================================

//============================
//コンストラクタ
//============================
CTelephonPole::CTelephonPole(int nPriority) : CStageObj(nPriority)
{

}

//============================
//デストラクタ
//============================
CTelephonPole::~CTelephonPole()
{

}


//==========================================================================================================================
//監視カメラの上部分の処理
//==========================================================================================================================

//============================
//コンストラクタ
//============================
CSurveillanceCameraUP::CSurveillanceCameraUP(int nPriority) : CStageObj(nPriority)
{
	
}

//============================
//デストラクタ
//============================
CSurveillanceCameraUP::~CSurveillanceCameraUP()
{

}

//============================
//初期化処理
//============================
HRESULT CSurveillanceCameraUP::Init()
{
	//頂点バッファ生成
	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================
//終了処理
//==========================
void CSurveillanceCameraUP::Uninit()
{
	CStageObj::Uninit();
}

//========================
//更新処理
//========================
void CSurveillanceCameraUP::Update()
{
	CStageObj::Update();


}

//======================
//描画処理
//======================
void CSurveillanceCameraUP::Draw()
{
	CStageObj::Draw();
}


//==========================================================================================================================
//監視カメラの下部分の処理
//==========================================================================================================================

//============================
//コンストラクタ
//============================
CSurveillanceCameraDown::CSurveillanceCameraDown(int nPriority) : CStageObj(nPriority)
{

}

//============================
//デストラクタ
//============================
CSurveillanceCameraDown::~CSurveillanceCameraDown()
{

}

//==========================================================================================================================
//店の処理
//==========================================================================================================================

//============================
//コンストラクタ
//============================
CShop::CShop(int nPriority) : CStageObj(nPriority)
{

}

//============================
//デストラクタ
//============================
CShop::~CShop()
{

}


//==========================================================================================================================
//壊れた家の処理
//==========================================================================================================================

//============================
//コンストラクタ
//============================
CBreakHouse::CBreakHouse(int nPriority) : CStageObj(nPriority)
{

}

//============================
//デストラクタ
//============================
CBreakHouse::~CBreakHouse()
{

}

//============================
//更新処理
//============================
void CBreakHouse::Update()
{
	//一回だけ処理を通す
	if (m_bOneFlag == false)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::FIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //炎エフェクトを呼ぶ
		CManager::GetInstance()->GetFire()->GetLife() = 60 * 3;                                               //ライフを設定
		CManager::GetInstance()->GetFire()->GetAlpha() = 150;                                                 //ライフを設定
		CManager::GetInstance()->GetFire()->SetSize(920.0f, 700.0f, 0.0f);                                    //大きさを設定
		CManager::GetInstance()->GetFire()->SetEffect(D3DXVECTOR3(GetPos().x+200.0f, GetPos().y+600.0f, GetPos().z));    //炎エフェクトを呼ぶ
		m_bOneFlag = true; //二度と通らなくする
	}

	//エフェクトのライフが既定の数値まで行った時
	if (CManager::GetInstance()->GetFire()->GetLife() <= 10)
	{
		m_bOneFlag = false; //また通るように設定する
	}
}