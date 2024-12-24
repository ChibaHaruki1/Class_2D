//=========================================================================
//
//モーション付きの敵の処理[enemyinmotion.cpp]
//Auther;Haruki Chiba
//
//=========================================================================

//==============================
//インクルード
#include "enemyinmotion.h"
#include "manager.h"
#include <time.h>

//=============================
//コンストラクタ
//=============================
CManagerEnemyInMotion::CManagerEnemyInMotion(int nPriority) : CEnemyCharacter(nPriority)
{
	m_nJumpFrame = 0;
	m_aFileName = nullptr;
	JumpNumber = 0;
	JumpRecastTime = 0;
}

//=============================
//デストラクタ
//=============================
CManagerEnemyInMotion::~CManagerEnemyInMotion()
{

}

//=============================
//初期化処理
//=============================
HRESULT CManagerEnemyInMotion::Init()
{
	//頂点バッファ生成
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}
	CEnemyCharacter::LoodEnemy(m_aFileName);
	CEnemyCharacter::SetMotionEnemy(ENEMYWALK);

	return S_OK;
}

//==============================
//破棄処理
//==============================
void CManagerEnemyInMotion::Uninit()
{
	CEnemyCharacter::Uninit();
}

//==============================
//更新処理
//==============================
void CManagerEnemyInMotion::Update()
{
	
}

//==============================
//描画処理
//==============================
void CManagerEnemyInMotion::Draw()
{
	CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //描画処理
}

//==============================
//生成処理
//==============================
CManagerEnemyInMotion* CManagerEnemyInMotion::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemyInMotion* pEnemyInMotion = nullptr;

	if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		pEnemyInMotion = new CEnemyInMotion();
		pEnemyInMotion->m_aFileName = "Enemy000";
	}
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		pEnemyInMotion = new CEnemyInMotion001();
		pEnemyInMotion->m_aFileName = "Enemy001";
	}

	//情報がある時
	if (pEnemyInMotion != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pEnemyInMotion->Init()))
		{
			pEnemyInMotion->m_pos = pos; //位置の同期
			return pEnemyInMotion;       //情報を返す
		}
	}

	return nullptr; //無を返す
}


//====================================================================================================================================
//敵の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion::CEnemyInMotion(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	m_rot.y = D3DX_PI*-0.5f;
}

//=============================
//デストラクタ
//=============================
CEnemyInMotion::~CEnemyInMotion()
{

}

//==============================
//更新処理
//==============================
void CEnemyInMotion::Update()
{
	CEnemyCharacter::UpdateEnemy001();                                                       //モーションの情報を更新する

	if (CObjectX::CollisionPlayerInEnemy(this,2.0f)==true)
	{
		CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //モーションの種類を設定

		m_nFrame++;
		if (m_nFrame >= 60)
		{
			CManagerBullet::Create(D3DXVECTOR3(this->m_posPrtsEnemy[0].x, this->m_posPrtsEnemy[0].y, this->m_posPrtsEnemy[0].z), D3DXVECTOR3(-sinf(m_rot.y) * MAX_BUULET_SPEED, 0.0f, -cosf(m_rot.y) * MAX_BUULET_SPEED),
				SET_BULLET_LIFE, CObject3D::ENEMYBULLET);
			m_nFrame = 0;
		}
	}
	else
	{
		if (m_JumpFlag == false)
		{
			CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定
			TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //プレイヤーに向かうように設定
		}
	}

	Junp(TYPE::ENEMYINMOTION, 15.0f);                          //ジャンプと重力処理関数を呼ぶ

	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//地面用ブロックの情報がある時
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (JumpNumber == -1)
			{
				//自機と地面用ブロックが当たったら
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, m_move) == true)
				{
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++;
						if (m_nJumpFrame >= 20)
						{
							m_JumpFlag = true; //飛ぶフラグをONにする

							m_nJumpFrame = 0;
							JumpNumber++;
							return;            //処理を抜ける
						}
					}
					else if (JumpRecastTime >= 0)
					{
						JumpRecastTime--;
					}

				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //重力を同期させる

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y軸の位置を設定
					}
				}
			}

			else if (JumpNumber == 0)
			{
				//自機と地面用ブロックが当たったら
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, m_move) == true)
				{
					JumpRecastTime = 5;
					JumpNumber = -1;
					return;            //処理を抜ける
				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //重力を同期させる

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y軸の位置を設定
					}
				}
			}

		}
	}

	CObjectX::Update(); //位置の更新
}


