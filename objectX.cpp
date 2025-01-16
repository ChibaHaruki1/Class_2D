//=========================================
//
//3Dオブジェクトの処理[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================

//============================
//インクルード
#include "objectX.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//引数付きコンストラクタ
//=============================
CObjectX::CObjectX(int nPriority) : CObjectManagerX(nPriority)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr;
	}

	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_minPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
		m_maxPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
		m_ModelSizePrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
		m_posPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
	}

	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_ModelSizePrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
		m_posPrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）;
	}

	m_pVtxBuff = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pMat = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きを初期化する
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_pCollision = nullptr;
	m_nRandom = 0;
	m_nFrame = 0;
	m_nDieFrame = 0;
	m_fGravity = 0.0f;
	m_fAngle = 0.0f;
	m_aFileName = nullptr;
	m_bGravityFlag = true;  //重力ON
	m_bJumpFlag = false;
	m_bOneFlag = false;
	pUI = nullptr;
}


//=====================
//デストラクタ
//=====================
CObjectX::~CObjectX()
{
	//m_nObsessionCount = 0;

	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}


//=====================
//初期化処理
//=====================
HRESULT CObjectX::Init()
{
	m_pCollision = new CCollision(); //当たり判定の情報を取得する
	return S_OK;
}


//=====================
//終了処理
//=====================
void CObjectX::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	if (m_pMat != nullptr)
	{
		m_pMat = nullptr;
	}

	for (int nCntMat = 0; nCntMat < MAX_TEXTURE; nCntMat++)
	{
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = nullptr;
		}
	}
}


//=======================
//更新処理
//=======================
void CObjectX::Update()
{
	//位置を更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//移動量を更新（減衰させる）
	m_move.x += (0.0f - m_move.x) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_move.y += (0.0f - m_move.y) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_move.z += (0.0f - m_move.z) * 0.5f; //少ないほうが早く、ぬるぬる動く
}


//=======================
//描画処理
//=======================
void CObjectX::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアルの保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを収得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを収得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//int a = 0;
	for (int nCntMat1 = 0; nCntMat1 < (int)m_dwNumMat; nCntMat1++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		if (m_pMat[nCntMat1].pTextureFilename != nullptr)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat1]);
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat1]);
		}
		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat1);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===============================================================================================================================================================================
//重力処理
//===============================================================================================================================================================================
void CObjectX::Gravity()
{
	//重力ONの時
	if (m_bGravityFlag == true)
	{
		m_fGravity += MAX_GRAVITY_G; //重力加速度
		m_pos.y -= m_fGravity; //プレイヤーのｙposに重力加速度をつける
	}
}

//======================================================================================================================================
//位置の同期処理
//======================================================================================================================================
void CObjectX::GravityTogether()
{
	m_fGravity = 0.0f; //重力の初期化

	//一回のみ飛ぶ
	if (m_bJumpFlag == true)
	{
		m_bJumpFlag = false; //フラグをflaseにする
	}
	m_bGravityFlag = true; //重力を
}

//======================================================================================================================================
//ジャンプ処理
//======================================================================================================================================
void CObjectX::Junp(TYPE type,float fJumpPwer)
{
	//ジャンプフラグONの時
	if (m_bJumpFlag == true)
	{
		m_pos.y += fJumpPwer;  //pos.y値を加算させる

		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->CCharacter::SetMotion(CCharacter::MOTIONSTATE::JUMP);
			CManager::GetScene()->GetPlayerX()->m_bMotionType = true;
		}
		else if (type == TYPE::ENEMYINMOTION)
		{
			CManager::GetInstance()->GetEnemyInMotion(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			CManager::GetInstance()->GetEnemyInMotion(0)->SetMotionType(true);
			m_pos.x += 3.0f;
		}
		else if (type == TYPE::ENEMYINMOTION001)
		{
			CManager::GetInstance()->GetEnemyInMotion001(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			CManager::GetInstance()->GetEnemyInMotion001(0)->SetMotionType(true);
			m_pos.x += 3.0f;
		}
	}
	else
	{
		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->m_bMotionType = false;
		}
	}
	Gravity();  //重力処理を呼ぶ
}

