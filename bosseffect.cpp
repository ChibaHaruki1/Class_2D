//===================================
//
//エフェクトの処理[efect.cpp]
//Auther:Chiba Haruki
//
//===================================

//インクルード
#include "main.h"
#include "rendererh.h"
#include "bosseffect.h"
#include "manager.h"

//==================================================================================
//演出用エフェクトのストラテジークラス基底処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CBossEffectDirection::CBossEffectDirection()
{
	m_pEffectFileName = nullptr;
	m_nLife = 0;
	m_pVtxBuffMine = nullptr;
}

//==========================================
//デストラクタ
//==========================================
CBossEffectDirection::~CBossEffectDirection()
{

}

//==================================================================================
//テクスチャの設定処理
//==================================================================================
void CBossEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(fTexSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexSize, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================================================================================
//テクスチャの更新処理
//==================================================================================
void CBossEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount ,float fMaxTex)
{
	m_nLife++;  //カウントする

	//ライフが既定の数値になった時
	if (m_nLife >= CManagerBossEffect::MAX_BOSSANIMATION_LIFE * dLifeCount)
	{
		VERTEX_3D* pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex.x = pVtx[0].tex.x + fMaxTex;
		pVtx[1].tex.x = pVtx[1].tex.x + fMaxTex;
		pVtx[2].tex.x = pVtx[2].tex.x + fMaxTex;
		pVtx[3].tex.x = pVtx[3].tex.x + fMaxTex;

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();

		m_nLife = 0; //ライフを初期化する
	}
}


//==================================================================================
//演出用エフェクトのストラテジークラスの継承処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CAttackEffect::CAttackEffect()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Impact.png";
}

//==========================================
//デストラクタ
//==========================================
CAttackEffect::~CAttackEffect()
{

}


//==================================================================================
//必殺技のストラテジークラスの継承処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CSourceSpecialAttackBoss::CSourceSpecialAttackBoss()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\SpecialGage\\BossSpecialAllGage002.png";
}

//==========================================
//デストラクタ
//==========================================
CSourceSpecialAttackBoss::~CSourceSpecialAttackBoss()
{

}


//=======================================================================================================================================================================
//エフェクトの管理者処理
//=======================================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CManagerBossEffect::CManagerBossEffect(int nPriority) : CObject3D(nPriority)
{
	SetLife(100);                         
	m_pEffectDirection000 = nullptr;
	m_nEffectNumber = -1;
	m_nBossRotNumber = 0;
	m_dLifeCount = 0.0;
	m_bFly = false;
}


//===========================
//デストラクタ
//===========================
CManagerBossEffect::~CManagerBossEffect()
{
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;
		m_pEffectDirection000 = nullptr;
	}
}


//============================
//初期化処理
//============================
HRESULT CManagerBossEffect::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	SetSizeX(40.0f);
	SetSizeY(40.0f);
	SetSize(GetSizeX(), GetSizeY(), 40.0f);  //大きさの設定
	return S_OK;
}


//============================
//初期化処理
//============================
void CManagerBossEffect::Uninit()
{
	//m_pEffectDirection = std::make_shared<CEffectDirection>(1);
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}


//============================
//初期化処理
//============================
void CManagerBossEffect::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, fMaxTex);
	//m_nLife--;                           //ライフを減らす

	//SetCol(255, 255, 255, m_nAlpha);     //色の設定

	////ライフが尽きた時
	//if (m_nLife <= 0)
	//{
	//	CManager::GetInstance()->DesignationUninit3D(IMPACT);
	//	CObject3D::Release();
	//	return;
	//}

	//CObject3D::Update();
}

//============================
//初期化処理
//============================
void CManagerBossEffect::Draw()
{
	CObject3D::DrawEffect();
}


//============================
//エフェクトの設定
//============================
void CManagerBossEffect::SetEffect(D3DXVECTOR3 pos)
{
	SetPos(pos);
	//m_move = move;
	//m_nLife = nLife;
}


