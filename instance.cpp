//======================================================
//
//�C���X�^���X���Ǘ����鏈��[instance.cpp]
//Auther;HARUKI CHIBA
//
//======================================================

#include "instance.h"

//=======================
//�R���X�g���N�^
//=======================
CInstance::CInstance()
{
	//�I�u�W�F�N�g�̍ő吔����
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

	//�X�e�[�W�I�u�W�F�N�g�̍ő吔����
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;
		m_pSurveillanceCameraUp[nCount1] = nullptr;
		m_pSurveillanceCameraDown[nCount1] = nullptr;
	}

	//���ꂫ�̍ő吔����
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;
	}

	//�G�̍ő吔����
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;
	}

	//��ꂽ�ƕ���
	for (int nCount4=0 ;nCount4< MAX_BREAKHOUSE;nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;
	}

	//���[�V�����t���̓G�̕���
	for (int nCount5 = 0; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr;
		m_pEnemyInMotion001[nCount5] = nullptr;
	}

	//�C���X�^���X�̏�����
	m_pSpeceBattleShip000 = nullptr; //���̃X�e�[�W�֍s���I�u�W�F�N�g�̏�����
	m_pShop = nullptr;               //�X�̏�����
	m_pEffect = nullptr;             //�v���C���[�̒e�ɂ��G�t�F�N�g�̏�����
	m_pExplosion = nullptr;          //�����G�t�F�N�g�̏�����
	m_pExplosion001 = nullptr;       //�����G�t�F�N�g001�̏�����
	m_pThander = nullptr;            //���G�t�F�N�g�̏�����
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

	//2D�̃C���X�^���X�̏�����
	m_pShopScreen = nullptr;
	m_pBuyText = nullptr;
	m_pPlayerHPGage = nullptr;
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	//�RD�̏�����
	m_pFuelGage = nullptr;

	//���ꂽ���̏�����
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
//�f�X�g���N�^
//=======================
CInstance::~CInstance()
{

}


//=======================
//����������
//=======================
HRESULT CInstance::Init()
{
	return S_OK;
}


//=======================
//�j������
//=======================
void CInstance::Uninit()
{
	//�I�u�W�F�N�g�̍ő吔����
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

	//�X�e�[�W�I�u�W�F�N�g�̍ő吔����
	for (int nCount1 = 0; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;
		m_pSurveillanceCameraUp[nCount1] = nullptr;
		m_pSurveillanceCameraDown[nCount1] = nullptr;
	}

	//���ꂫ�̍ő吔����
	for (int nCount2 = 0; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;
	}

	//�G�̍ő吔����
	for (int nCount3 = 0; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;
	}

	//��ꂽ�ƕ���
	for (int nCount4 = 0; nCount4 < MAX_BREAKHOUSE; nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;
	}

	//���[�V�����t���̓G�̕���
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
//�G�̏��𖳂���
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
//nullptr�ɂ��������̂��w�肷�鏈��
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
//3D���f����nullptr�ɂ��������̂��w�肷�鏈��
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
//�QD��nullptr�ɂ��������̂��w�肷�鏈��
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
//�RD��nullptr�ɂ��������̂��w�肷�鏈��
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
//2D�̃C���X�^���X�𐶐����鏈��
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
//3D�̃C���X�^���X�𐶐����鏈��
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

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//X�I�u�W�F�N�g�̃C���X�^���X�𐶐����鏈��
//============================================================================================================================
CObjectX* CInstance::GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos)
{
	//�j�Ђ̐���
	if (type == CObjectX::TYPE::DEBRIS)
	{
		return m_pDebrisX[nNumber] = CDebrisX::Create(pos);
	}

	//�d���̐���
	else if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		return m_pTelephonPole[nNumber] = CStageObj::Create(pos, type);
	}

	//�Ď��J�����̏�̕����̐���
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		return m_pSurveillanceCameraUp[nNumber] = CStageObj::Create(pos, type);
	}

	//�Ď��J�����̉��̕����̐���
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERADOWN)
	{
		return m_pSurveillanceCameraDown[nNumber] = CStageObj::Create(pos, type);
	}

	//��ꂽ�Ƃ̐���
	else if (type == CObjectX::TYPE::BREAKHOUSE)
	{
		m_nBreakHouse++;
		return m_pBreakHouse[m_nBreakHouse] = CStageObj::Create(pos, type);
	}

	//�X�̐���
	else if (type == CObjectX::TYPE::SHOP)
	{
		return m_pShop = CStageObj::Create(pos, type);
	}

	//�G�̐���
	else if (type == CObjectX::TYPE::ENEMY)
	{
		return m_pEnemy000 = CManagerEnemy::Create(pos,type);
	}

	//�G001�̐���
	else if (type == CObjectX::TYPE::ENEMY001)
	{
		m_nEnemy++;
		return m_pEnemy001[m_nEnemy] = CManagerEnemy::Create(pos, type);
	}

	//���[�V�����t���̓G�̐���
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_nEnemyInMotion++;
		return m_pEnemyInMotion000[m_nEnemyInMotion] = CManagerEnemyInMotion::Create(pos,type);
	}

	//���[�V�����t���̓G001�̐���
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_nEnemyInMotion001++;
		return m_pEnemyInMotion001[m_nEnemyInMotion001] = CManagerEnemyInMotion::Create(pos, type);
	}

	//�{�X�̐���
	else if (type == CObjectX::TYPE::BOSS)
	{
		return m_pBoss = CBoss::Create(pos);
	}

	return nullptr; //����Ԃ�
}


//============================================================================================================================
//�u���b�N�̐�������
//============================================================================================================================
CObjectX* CInstance::CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//�n�ʗp�̃u���b�N�̐���
	if (type == CObjectX::STRATEGYTYPE::BLOCK000)
	{
		m_nNumFiledBlock++;
		return m_pFieldBlock[m_nNumFiledBlock] = CManagerBlock::Create(pos, type);
	}

	//�オ�邽�߂̃u���b�N�̐���
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
//���ꂫ�̐���
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

