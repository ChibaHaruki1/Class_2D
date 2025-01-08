//==================================
//
//弾の処理[bullet.h]
//Auther:Chiba Haruki
//
//==================================

//インクルード
#include "main.h"
#include "manager.h"
#include "bullet.h"


//==============================================================================================================
//==================================================3D弾の処理==================================================
//==============================================================================================================

//=====================
//コンストラクタ
//=====================
CManagerBullet::CManagerBullet(int nPriority) :CObject3D(nPriority)
{
	//ポインター初期化
	//m_aFileName = "data\\TEXTURE\\bullet001.png";
}

//=====================
//デストラクタ
//=====================
CManagerBullet::~CManagerBullet()
{

}


//=====================
//初期化処理
//=====================
HRESULT CManagerBullet::Init()
{
	//頂点バッファ生成に失敗したとき
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //失敗を返す
	}
	SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetSizeX(40.0f);
	SetSize(GetSizeX(), 40.0f, 0.0f);//サイズの調整
	return S_OK;
}


//=====================
//終了処理
//=====================
void CManagerBullet::Uninit()
{
	CObject3D::Uninit();  //基底クラスの破棄処理
}


//=====================
//更新処理
//=====================
void CManagerBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetCol(255, 160, 0, GetAlpha()); //色の設定

	if (GetAlpha() >= 1)
	{
		GetAlpha() -= 5;
	}

	GetLife()--; //寿命カウント

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//=====================
//描画処理
//=====================
void CManagerBullet::Draw()
{
	CObject3D::DrawBillboard();
}


//====================
//弾の位置の設定処理
//====================
void CManagerBullet::SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	SetPos(pos); //弾の位置を引数と同期する
	SetMove(move); //弾の移動量を引数と同期する
	SetLife(nLife); //寿命を設定する
}


//=========================
//弾のの生成
//=========================
CManagerBullet* CManagerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject::TYPE type)
{
	CManagerBullet* pBullet3D = nullptr;

	if (type == CObject3D::TYPE::BULLET)
	{
		pBullet3D = new CBullet3D(3);

		if (SUCCEEDED(pBullet3D->Init()))
		{

		}
	}
	else if (type == CObject3D::TYPE::SPECIALBULLET)
	{
		pBullet3D = new CSpecialBullet(3);

		if (SUCCEEDED(pBullet3D->Init()))
		{

		}
	}
	else if (type == CObject3D::TYPE::ENEMYBULLET)
	{
		pBullet3D = new CEnemyBullet(3);

		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(40.0f, 40.0f, 40.0f);
		}
	}
	else if (type == CObject3D::TYPE::BOSSBULLET)
	{
		pBullet3D = new CBossBullet(3);

		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(40.0f, 40.0f, 40.0f);
		}
	}

	if (pBullet3D != nullptr)
	{
		pBullet3D->SetFileNamePass("data\\TEXTURE\\bullet001.png");
		pBullet3D->SetInfo(pos, move, nLife);
		pBullet3D->Lood();
		return pBullet3D;
	}
	return nullptr;
}

//================================================================================================================================================
//プレイヤーの通常弾処理
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CBullet3D::CBullet3D(int nPriority) : CManagerBullet(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CBullet3D::~CBullet3D()
{

}




//===========================
//エフェクトの処理を呼ぶ
//===========================
void CBullet3D::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //雷エフェクトを呼ぶ
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //破片エフェクトを呼ぶ


	CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());                                                        //爆発エフェクトの位置を設定
	CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos());                                                     //爆発エフェクトの位置を設定
	CManager::GetInstance()->GetThander()->SetEffect(GetPos());                                                          //雷エフェクトの位置を設定
	//CManager::GetInstance()->GetDebris()->SetEffect(GetPos());                                                           //破片エフェクトの位置を設定
}


