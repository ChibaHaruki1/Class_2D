//===================================
//
//エフェクトの処理[efect.cpp]
//Auther:Chiba Haruki
//
//===================================

#include "main.h"
#include "rendererh.h"
#include "efect.h"
#include "manager.h"


//==================================================================================
//演出用エフェクトのストラテジークラス基底処理
//==================================================================================
CEffectDirection::CEffectDirection()
{
	m_pEffectFileName = nullptr;
	m_nLife = 0;
	m_pVtxBuffMine = nullptr;
}
CEffectDirection::~CEffectDirection()
{
	
}

//==================================================================================
//テクスチャの設定処理
//==================================================================================
void CEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,float fTexSize)
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
void CEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff,double dLifeCount,float fMaxTex)
{
	m_nLife++;  //カウントする

	//ライフが既定の数値になった時
	if (m_nLife >= CManagerEffect::MAX_EXPLOSION_LIFE * dLifeCount)
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
CThunder::CThunder()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\thunder.png";
}
CThunder::~CThunder()
{

}


//==================================================================================
//爆発エフェクト
//==================================================================================
CExplotion::CExplotion()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\explosion001.png";
}
CExplotion::~CExplotion()
{

}


//==================================================================================
//炎の爆発エフェクト
//==================================================================================
CExplotionPillar::CExplotionPillar()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\Fire000.png";
}
CExplotionPillar::~CExplotionPillar()
{

}


//==================================================================================
//柱状の炎エフェクト
//==================================================================================
CExplotionPillar001::CExplotionPillar001()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\PillarOfFireAll.png";
}
CExplotionPillar001::~CExplotionPillar001()
{

}


//==================================================================================
//破片エフェクトのストラテジークラスの継承処理
//==================================================================================
CFormerDebris::CFormerDebris()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\010.png";
}
CFormerDebris::~CFormerDebris()
{

}


//==================================================================================
//必殺技
//==================================================================================
CSourceSpecialAttack::CSourceSpecialAttack()
{
	m_pEffectFileName = "data\\TEXTURE\\UI\\SpecialGage\\SpecialGageRE.png";
}
CSourceSpecialAttack::~CSourceSpecialAttack()
{

}


//=======================================================================================================================================================================
//エフェクトの管理者処理
//=======================================================================================================================================================================
 
//===========================
//コンストラクタ
//===========================
CManagerEffect::CManagerEffect(int nPriority) : CObject3D(nPriority)
{
	m_nLife = (int)(SET_BULLET_LIFE*0.7f);                          //ライフを弾の設定されたライフと同じにする（同時に消すため）
	m_pEffectDirection000 = nullptr;
	m_nEffectNumber = -1;
	m_dLifeCount = 0.0;
	m_fMaxTex = MAX_EXPLOSION_TEX;
}

//===========================
//デストラクタ
//===========================
CManagerEffect::~CManagerEffect()
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
HRESULT CManagerEffect::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	SetSize(40.0f, 40.0f, 0.0f);  //大きさの設定
	//m_pEffectDirection = std::make_shared<CEffectDirection>(0);
	return S_OK;
}

//============================
//破棄処理
//============================
void CManagerEffect::Uninit()
{
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}

//============================
//更新処理
//============================
void CManagerEffect::Update()
{
	if (m_dLifeCount != 0.0)
	{
		m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, m_fMaxTex); //strategyの基底クラスの処理を呼ぶ
	}
	m_nLife--;                     //ライフを減らす

	//炎以外
	if (m_nEffectNumber != 1)
	{
		if (m_nAlpha > 0)
		{
			m_nAlpha -= 5;                 //アルファ値を減らす
		}
	}
	SetCol(255, 255, 255, m_nAlpha);  //色の設定

	//ライフが尽きた時
	if (m_nLife <= 0)
	{
		//炎エフェクト時
		if (m_nEffectNumber == 1)
		{
			this->SetEffect(m_pos);  //自信のエフェクトを呼ぶ
			m_nAlpha = 200;          //アルファ値の設定
			m_nLife = 60;            //ライフの設定
			m_nEffectNumber = -1;    //エフェクトナンバーの初期化（その後消すため）
		}

		//その他の時
		else
		{
			CObject3D::Release();
			return;
		}
	}

	CObject3D::Update();
}

//============================
//描画処理
//============================
void CManagerEffect::Draw()
{
	CObject3D::DrawEffect();
}

//============================
//ビルボード描画処理
//============================
void CManagerEffect::DrawNoml()
{

}


//============================
//エフェクトの設定
//============================
void CManagerEffect::SetEffect(D3DXVECTOR3 pos)
{
	m_pos = pos;
	//m_move = move;
	//m_nLife = nLife;
}