//====================================================================================================================================
//敵001の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	m_rot.y = D3DX_PI * -0.5f; //向きを設定（右向き）
	m_nHitFrame = 0;
	m_bHit = false;
	m_nLife = 5;
}

//=============================
//デストラクタ
//=============================
CEnemyInMotion001::~CEnemyInMotion001()
{

}


//==============================
//更新処理
//==============================
void CEnemyInMotion001::Update()
{
	//プレイヤーが判定の範囲内に来たら更新処理を実行する
	if (CObjectX::CollisionPlayerInEnemy(this, 10.0f) == true)
	{
		if (m_nLife > 0)
		{
			CEnemyCharacter::UpdateEnemy001();                                                    //モーションの情報を更新する

			//プレイヤーと当たっている時
			if (CObjectX::CollisionPlayerInEnemy(this, 4.0f) == true)
			{
				CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //モーションの種類を設定

				m_nFrame++;     //弾を撃つ際のフレームを増やす

				//フレームが規定数に達した時
				if (m_nFrame >= 60)
				{
					CManagerBullet::Create(D3DXVECTOR3(this->m_posPrtsEnemy[4].x + 100.0f, this->m_posPrtsEnemy[4].y + 30.0f, this->m_posPrtsEnemy[4].z), D3DXVECTOR3(-sinf(m_rot.y) * MAX_BUULET_SPEED, 0.0f, -cosf(m_rot.y) * MAX_BUULET_SPEED),
						SET_BULLET_LIFE, CObject3D::ENEMYBULLET);
					m_nFrame = 0; //フレームの初期化
				}

				//プレイヤーが敵に接触したら
				if (CObjectX::CollisionPlayerInEnemy(this, 1.5f) == true)
				{
					m_bHit = true; //当たった判定をOnにする
				}

				//AdjustmentBulletAndRot(); //プレイヤーに対する機体と弾の調整処理を呼ぶ
			}

			//プレイヤーと当たってない時
			else
			{
				//向きの初期化
				m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;
				CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion;

				//飛んでいないとき
				if (m_JumpFlag == false)
				{
					CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定

					//ジャンプのリキャストタイムが切れた時
					if (m_nJumpFrame == 0)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);        //プレイヤーに向かうように設定
					}
				}
			}

			//プレイヤーが敵に当たった時
			if (m_bHit == true)
			{
				PlayerBloWwaway();               //プレイヤーの吹き飛び処理を呼ぶ
			}

			Junp(TYPE::ENEMYINMOTION001, 15.0f); //ジャンプと重力処理関数を呼ぶ
			WhenCollisionBlock();                //地面用のブロックに触れている時の処理
			CObjectX::Update();                  //move値の更新
		}

		else if (m_nLife <= 0)
		{
			m_nDieFrame++;
			srand((unsigned)time(NULL));  //乱数系列を初期化
			if (m_nDieFrame <= 1)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //爆発エフェクトの位置を設定

				CManager::GetInstance()->GetExplosion()->SetEffect(m_pos);                                                        //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetEffect(m_pos);
			}
			else if (m_nDieFrame <= 20)
			{

			}

			else if (m_nDieFrame <= 21)
			{
				m_nRandom = -100 + rand() % 200;

				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //爆発エフェクトの位置を設定

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else if (m_nDieFrame <= 40)
			{

			}
			else if (m_nDieFrame <= 41)
			{

				m_nRandom = -100 + rand() % 200;
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //爆発エフェクトの位置を設定

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else if (m_nDieFrame <= 60)
			{

			}
			else if (m_nDieFrame <= 61)
			{

				m_nRandom = -100 + rand() % 200;
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを呼ぶ（1つ目）
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを呼ぶ（2つ目）

				CManager::GetInstance()->GetExplosion()->SetSize(250.0f, 250.0f, 0.0f);                                           //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetSize(250.0f, 250.0f, 0.0);                                         //爆発エフェクトの位置を設定

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else
			{
				CManager::GetInstance()->GetGameScore()->AddScore(2000);                                                          //スコアを加算
				CObjectX::Release();
				return;
			}
		}
	}
}