//======================================================================================================================================
//引数で指定した目標に向かう処理
//======================================================================================================================================
void CObjectX::TargetHeadingTowards(CObjectX*pObject,float MAX_SPEED)
{
	//対角線の角度を算出する（目標ー自機）
	m_fAngle = atan2f(pObject->m_pos.x - m_pos.x, pObject->m_pos.z - m_pos.z);

	//移動処理
	m_move.x = sinf(m_fAngle) * MAX_SPEED;
	m_move.z = cosf(m_fAngle) * MAX_SPEED;
	m_rot.y = m_fAngle * -1; //向きをプレイヤーに合わせる
}


//================================================
//プレイヤーとボスの当たり判定
bool CObjectX::CollisionBossPrts()
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_BOSSPARTS-1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(m_posPrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), m_ModelSizePrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}

	
	return false;
}

//=============================
//継承objの右側の当たり判定
bool CObjectX::CollisionRightSelectPlayer(CObjectX* pObject)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
	
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBoxRight( pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), 
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}
	return false;
}

//=============================
//継承objの左側の当たり判定
bool CObjectX::CollisionLeftSelectPlayer(CObjectX* pObject)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBoxLeft(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
		}
	}
	return false;
}

//=============================
//プレイヤーと他の当たり判定
//=============================
bool CObjectX::CollisionPlayerSelect(CObjectX* pObject)
{
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0), pObject->m_ModelSize) == true)
	{
		return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}
	return false;
}

//=============================
//プレイヤーと敵の当たり判定
//=============================
bool CObjectX::CollisionPlayerInEnemy(CObjectX* pObject,float fMagnification)
{
	//プレイヤーと敵の当たり判定
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->GetPos(), CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0) * fMagnification, pObject->GetModelSizePrtsEnemy(0)* fMagnification) == true)
	{
		return true;               //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}
	return false;
}

//=============================
//テクスチャの情報を格納
//=============================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex, LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD NumMat, D3DXMATERIAL* pMat)
{
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_dwNumMat = NumMat;
	m_pMat = pMat;

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] == nullptr)
		{
			m_pTexture[nCntMat] = pTex;
			break;
		}
	}
}


//==============================
//Xファイルのサイズの取得
//==============================
void CObjectX::Size()
{
	int nNumVertex; //頂点数の格納
	DWORD dSIze; //頂点のフォーマットサイズ取得情報を保管する
	BYTE* pVtxByte; //頂点フォーマットの取得

	//頂点数を取得
	nNumVertex = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズ取得
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点メッシュのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//位置を代入するための変数
		D3DXVECTOR3 mtx;

		mtx = *(D3DXVECTOR3*)pVtxByte;

		if (mtx.x > max.x)
		{
			max.x = mtx.x;
		}
		else if (mtx.x < min.x)
		{
			min.x = mtx.x;
		}

		if (mtx.y > max.y)
		{
			max.y = mtx.y;
		}
		else if (mtx.y < min.y)
		{
			min.y = mtx.y;
		}

		if (mtx.z > max.z)
		{
			max.z = mtx.z;
		}
		else if (mtx.z < min.z)
		{
			min.z = mtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxByte += dSIze;
	}

	if (min.y < 0)
	{
		if (max.y < min.y)
		{
			max.y = min.y * -1.0f;
		}
		min.y = 0;
	}

	//オブジェクトのサイズを計算する
	m_ModelSize = max - min;
}