//===========================
//エフェクトの生成
//===========================
CManagerEffect* CManagerEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CManagerEffect* pEffect = nullptr; //基底クラスのポインター

	//雷
	if (type == CObject3D::TYPE::THENDER)
	{
		pEffect = new CBreakEffect(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = 0;                                        //エフェクトナンバーの設定
			pEffect->m_pEffectDirection000 = new CThunder();                     //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff,1.0f);   //一分割
			pEffect->m_dLifeCount = 0.0;
			pEffect->m_fMaxTex = 1.0;
		}
	}

	//爆発
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		pEffect = new CExplosion(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);  //八分割
			pEffect->SetSize(70.0f, 70.0f, 0.0f);                                             //大きさを設定
			pEffect->m_dLifeCount = 0.6;
		}
	}

	//爆発００１
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		pEffect = new CExplosion001(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                                     //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->m_pEffectFileName = "data\\TEXTURE\\UI\\Explosion\\explosion004.png";  //テクスチャのファイルパスを設定
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);                       //八分割
			pEffect->SetSize(70.0f, 70.0f, 0.0f);                                                                  //大きさを設定
			pEffect->m_dLifeCount = 0.6;                                                                           //アニメーションの進める速さを設定
		}
	}

	//炎
	else if (type == CObject3D::TYPE::FIRE)
	{
		pEffect = new CFire(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar();                          //継承クラス
			pEffect->m_nEffectNumber = 1;                                                     //エフェクトナンバーの設定
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);  //八分割                                          
			pEffect->SetSize(92.0f, 190.0f, 0.0f);                                            //大きさの設定
			pEffect->m_dLifeCount = 0.5;                                                      //アニメーションの進める速さを設定
		}
	}

	//柱状の炎
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		pEffect = new CPillarOfFire(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar001();                           //ストラテジーの継承クラス
			pEffect->m_nEffectNumber = 2;                                                         //エフェクトナンバーの設定
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);      //八分割
			pEffect->SetSize(pEffect->m_fPillarOfFireSizeX, pEffect->m_fPillarOfFireSizeY, 0.0f); //大きさの設定
			pEffect->m_dLifeCount = 0.5;                                                          //アニメーションの進める速さを設定
		}
	}

	//破片
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		pEffect = new CDebris(); //継承クラス

		//初期化に成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CFormerDebris();                                 //ストラテジー継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, 1.0f);                   //一分割
		}
	}

	//必殺技
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		pEffect = new CSpecialAttack(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttack();                        //ストラテジー継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->m_pVtxBuff, MAX_EXPLOSION_TEX);    //八分割
			pEffect->SetSize(pEffect->m_fSepecialAttackX, pEffect->m_fSepecialAttackY, 0.0f);   //大きさの設定
		}
	}

	//テクスチャーや位置の同期
	if (pEffect != nullptr)
	{
		pEffect->m_aFileName = pEffect->m_pEffectDirection000->m_pEffectFileName;  //テクスチャのファイルパスの同期
		pEffect->m_pos = pos;                                                      //位置の同期
		pEffect->Lood();                                                           //テクスチャの読み込み関数
		return pEffect;                                                            //情報を返す
	}

	return nullptr; //無を返す
}


//=======================================================================================================================================================
//壊れたときのエフェクト処理
//=======================================================================================================================================================
CBreakEffect::CBreakEffect()
{
	
}
CBreakEffect::~CBreakEffect()
{

}


//==============================================================================================================================================================
//爆発エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CExplosion::CExplosion()
{
	
}

//===========================
//コンストラクタ
//===========================
CExplosion::~CExplosion()
{

}


//==============================================================================================================================================================
//炎エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
CFire::CFire()
{
	m_nLife = 120;
}

//===========================
//コンストラクタ
CFire::~CFire()
{

}

//===========================
//描画処理
//===========================
void CFire::Draw()
{
	CObject3D::DrawEffect1();
}


//==============================================================================================================================================================
//柱状の炎
//==============================================================================================================================================================

//===========================
//コンストラクタ
CPillarOfFire::CPillarOfFire()
{
	m_nLife = 180;
	m_nAlpha = 255;
	m_nFrame = 0;
}

//===========================
//コンストラクタ
CPillarOfFire::~CPillarOfFire()
{

}

//============================
//初期化処理
//============================
HRESULT CPillarOfFire::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
//更新処理
//============================
void CPillarOfFire::Update()
{
	this->m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff,0.5, MAX_EXPLOSION_TEX); //自身のストラテジー継承クラスの処理を呼ぶ
	SetCol(255, 255, 255, m_nAlpha);  //色の設定

	//フレームが規定値に行った時
	if (m_nFrame >= 60)
	{
		if (CObject3D::CollisionPrtsPlayer(m_fPillarOfFireSizeX, m_fPillarOfFireSizeY, 40.0f) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.01f; //HPゲージを減らす
			CManager::GetInstance()->GetPlayerHPGage()->SetSIze(0.0f, CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX(), 40.0f, 70.0f);  //大きさをあらかじめ決めないと
			m_nFrame = 0;
			m_nLife = 0;
		}
	}
	else
	{
		m_nFrame++;
	}

	//ライフが０以下の時
	if (m_nLife <= 0)
	{
		m_nAlpha -= 5;  //alpha値を減らす
		
		//alpha値が０以下の時
		if (m_nAlpha <= 0)
		{
			CObject::Release(); //自身を削除
			return;             //処理を抜ける
		}
	}
	else
	{
		m_nLife--;
	}
}


