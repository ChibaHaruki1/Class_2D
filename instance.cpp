//======================================================
//
//インスタンスを管理する処理[instance.cpp]
//Auther;HARUKI CHIBA
//
//======================================================

#include "instance.h"

//=======================
//コンストラクタ
//=======================
CInstance::CInstance()
{
	//オブジェクトの最大数分回す
	for (int nCount = 0; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;
		m_pGoUpBlock[nCount] = nullptr;
		m_pRoadBlock[nCount] = nullptr;
		m_pWallRoadBlock[nCount] = nullptr;
		m_pWallRoadBlock001[nCount] = nullptr;
		m_pSmallBlock[nCount] = nullptr;
		m_pSmallBlock001[nCount] = nullptr;
		m_pUpWallBlock[nCount] = nullptr;
		m_pDebrisX[nCount] = nullptr;
		m_pPraticles[nCount] = nullptr;
		m_pPraticles001[nCount] = nullptr;
	}

	//ステージオブジェクトの最大数分回す
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;
		m_pSurveillanceCameraUp[nCount1] = nullptr;
		m_pSurveillanceCameraDown[nCount1] = nullptr;
	}

	//がれきの最大数分回す
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;
	}

	//敵の最大数分回す
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;
	}

	//壊れた家分回す
	for (int nCount4=0 ;nCount4< MAX_BREAKHOUSE;nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;
	}

	//モーション付きの敵の分回す
	for (int nCount5 = 0; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr;
		m_pEnemyInMotion001[nCount5] = nullptr;
	}

	//インスタンスの初期化
	m_pSpeceBattleShip000 = nullptr; //次のステージへ行くオブジェクトの初期化
	m_pShop = nullptr;               //店の初期化
	m_pEffect = nullptr;             //プレイヤーの弾につくエフェクトの初期化
	m_pExplosion = nullptr;          //爆発エフェクトの初期化
	m_pExplosion001 = nullptr;       //爆発エフェクト001の初期化
	m_pThander = nullptr;            //雷エフェクトの初期化
	m_pFire = nullptr;
	m_pImpact = nullptr;
	m_pDebris = nullptr;
	m_pPillarOfFire = nullptr;
	m_pSepecialAttack = nullptr;
	m_pBossSpecialAttack = nullptr;
	m_pEnemy000 = nullptr;
	m_pBoss = nullptr;
	m_pFinalBlosk = nullptr;
	m_pFinalCeiling = nullptr;

	//2Dのインスタンスの初期化
	m_pShopScreen = nullptr;
	m_pBuyText = nullptr;
	m_pPlayerHPGage = nullptr;
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	//３Dの初期化
	m_pFuelGage = nullptr;

	//作られた数の初期化
	m_nGunCount = -1;
	m_nNumFiledBlock = -1;
	m_nNumGoUpBlock = -1;
	m_nRoadBlock = -1;
	m_nWallRoadBlock = -1;
	m_nWallRoadBlock001 = -1;
	m_nSmallBlock = -1;
	m_nSmallBlock001 = -1;
	m_nUpWallBlock = -1;
	m_nEnemy = -1;
	m_nEnemyInMotion = -1;
	m_nEnemyInMotion001 = -1;
	m_nWoodenBoard = -1;
	m_nBreakHouse = -1;
}


//=======================
//デストラクタ
//=======================
CInstance::~CInstance()
{

}


//=======================
//初期化処理
//=======================
HRESULT CInstance::Init()
{
	return S_OK;
}


//=======================
//破棄処理
//=======================
void CInstance::Uninit()
{
	//オブジェクトの最大数分回す
	for (int nCount = 0; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;
		m_pGoUpBlock[nCount] = nullptr;
		m_pRoadBlock[nCount] = nullptr;
		m_pWallRoadBlock[nCount] = nullptr;
		m_pWallRoadBlock001[nCount] = nullptr;
		m_pSmallBlock[nCount] = nullptr;
		m_pSmallBlock001[nCount] = nullptr;
		m_pUpWallBlock[nCount] = nullptr;
		m_pDebrisX[nCount] = nullptr;
		m_pPraticles[nCount] = nullptr;
		m_pPraticles001[nCount] = nullptr;
	}

	//ステージオブジェクトの最大数分回す
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;
		m_pSurveillanceCameraUp[nCount1] = nullptr;
		m_pSurveillanceCameraDown[nCount1] = nullptr;
	}

	//がれきの最大数分回す
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;
	}

	//敵の最大数分回す
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;
	}

	//壊れた家分回す
	for (int nCount4 = 0; nCount4 < MAX_BREAKHOUSE; nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;
	}

	//モーション付きの敵の分回す
	for (int nCount5 = 0; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr;
		m_pEnemyInMotion001[nCount5] = nullptr;
	}

	m_pSpeceBattleShip000 = nullptr;
	m_pShop = nullptr;
	m_pEffect = nullptr;
	m_pExplosion = nullptr;
	m_pThander = nullptr;
	m_pFire = nullptr;
	m_pImpact = nullptr;
	m_pExplosion001 = nullptr;
	m_pDebris = nullptr;
	m_pPillarOfFire = nullptr;
	m_pSepecialAttack = nullptr;
	m_pBossSpecialAttack = nullptr;
	m_pShopScreen = nullptr;
	m_pBuyText = nullptr;
	m_pEnemy000 = nullptr;
	m_pBoss = nullptr;
	m_pFinalBlosk = nullptr;
	m_pFinalCeiling = nullptr;
	m_pPlayerHPGage = nullptr;
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	m_pFuelGage = nullptr;
}