//===============================
//オブジェクトとの当たり判定
//===============================
void CBullet3D::CollisionOnObject()
{
	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//ブロックとの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize()) == true)
		{
			CallEffect(true);         //エフェクト処理を呼ぶ

			CObject3D::Release();     //自身の解放
			return;                   //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}

	//敵の情報がある時
	if (CManager::GetInstance()->GetEnemy000() != nullptr)
	{
		//敵との当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy000()->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy000()->GetModelSize()*0.4f, GetSizeX(), 10) == true)
		{
			//CallEffect(true);         //エフェクト処理を呼ぶ
			CManager::GetInstance()->GetEnemy000()->GetLife() -= 1;   //敵のライフを減らす

			//敵のライフが０以下の時
			if (CManager::GetInstance()->GetEnemy000()->GetLife() <= 0)
			{
				CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY, 0); //ポインターをnullptrにする
			}

			SetLife(0); //ライフを０にする
			return;
		}
	}

	//敵001の情報がある時
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetEnemyCount() + 1; nCount1++)
	{
		if (CManager::GetInstance()->GetEnemy001(nCount1) != nullptr)
		{
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy001(nCount1)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy001(nCount1)->GetModelSize() * 0.5f, GetSizeX(), 10) == true)
			{
				CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() -= 1; //敵のライフを減らす

				//敵のライフが０以下の時
				if (CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY001, nCount1);  //ポインターをnullptrにする
				}

				SetLife(0); //ライフを０にする
				return;
			}
		}
	}

	//カメラの上部分の情報がある時
	if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
	{
		//カメラとの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(),
			GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
			CManager::GetInstance()->GetSurveillanceCameraUp(0)->GetModelSize()))
		{
			CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->Release(); //カメラの上部分の削除
			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SURVEILLANCECAMERAUP, 0);                                    //ポインターをnullptrにする

			SetLife(0); //ライフを０にする
			return;
		}
	}

	//モーション付きの敵001の情報がある時
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count()+1; nMotionInEnemy001++)
	{
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			for (int i = 0; i < CObjectX::MAX_ENEMYPARTS; i++)
			{
				//モーション付きの敵001の当たり判定
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(i),
					GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(i) * 0.5f))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() -= 1;

					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{                                     
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //ポインターをnullptrにする
					}

					SetLife(0); //ライフを０にする
					return;
				}
			}
		}
	}

	//ボスの情報がある時
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 2; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			if (CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->m_bCreateGun == true)
			{
				//ボスとの当たり判定
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
					MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), GetSizeX(), nCount2))
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.01f; //ボスのHPゲージを減らす

					//指定のpartsを描画しない＋処理から外す条件にする
					if (nCount2 == 6 || nCount2 == 7 || nCount2 == 8 || nCount2 == 9 || nCount2 == 11 || nCount2 == 12 || nCount2 == 13 || nCount2 == 15)
					{
						CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->m_bCreateGun = false;
					}

					CallEffect(true);         //エフェクト処理を呼ぶ
					CObject3D::Release();     //自身の解放
					return;                   //処理を抜ける
				}
			}
		}
	}
}

//================================================================================================================================================
//プレイヤーの必殺弾処理
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CSpecialBullet::CSpecialBullet(int nPriority) : CManagerBullet(nPriority)
{

}


//======================
//コンストラクタ
//======================
CSpecialBullet::~CSpecialBullet()
{

}