//==============================================================================================================================================================
//弾につくエフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	m_nLife = SET_BULLET_LIFE/2;                          //ライフを弾の設定されたライフと同じにする（同時に消すため）
	m_aFileName = "data\\TEXTURE\\UI\\effect000.jpg"; //テクスチャのファイルパスを設定
}


//===========================
//デストラクタ
//===========================
CEffect::~CEffect()
{
	
}


//============================
//初期化処理
//============================
HRESULT CEffect::Init()
{
	//頂点バッファ生成
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;
	}
	SetSize(40.0f, 40.0f, 0.0f);
	return S_OK;
}


//============================
//破棄処理
//============================
void CEffect::Uninit()
{
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}


//============================
//更新処理
//============================
void CEffect::Update()
{
	m_nLife--;
	if (m_nLife <= 0)
	{
		CObject3D::Release();
		return;
	}

	CObject3D::Update();
}


//============================
//描画処理
//============================
void CEffect::Draw()
{
	CObject3D::DrawEffect();
}


//============================
//ビルボード描画処理
//============================
void CEffect::DrawNoml()
{
	
}


//============================
//エフェクトの設定
//============================
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	m_pos = pos;
	m_move = move;
	m_nLife = nLife;
}


//===========================
//エフェクトの生成
//===========================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pEffect = new CEffect();

	if (SUCCEEDED(pEffect->Init()))
	{
		if (pEffect != nullptr)
		{
			pEffect->m_pos = pos;
			pEffect->Lood();
			return pEffect;
		}
	}

	return nullptr;
}


//==============================================================================================================================================================
//爆発エフェクト001
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CExplosion001::CExplosion001()
{
	
}


//===========================
//コンストラクタ
//===========================
CExplosion001::~CExplosion001()
{

}

//==============================================================================================================================================================
//破片エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CDebris::CDebris()
{
	m_nLife = 10;
	m_fSiseX = 50.0f;
}


//===========================
//コンストラクタ
//===========================
CDebris::~CDebris()
{

}

//===========================
//更新処理
//===========================
void CDebris::Update()
{
	m_nLife--;                            //ライフを減らす
	m_fSiseX+=4.0f;                       //サイズを大きくする
	SetSize(m_fSiseX,m_fSiseX,0.0f);      //サイズの設定

	//ライフが０以下の時
	if (m_nLife <= 0)
	{
		CObject3D::Release(); //自身を消す
	}
}


//==============================================================================================================================================================
//必殺技
//==============================================================================================================================================================

//===========================
//コンストラクタ
CSpecialAttack::CSpecialAttack()
{
	m_nLife = 180;
	m_nAlpha = 255;
	m_nFrame = 0;
	m_fSizeX = m_fSepecialAttackX;
	m_nRotNumber = 0;
}

//===========================
//コンストラクタ
CSpecialAttack::~CSpecialAttack()
{

}

//============================
//更新処理
//============================
void CSpecialAttack::Update()
{
	this->m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff,0.3, MAX_EXPLOSION_TEX); //自身のストラテジー継承クラスの処理を呼ぶ

	SetCol(255, 255, 255, m_nAlpha);         //色の設定

	if (m_fSizeX <= 2000.0f)
	{
		m_fSizeX += 30.0f;                    //サイズを大きくする
	}

	if (m_nRotNumber == 1)
	{
		SetEffectSize(m_fSizeX, m_fSepecialAttackY, 0.0f);    //サイズの設定
	}
	else if(m_nRotNumber == 2)
	{
		SetEffectSize(-m_fSizeX, m_fSepecialAttackY, 0.0f);   //サイズの設定
	}

	if (CManager::GetScene()->GetPlayerX()->GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
	{
		//m_rot.y = CManager::GetScene()->GetCamera()->GetRot().y -D3DX_PI;
	}

	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 0; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
				m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), m_fSizeX, nCount2))
			{
				//CManager::GetInstance()->GetPlayerHPGage()->SetSIze(0.0f, CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX(), 40.0f, 70.0f); //大きさをあらかじめ決めないと
				CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.00005f; //ボスのHPゲージを減らす
			}
		}
	}

	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count() + 1; nMotionInEnemy001++)
	{
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			for (int nCount1 = 0; nCount1 < CObjectX::MAX_ENEMYPARTS; nCount1++)
			{
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nCount1),
					m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(nCount1), m_fSizeX, nCount1))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() -= 1;

					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //ポインターをnullptrにする
						return;
					}
				}
			}
		}
	}
	

	//ライフが０以下の時
	if (m_nLife <= 0)
	{
		m_nAlpha -= 5;          //alpha値を減らす

		//alpha値が０以下の時
		if (m_nAlpha <= 0)
		{
			CObject::Release(); //自身を削除
			return;             //処理を抜ける
		}
	}
	else
	{
		m_nLife--; //ライフを減らす
	}
}