//===========================
//エフェクトの生成
//===========================
CManagerBossEffect* CManagerBossEffect::Create(D3DXVECTOR3 pos, CObject3D::TYPE type)
{
	CManagerBossEffect* pEffect = nullptr;

	if (type == CObject3D::TYPE::IMPACT)
	{
		pEffect = new CImpact();

		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;
			pEffect->m_pEffectDirection000 = new CAttackEffect();
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(),1.0f);
		}
	}
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		pEffect = new CBossSpecialAttack();

		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttackBoss();
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), MAX_BOSSANIMETION_TEX);
			pEffect->SetSize(200.0f, 200.0f, 0.0f);   //大きさの設定
		}
	}
	
	if (pEffect != nullptr)
	{
		pEffect->SetFileNamePass(pEffect->m_pEffectDirection000->m_pEffectFileName);
		pEffect->SetPos(pos);
		pEffect->Lood();
		return pEffect;
	}

	return nullptr;
}


//=======================================================================================================================================================
//衝撃波のエフェクトの処理
//=======================================================================================================================================================

//============================
//コンストラクタ
//============================
CImpact::CImpact()
{

}

//============================
//デストラクタ
//============================
CImpact::~CImpact()
{

}

//============================
//更新処理
//============================
void CImpact::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, 0.0f,1.0f);
	GetLife()--;                           //ライフを減らす
	GetSizeX() += 4.0f;                    //ｘ軸のサイズを大きくする
	GetSizeY() += 1.0f;                    //ｙ軸のサイズを大きくする

	SetCol(255, 255, 255, GetAlpha());       //色の設定
	SetSize(GetSizeX(), GetSizeY(), 40.0f);  //大きさの更新

	//右側に当たった時
	if (CObject3D::CollisionPrts1Right(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		m_bFly = true;
	}
	//左側に当たった時
	else if (CObject3D::CollisionPrts1Left(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x -= 100.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().y += 100.0f;
	}

	//ライフが尽きた時
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->DesignationUninit3D(TYPE::IMPACT);
		CObject3D::Release();
		return;
	}

	CObject3D::Update();
}


//=======================================================================================================================================================
//必殺技のエフェクトの処理
//=======================================================================================================================================================

//============================
//コンストラクタ
//============================
CBossSpecialAttack::CBossSpecialAttack()
{

}

//============================
//デストラクタ
//============================
CBossSpecialAttack::~CBossSpecialAttack()
{

}

//============================
//更新処理
//============================
void CBossSpecialAttack::Update()
{
	this->m_pEffectDirection000->Effect(GetTexture(), GetBuffer(), 0.3, MAX_BOSSANIMETION_TEX); //自身のストラテジー継承クラスの処理を呼ぶ

	SetCol(255, 255, 255, GetAlpha());          //色の設定

	//サイズが規定値より大きくなった時
	if (GetSizeX() <= 2000.0f)
	{
		GetSizeX() += 30.0f;                    //サイズを大きくする
	}

	float a = GetPos().y - CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(17).y * 1.5f;
	float b = CManager::GetScene()->GetPlayerX()->GetPos().x;

	//向き番号が１の時
	if (GetRotNumber() == 1)
	{
		SetEffectSize(GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);    //サイズの設定

		//点Cは自機が右に居る時点で確定で小さいため現在のpos.xを足した上で計算する
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), GetPos().x, GetPos().y + PLUS_POS_Y,
			GetSizeX() + GetPos().x, a) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
		}
	}

	//向き番号が２の時
	else if (GetRotNumber() == 2)
	{
		SetEffectSize(-GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);   //サイズの設定

		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), -GetSizeX() + GetPos().x, GetPos().y + PLUS_POS_Y,
			GetPos().x, a) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE;
		}
	}

	//ライフが０以下の時
	if (GetLife() <= 0)
	{
		GetAlpha() -= 5;          //alpha値を減らす

		//alpha値が０以下の時
		if (GetAlpha() <= 0)
		{
			CObject::Release(); //自身を削除
			return;             //処理を抜ける
		}
	}
	else
	{
		GetLife()--; //ライフを減らす
	}
}