//============================================================================================================================
//敵の情報を無くす
//============================================================================================================================
void CInstance::DesignationUninitXEnemy(CObjectX::TYPE type, int nNumber)
{
	if (type == CObjectX::TYPE::ENEMY001)
	{
		m_pEnemy001[nNumber] = nullptr;
	}
	else if (type == CObjectX::TYPE::ENEMY)
	{
		m_pEnemy000 = nullptr;
	}
	else if(type==CObjectX::TYPE::BOSS)
	{
		m_pBoss = nullptr;
	}
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_pEnemyInMotion001[nNumber] = nullptr;
	}

}

//============================================================================================================================
//nullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninit(int nNumber)
{
	if (nNumber == 8)
	{
		for (int nCount8 = 0; nCount8 < MAX_OBJECT_DATA; nCount8++)
		{
			if (m_pPraticles001[nCount8] != nullptr)
			{
				m_pPraticles001[nCount8] = nullptr;
			}
		}
	}
}

//============================================================================================================================
//3Dモデルのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninitX(CObjectX::TYPE type, int nNumber)
{
	if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		m_pSurveillanceCameraUp[nNumber] = nullptr;
	}
	else if (type == CObjectX::TYPE::DEBRIS)
	{
		if (m_pDebrisX[nNumber] != nullptr)
		{
			m_pDebrisX[nNumber] = nullptr;
		}
	}
}


//============================================================================================================================
//２Dのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninit2D(CObject2D::TYPE type)
{
	if (type == CObject2D::TYPE::SCREEN)
	{
		m_pShopScreen = nullptr;
	}

	if (type == CObject2D::TYPE::BUYSENDTEXT)
	{
		m_pBuyText = nullptr;
	}
}


//============================================================================================================================
//３Dのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninit3D(CObject3D::TYPE type)
{
	if (type == CObject3D::TYPE::PRTICLES)
	{
		for (int nCount = 0; nCount < MAX_OBJECT_DATA; nCount++)
		{
			m_pPraticles[nCount] = nullptr;
		}
	}
	else if (type == CObject3D::TYPE::IMPACT)
	{
		m_pImpact = nullptr;
	}
}


//============================================================================================================================
//2Dのインスタンスを生成する処理
//============================================================================================================================
CObject2D* CInstance::GetCreateObjectInstnace2D(CObject2D::TYPE type, int nNumber)
{
	if (type == CObject2D::TYPE::SCREEN)
	{
		return m_pShopScreen = CShopScreen::Create();
	}
	else if (type == CObject2D::TYPE::BUYSENDTEXT)
	{
		return m_pBuyText = CBuyText::Create();
	}
	else if (type==CObject2D::TYPE::HP)
	{
		return m_pPlayerHPGage = CManagerGage::Create(type);
	}
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		return m_pBossHPGage = dynamic_cast<CBossHPGage*>(CManagerGage::Create(type));
	}
	else if (type == CObject2D::TYPE::SCORE)
	{
		m_pGameScore = CManagerScore::Create(CScene::MODE_GAME01, nNumber);
	}
	return nullptr;
}


//============================================================================================================================
//3Dのインスタンスを生成する処理
//============================================================================================================================
CObject3D* CInstance::GetCreateObjectInstnace(CObject3D::TYPE type, int nNumber, D3DXVECTOR3 pos)
{
	if (type == CObject3D::TYPE::PRTICLES)
	{
		return m_pPraticles[nNumber] = CParticles::Create(pos);
	}

	else if (type == CObject3D::TYPE::PRTICLES001)
	{
		return m_pPraticles001[nNumber] = CParticles001::Create(pos);
	}

	else if (type == CObject3D::TYPE::EFFECT)
	{
		return m_pEffect = CEffect::Create(pos);
	}

	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		return m_pExplosion = CManagerEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		return m_pExplosion001 = CManagerEffect::Create(pos,type);
	}

	else if (type == CObject3D::TYPE::THENDER)
	{
		return m_pThander = CManagerEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::FIRE)
	{
		return m_pFire = CManagerEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::IMPACT)
	{
		return m_pImpact = CManagerBossEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::DEBRIS)
	{
		return m_pDebris = CManagerEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		return m_pPillarOfFire = CManagerEffect::Create(pos, type);
	}

	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		return m_pSepecialAttack = dynamic_cast<CSpecialAttack*>(CManagerEffect::Create(pos, type));
	}

	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		return m_pBossSpecialAttack = CManagerBossEffect::Create(pos, type);
	}

	else if (type==CObject3D::TYPE::FUELGAGE)
	{
		return 	m_pFuelGage = CFuelGage::Create();

	}

	return nullptr; //無を返す
}


