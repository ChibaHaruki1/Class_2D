//================================
//
//敵の処理[enemy.cpp]
//Auther:Chiba Haruki
//
//================================

#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "explosion.h"
#include "player.x.h"


//=========================
//コンストラクタ
//=========================
CManagerEnemy::CManagerEnemy(int Priority) : CObjectX(Priority)
{

}


//=========================
//デストラクタ
//=========================
CManagerEnemy::~CManagerEnemy()
{

}


//=========================
//初期化処理
//=========================
HRESULT CManagerEnemy::Init()
{
	m_nLife = 3;
	GetPos() = D3DXVECTOR3(700.0f, 50.0f, 0.0f); //位置を設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}


//=========================
//終了処理
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit();
}


//=========================
//更新処理
//=========================
void CManagerEnemy::Update()
{
	
}

//==========================
//描画処理
//==========================
void CManagerEnemy::Draw()
{
	CObjectX::Draw();
}

//==========================
//3Dモデルの敵の作成
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr;

	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX();

		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->m_aFileName = "data\\XFILE\\ENEMY\\Enemy000.x";
		}
	}
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X();

		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->m_aFileName = "data\\XFILE\\ENEMY\\Enemy001.x";
		}
	}

	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->GetPos() = pos;
		pManagerEnemy->Lood();
		pManagerEnemy->Size();
		return pManagerEnemy;
	}

	return nullptr;
}

//===========================================
//敵の処理
//===========================================

//=========================
//更新処理
//=========================
void CEnemyX::Update()
{
	TargetHeadingTowards(CManager::GetScene()->GetPlayerX(),2.0f);  //プレイヤーに向かう処理関数を呼ぶ

	if (CollisionPlayerSelect(this) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * CManagerBossEffect::MAX_DAMAGE;
	}

	//
	if (m_nLife <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）
		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));               //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 50.0f, GetPos().z));            //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetGameScore()->AddScore(1000);                                                          //スコアを加算
		CObjectX::Release();
		return;
	}
	CObjectX::Update();
}

//===========================================
//敵001の処理
//===========================================

//=========================
//更新処理
//=========================
void CEnemy001X::Update()
{
	m_rot.y += 0.1f;

	if (CollisionPlayerSelect(this) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
	}


	if (m_nLife <= 0)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）

		CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y+50.0f, GetPos().z));                 //爆発エフェクトの位置を設定
		CManager::GetInstance()->GetGameScore()->AddScore(100);                                                           //スコアを加算
		CObjectX::Release();
		return;
	}
}