//===============================================
//プレイヤーが敵に当たった時
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //当たった

	//Hitframeが既定値へいった時
	if (m_nHitFrame <= 20)
	{
		//左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += 10.0f;  //右に移動
		}

		//右向きの時
		else if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= 10.0f;  //左に移動
		}
	}
	else
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= 
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.001f; //HPゲージを減らす
		m_nHitFrame = 0; //hitframeを初期化
		m_bHit = false;  //当たった判定をoffにする
	}
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//左向きの時
	if (m_rot.y >= D3DX_PI_ORI)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetMuki()==1)
		{
			m_pModelPrtsEnemy[0]->m_rot.x += 0.01f;
			CEnemyBullet::m_fAdditionPosY -= 0.3f;
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			m_pModelPrtsEnemy[0]->m_rot.x -= 0.01f;
			CEnemyBullet::m_fAdditionPosY += 0.3f;
		}
	}

	//右向きの時
	else if (m_rot.y <= -D3DX_PI_ORI)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 1)
		{
			m_pModelPrtsEnemy[0]->m_rot.x -= 0.01f; //
			CEnemyBullet::m_fAdditionPosY += 0.3f;
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			m_pModelPrtsEnemy[0]->m_rot.x += 0.01f;
			CEnemyBullet::m_fAdditionPosY -= 0.3f;
		}
	}

	Correctionrot(); //向きを修正する関数を呼ぶ
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//地面用ブロックの情報がある時
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (JumpNumber == -1)
			{
				//自機と地面用ブロックが当たったら
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, m_move) == true)
				{
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++;
						SetMotionEnemy(ENEMYJUMP);
						if (m_nJumpFrame >= 40)
						{
							m_JumpFlag = true; //飛ぶフラグをONにする
							m_nJumpFrame = 0;
							JumpNumber++;

							return;            //処理を抜ける
						}
					}
					else if (JumpRecastTime >= 0)
					{
						JumpRecastTime--;
					}
					return;
				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //重力を同期させる

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y軸の位置を設定
					}
				}
			}

			else if (JumpNumber == 0)
			{
				//自機と地面用ブロックが当たったら
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, m_move) == true)
				{
					JumpRecastTime = 5;
					JumpNumber = -1;
					return;            //処理を抜ける
				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //重力を同期させる

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y軸の位置を設定
					}
				}
			}
		}
	}

	//道用ブロック分回す
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetRoadBlockCount() + 1; nCount2++)
	{
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), m_ModelSize, CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.01f, m_move) == true)
			{

			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), m_ModelSize, CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), m_move) == true)
				{
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;//y軸の位置を設定
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //フラグをflaseにする
					}
				}
			}
		}
	}

	//壁兼道用ブロック分回す
	for (int nCount3 = 0; nCount3 < CManager::GetInstance()->GetWallRoadBlockCount() + 1; nCount3++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			if (m_pCollision->ColiisionBoxRoadBlock001(m_pos, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), m_ModelSize, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * 1.01f, m_move) == true)
			{

			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), m_ModelSize, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), m_move) == true)
				{
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;//y軸の位置を設定
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //フラグをflaseにする
					}
				}
			}
		}
	}
	
	//壁兼道001用ブロック分回す
	for (int nCount4 = 0; nCount4 < CManager::GetInstance()->GetWallRoadBlock001Count() + 1; nCount4++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), m_ModelSize, CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), m_move) == true)
			{
				GravityTogether();
				m_pos.y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;//y軸の位置を設定
				if (m_JumpFlag == true)
				{
					m_JumpFlag = false; //フラグをflaseにする
				}
			}
		}
	}

	//小さいブロック分回す
	for (int nCount5 = 0; nCount5 < CManager::GetInstance()->GetSmallBlockCount() + 1; nCount5++)
	{
		if (CManager::GetInstance()->GetSmallBlock(nCount5) != nullptr)
		{
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), m_ModelSize, CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize() * 1.3f, m_move) == true)
			{

			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), m_ModelSize, CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), m_move) == true)
				{
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;//y軸の位置を設定
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //フラグをflaseにする
					}
				}
			}
		}
	}

}

//===============================================
//向きを修正
//===============================================
void CEnemyInMotion001::Correctionrot()
{
	//加減算してきた変数の値が既定の位置の範囲内の時
	if (CEnemyBullet::m_fAdditionPosY <= -CEnemyBullet::InitAddItion && CEnemyBullet::m_fAdditionPosY >= -8.0f)
	{
		m_rot.y = -D3DX_PI_ORI;                                         //向きを逆に設定
		m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;                           //向きの初期化
		CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion * 4.0f;  //弾の出る向きを調整
	}
	else if (CEnemyBullet::m_fAdditionPosY >= CEnemyBullet::InitAddItion * 3.0f && CEnemyBullet::m_fAdditionPosY <= 21.3f)
	{
		m_rot.y = D3DX_PI_ORI;                                         //向きを逆に設定
		m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;                           //向きの初期化
		CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion * 4.0f;  //弾の出る向きを調整
	}
}