//============================================================================================================================
//Xオブジェクトのインスタンスを生成する処理
//============================================================================================================================
CObjectX* CInstance::GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos)
{
	//破片の生成
	if (type == CObjectX::TYPE::DEBRIS)
	{
		return m_pDebrisX[nNumber] = CDebrisX::Create(pos);
	}

	//電柱の生成
	else if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		return m_pTelephonPole[nNumber] = CStageObj::Create(pos, type);
	}

	//監視カメラの上の部分の生成
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		return m_pSurveillanceCameraUp[nNumber] = CStageObj::Create(pos, type);
	}

	//監視カメラの下の部分の生成
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERADOWN)
	{
		return m_pSurveillanceCameraDown[nNumber] = CStageObj::Create(pos, type);
	}

	//壊れた家の生成
	else if (type == CObjectX::TYPE::BREAKHOUSE)
	{
		m_nBreakHouse++;
		return m_pBreakHouse[m_nBreakHouse] = CStageObj::Create(pos, type);
	}

	//店の生成
	else if (type == CObjectX::TYPE::SHOP)
	{
		return m_pShop = CStageObj::Create(pos, type);
	}

	//敵の生成
	else if (type == CObjectX::TYPE::ENEMY)
	{
		return m_pEnemy000 = CManagerEnemy::Create(pos,type);
	}

	//敵001の生成
	else if (type == CObjectX::TYPE::ENEMY001)
	{
		m_nEnemy++;
		return m_pEnemy001[m_nEnemy] = CManagerEnemy::Create(pos, type);
	}

	//モーション付きの敵の生成
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_nEnemyInMotion++;
		return m_pEnemyInMotion000[m_nEnemyInMotion] = CManagerEnemyInMotion::Create(pos,type);
	}

	//モーション付きの敵001の生成
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_nEnemyInMotion001++;
		return m_pEnemyInMotion001[m_nEnemyInMotion001] = CManagerEnemyInMotion::Create(pos, type);
	}

	//ボスの生成
	else if (type == CObjectX::TYPE::BOSS)
	{
		return m_pBoss = CBoss::Create(pos);
	}

	return nullptr; //無を返す
}


//============================================================================================================================
//ブロックの生成処理
//============================================================================================================================
CObjectX* CInstance::CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//地面用のブロックの生成
	if (type == CObjectX::STRATEGYTYPE::BLOCK000)
	{
		m_nNumFiledBlock++;
		return m_pFieldBlock[m_nNumFiledBlock] = CManagerBlock::Create(pos, type);
	}

	//上がるためのブロックの生成
	else if (type == CObjectX::STRATEGYTYPE::BLOCK001)
	{
		m_nNumGoUpBlock++;
		return m_pGoUpBlock[m_nNumGoUpBlock] = CManagerBlock::Create(pos, type);
	}

	else if (type == CObjectX::STRATEGYTYPE::BLOCK002)
	{
		m_nRoadBlock++;
		return m_pRoadBlock[m_nRoadBlock] = CManagerBlock::Create(pos, type);
	}

	else if (type == CObjectX::STRATEGYTYPE::BLOCK003)
	{
		m_nWallRoadBlock++;
		return m_pWallRoadBlock[m_nWallRoadBlock] = CManagerBlock::Create(pos, type);
	}

	else if (type == CObjectX::STRATEGYTYPE::BLOCK003_001)
	{
		m_nWallRoadBlock001++;
		return m_pWallRoadBlock001[m_nWallRoadBlock001] = CManagerBlock::Create(pos, type);
	}
	else if (type == CObjectX::STRATEGYTYPE::BLOCK004)
	{
		m_nSmallBlock++;
		return m_pSmallBlock[m_nSmallBlock] = CManagerBlock::Create(pos, type);
	}
	else if (type == CObjectX::STRATEGYTYPE::BLOCK004_001)
	{
		m_nSmallBlock001++;
		return m_pSmallBlock001[m_nSmallBlock001] = CManagerBlock::Create(pos, type);
	}
	else if (type == CObjectX::STRATEGYTYPE::BLOCK005)
	{
		m_nUpWallBlock++;
		return m_pUpWallBlock[m_nUpWallBlock] = CManagerBlock::Create(pos, type);
	}

	else if (type == CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		return m_pSpeceBattleShip000 = CManagerBlock::Create(pos, type);
	}

	else if (type == CObjectX::STRATEGYTYPE::FINALBLOCK)
	{
		return m_pFinalBlosk = CManagerBlock::Create(pos,type);
	}

	else if (type == CObjectX::STRATEGYTYPE::FINALCEILLING)
	{
		return m_pFinalCeiling = CManagerBlock::Create(pos, type);
	}

	return nullptr;
}

//============================================================================================================================
//がれきの生成
//============================================================================================================================
CObjectX* CInstance::CreateRubble(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	if (type == CObjectX::STRATEGYTYPE::WODDENBORAD)
	{
		m_nWoodenBoard++;
		return m_pWoodenBoard[m_nWoodenBoard] = CManagerBlock::Create(pos,type);
	}

	return nullptr;
}