//===========================
//更新処理
//===========================
void CSpecialBullet::Update()
{
	if (CManager::GetScene()->GetPlayerX()->m_pModelPrts[18]->m_bCreateGun == true)
	{
		if (GetSizeX() <= 1000.0f)
		{
			GetSizeX() += 10.0f;
		}
		SetSize(GetSizeX(), 40.0f, 0.0f);//サイズの調整
	}
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CSpecialBullet::CallEffect(bool bUse)
{
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //雷エフェクトを呼ぶ
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //破片エフェクトを呼ぶ
	////CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //破片エフェクトを呼ぶ


	//CManager::GetInstance()->GetExplosion()->SetEffect(m_pos);                                                        //爆発エフェクトの位置を設定
	//CManager::GetInstance()->GetExplosion001()->SetEffect(m_pos);                                                     //爆発エフェクトの位置を設定
	//CManager::GetInstance()->GetThander()->SetEffect(m_pos);                                                          //雷エフェクトの位置を設定
	//CManager::GetInstance()->GetDebris()->SetEffect(m_pos);                                                           //破片エフェクトの位置を設定
	////CManager::GetInstance()->GetPillarOfFire()->SetEffect(m_pos);                                                           //破片エフェクトの位置を設定
}


//===============================
//オブジェクトとの当たり判定
//===============================
void CSpecialBullet::CollisionOnObject()
{
	//ボスの当たり判定
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 0; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//敵との当たり判定
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
				40, 40.0f, MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), GetSizeX(), nCount2))
			{
				if (CManager::GetScene()->GetPlayerX()->m_pModelPrts[18]->m_bCreateGun == false)
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.01f; //ボスのHPゲージを減らす
					CallEffect(true);         //エフェクト処理を呼ぶ
					CObject3D::Release();     //自身の解放
					return;                   //処理を抜ける
				}
				else
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.0001f; //ボスのHPゲージを減らす
				}
			}
		}
	}
}

//======================================================================================================================================================================
//敵の弾の処理
//======================================================================================================================================================================

//static変数の初期化
float CEnemyBullet::m_fAdditionPosY = InitAddItion;

//=====================
//コンストラクタ
//=====================
CEnemyBullet::CEnemyBullet(int nPriority) :CManagerBullet(nPriority)
{
	SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=====================
//デストラクタ
//=====================
CEnemyBullet::~CEnemyBullet()
{
	CObject3D::Uninit();
}


//=====================
//更新処理
//=====================
void CEnemyBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, GetAlpha()); //色の設定
	GetPos().y -= m_fAdditionPosY;

	//アルファ値が0より大きい時
	if (GetAlpha() > 0)
	{
		GetAlpha() -= 5;
	}

	GetLife()--; //寿命カウント

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CEnemyBullet::CallEffect(bool bUse)
{
	
}


//===============================
//オブジェクトとの当たり判定
//===============================
void CEnemyBullet::CollisionOnObject()
{
	//プレイヤーのパーツ数分回す
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//プレイヤーの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f, nCount2))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.05f; //HPゲージを減らす

			CallEffect(true);         //エフェクト処理を呼ぶ
			CObject3D::Release();     //自身の解放
			return;                   //処理を抜ける
		}
	}
}


//======================================================================================================================================================================
//ボスの弾の処理
//======================================================================================================================================================================

//static変数の初期化

//=====================
//コンストラクタ
//=====================
CBossBullet::CBossBullet(int nPriority) :CManagerBullet(nPriority)
{
	SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=====================
//デストラクタ
//=====================
CBossBullet::~CBossBullet()
{
	CObject3D::Uninit();
}


//=====================
//更新処理
//=====================
void CBossBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, GetAlpha()); //色の設定

	//アルファ値が0より大きい時
	if (GetAlpha() >0)
	{
		GetAlpha() -= 5;
	}

	GetLife()--; //寿命カウント

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CBossBullet::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //柱状の炎エフェクトを呼ぶ
	CManager::GetInstance()->GetPillarOfFire()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 200.0f, GetPos().z));                 //柱状の炎エフェクトの位置を設定
}


//===============================
//オブジェクトとの当たり判定
//===============================
void CBossBullet::CollisionOnObject()
{
	//プレイヤーのパーツ数分回す
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//プレイヤーの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f, nCount2))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.05f; //HPゲージを減らす

			CallEffect(true);         //エフェクト処理を呼ぶ
			CObject3D::Release();     //自身の解放
			return;                   //処理を抜ける
		}
	}
}