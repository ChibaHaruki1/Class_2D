//=========================================================
//
//瓦礫の破片オブジェクトの処理[direction_obj.cpp]
//Auther:Haruki Chiba
//
//=========================================================

//============================
//インクルード
#include "main.h"
#include "direction_obj.h"
#include "manager.h"

//============================
//static変数の初期化


//============================
//コンストラクタ
//============================
CDebrisX::CDebrisX(int nPriority) : CObjectX(nPriority)
{
	SetFileName("data\\XFILE\\DirectionObj\\Debris.x");
}


//============================
//デストラクタ
//============================
CDebrisX::~CDebrisX()
{

}


//============================
//初期化処理
//============================
HRESULT CDebrisX::Init()
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
void CDebrisX::Uninit()
{
	CObjectX::Uninit();
}


//========================
//更新処理
//========================
void CDebrisX::Update()
{
	GetLife()++;

	if (GetLife() >= 30)
	{
		SetLife(0);
  		CObjectX::Release();
		//CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::DEBRIS, m_nDirectionCount);
		return;
	}

	CObjectX::Update();
}


//======================
//描画処理
//======================
void CDebrisX::Draw()
{
	CObjectX::Draw();
}


//=====================
//生成
//=====================
CDebrisX* CDebrisX::Create(D3DXVECTOR3 pos)
{
	CDebrisX* m_pDebris3D = new CDebrisX();

	//初期化に成功
	if (SUCCEEDED(m_pDebris3D->Init()))
	{
		//情報がある時
		if (m_pDebris3D != nullptr)
		{
			m_pDebris3D->GetPos() = pos; //位置を同期させる
			m_pDebris3D->Lood(); //Xファイルを読み込む関数を呼ぶ
			m_pDebris3D->SetType(TYPE::DEBRIS);
			return m_pDebris3D; //情報を返す
		}
	}
	
	return nullptr;
}