//==================================
//オブジェクトの配置
//==================================
void CObjectX::ObjectArrangement(CObjectX::TYPE type, CUI* pUI1)
{
	//Oキーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_O) == true)
	{
		if (pUI == nullptr)
		{
			pUI = CCreateInObject::Create(CObject3D::TYPE_UI::CLING);
			pUI->SetSize(50.0f, 0.0f, 50.0f);
		}

		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;
			CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++;

			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), m_pos);
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 180.0f, m_pos.z - 50.0f));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 170.0f, m_pos.z - 50.0f));

			//レーザーUIの生成と位置を同期させる
			pUI1 = CLaserCamare::Create(CObject3D::TYPE_UI::LASER);

			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //生成したオブジェクトの位置に同期
		}

		//地面用ブロックの時
		else if (type == CObjectX::TYPE::FIELDBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(m_pos.x + 600.0f, m_pos.y, m_pos.z));
		}
		//上がる用ブロックの時
		else if (type == CObjectX::TYPE::GOUPBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}
		//道用ブロックの時
		else if (type == CObjectX::TYPE::ROADBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}
		//壁兼道用ブロックの時
		else if (type == CObjectX::TYPE::WALLROADBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//壁兼道用001ブロックの時
		else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//小さい用ブロックの時
		else if (type == CObjectX::TYPE::SMALLBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
		//小さい用001ブロックの時
		else if (type == CObjectX::TYPE::SMALLBLOCK_001)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
		//上に設置する用ブロックの時
		else if (type == CObjectX::TYPE::UPWALLBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
	}

	//9キーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_9) == true)
	{
		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() <= 0)
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() = CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount();
			}
			else
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() -= 1;
			}

			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //生成したオブジェクトの位置に同期
		}
	}

	//8キーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_8) == true)
	{
		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			//配列カウントが、全体数かそれより大きい時
			if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() >= CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount())
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() = 0;
			}
			else
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() += 1;
			}
			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //生成したオブジェクトの位置に同期
		}
	}

	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() < CInstance::MAX_STAGEOBJECT && CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() > -1 && CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
		{
			/*if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y += 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y -= 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x += 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x -= 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}*/

			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				if (CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
				{
					CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->TextFileWrite(CObjectX::TYPE::TELEPHONPOLE, CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
						CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y,
						CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z);
					return;
				}
			}
		}
	}

	//地面用ブロックの時
	else if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		if (CManager::GetInstance()->GetFieldBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetFieldBlockCount() > -1 && CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				if (CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount()) != nullptr)
				{
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->TextFileWrite(CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x,
						CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y,
						CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().z, type);
					return;
				}
			}

		}
	}

	//上がる用ブロックの時
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		if (CManager::GetInstance()->GetGoUpBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetGoUpBlockCount() > -1 && CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				if (CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount()) != nullptr)
				{
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->TextFileWrite(CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x,
						CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y,
						CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().z, type);
					return;
				}
			}
		}
	}

	//道用ブロックの時
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		if (CManager::GetInstance()->GetRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetRoadBlockCount() > -1 && CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->TextFileWrite(CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().z, type);
				return;
			}
		}
	}

	//壁兼道用ブロックの時
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		if (CManager::GetInstance()->GetWallRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlockCount() > -1 && CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y += MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y -= MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x += MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x -= MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->TextFileWrite(CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().z, type);
				return;
			}
		}
	}

	//壁兼道用ブロック001の時
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		if (CManager::GetInstance()->GetWallRoadBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlock001Count() > -1 && CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y += MAX_OBJECTSPEED;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y -= MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x += MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x -= MAX_OBJECTSPEED
					;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->TextFileWrite(CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().z, type);
				return;
			}
		}
	}

	//小さい用ブロックの時
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		if (CManager::GetInstance()->GetSmallBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlockCount() > -1 && CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->TextFileWrite(CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().z, type);
				return;
			}
		}
	}

	//小さい用ブロックの時
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
	if (CManager::GetInstance()->GetSmallBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlock001Count() > -1 && CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count()) != nullptr)
	{
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
		{
			CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y += 1.0f;
		}
		else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
		{
			CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y -= 1.0f;
		}
		else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
		{
			CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x += 1.0f;
		}
		else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
		{
			CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x -= 1.0f;
		}
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
		{
			CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->TextFileWrite(CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x,
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y,
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().z, type);
			return;
		}
	}
	}

	//上壁用ブロックの時
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		if (CManager::GetInstance()->GetUpWallBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetUpWallBlockCount() > -1 && CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount()) != nullptr)
		{
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().y += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().y -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().x += 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().x -= 1.0f;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->TextFileWrite(CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().x,
					CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().y,
					CManager::GetInstance()->GetUpBlock(CManager::GetInstance()->GetUpWallBlockCount())->GetPos().z, type);
				return;
			}
		}
	}
}


//==================================
//Xファイルの読み込み
//==================================
HRESULT CObjectX::Lood()
{
	int nNumTexture = 0; //テクスチャの配列を進める為の変数
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイルがあるかどうか確かめる
	if (FAILED(D3DXLoadMeshFromX(m_aFileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_dwNumMat, &m_pMesh)))
	{
		return E_FAIL; //失敗を返す
	}

	//マテリアルデータへのポインタを収得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//マテリアル（テクスチャ）分回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pMat[nCntMat].pTextureFilename != nullptr)
		{//テクスチャファイルが存在する
			D3DXCreateTextureFromFile(pDevice, m_pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++;
		}
	}
	return S_OK; //成功を返す
}