//=========================================
//
//3D�I�u�W�F�N�g�̏���[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================

//============================
//�C���N���[�h
#include "objectX.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//�����t���R���X�g���N�^
//=============================
CObjectX::CObjectX(int nPriority) : CObjectManagerX(nPriority)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr;
	}

	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_minPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
		m_maxPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
		m_ModelSizePrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
		m_posPrts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
	}

	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_ModelSizePrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
		m_posPrtsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j;
	}

	m_pVtxBuff = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_pMat = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu��������(�ʒu�𒲐��ł���j
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�������(�ړ����x�𒲐��ł���j
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����������������
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_pCollision = nullptr;
	m_nRandom = 0;
	m_nFrame = 0;
	m_nDieFrame = 0;
	m_Gravity = 0.0f;
	m_fAngle = 0.0f;
	m_aFileName = nullptr;
	m_GravityFlag = true;  //�d��ON
	m_JumpFlag = false;
	m_bOneFlag = false;
	pUI = nullptr;
}


//=====================
//�f�X�g���N�^
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
//����������
//=====================
HRESULT CObjectX::Init()
{
	m_pCollision = new CCollision(); //�����蔻��̏����擾����
	return S_OK;
}


//=====================
//�I������
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
//�X�V����
//=======================
void CObjectX::Update()
{
	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V�i����������j
	m_move.x += (0.0f - m_move.x) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_move.y += (0.0f - m_move.y) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
	m_move.z += (0.0f - m_move.z) * 0.5f; //���Ȃ��ق��������A�ʂ�ʂ铮��
}


//=======================
//�`�揈��
//=======================
void CObjectX::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ��p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^������
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//int a = 0;
	for (int nCntMat1 = 0; nCntMat1 < (int)m_dwNumMat; nCntMat1++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		if (m_pMat[nCntMat1].pTextureFilename != nullptr)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat1]);
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat1]);
		}
		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat1);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===============================================================================================================================================================================
//�d�͏���
//===============================================================================================================================================================================
void CObjectX::Gravity()
{
	//�d��ON�̎�
	if (m_GravityFlag == true)
	{
		m_Gravity += MAX_GRAVITY_G; //�d�͉����x
		m_pos.y -= m_Gravity; //�v���C���[�̂�pos�ɏd�͉����x������
	}
}

//======================================================================================================================================
//�ʒu�̓�������
//======================================================================================================================================
void CObjectX::GravityTogether()
{
	m_Gravity = 0.0f; //�d�͂̏�����

	//���̂ݔ��
	if (m_JumpFlag == true)
	{
		m_JumpFlag = false; //�t���O��flase�ɂ���
	}
	m_GravityFlag = true; //�d�͂�
}

//======================================================================================================================================
//�W�����v����
//======================================================================================================================================
void CObjectX::Junp(TYPE type,float fJumpPwer)
{
	//�W�����v�t���OON�̎�
	if (m_JumpFlag == true)
	{
		m_pos.y += fJumpPwer;  //pos.y�l�����Z������

		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->CCharacter::SetMotion(CCharacter::MOTIONSTATE::JUMP);
			CManager::GetScene()->GetPlayerX()->m_bMotionType = true;
		}
		else if (type == TYPE::ENEMYINMOTION)
		{
			CManager::GetInstance()->GetEnemyInMotion(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			CManager::GetInstance()->GetEnemyInMotion(0)->m_bMotionType = true;
			m_pos.x += 3.0f;
		}
		else if (type == TYPE::ENEMYINMOTION001)
		{
			CManager::GetInstance()->GetEnemyInMotion001(0)->CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			CManager::GetInstance()->GetEnemyInMotion001(0)->m_bMotionType = true;
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
	Gravity();  //�d�͏������Ă�
}

//======================================================================================================================================
//�����Ŏw�肵���ڕW�Ɍ���������
//======================================================================================================================================
void CObjectX::TargetHeadingTowards(CObjectX*pObject,float MAX_SPEED)
{
	//�Ίp���̊p�x���Z�o����i�ڕW�[���@�j
	m_fAngle = atan2f(pObject->m_pos.x - m_pos.x, pObject->m_pos.z - m_pos.z);

	//�ړ�����
	m_move.x = sinf(m_fAngle) * MAX_SPEED;
	m_move.z = cosf(m_fAngle) * MAX_SPEED;
	m_rot.y = m_fAngle * -1; //�������v���C���[�ɍ��킹��
}


//================================================
//�v���C���[�ƃ{�X�̓����蔻��
bool CObjectX::CollisionBossPrts()
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_BOSSPARTS-1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(m_posPrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), m_ModelSizePrtsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}

	
	return false;
}

//=============================
//�p��obj�̉E���̓����蔻��
bool CObjectX::CollisionRightSelectPlayer(CObjectX* pObject)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
	
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBoxRight( pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount), 
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}
	return false;
}

//=============================
//�p��obj�̍����̓����蔻��
bool CObjectX::CollisionLeftSelectPlayer(CObjectX* pObject)
{
	//�v���C���[�̊e�p�[�c���̓����蔻�菈��
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBoxLeft(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount)) == true)
		{
			return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}
	return false;
}

//=============================
//�v���C���[�Ƒ��̓����蔻��
//=============================
bool CObjectX::CollisionPlayerSelect(CObjectX* pObject)
{
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0), pObject->m_ModelSize) == true)
	{
		return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}
	return false;
}

//=============================
//�v���C���[�ƓG�̓����蔻��
//=============================
bool CObjectX::CollisionPlayerInEnemy(CObjectX* pObject,float fMagnification)
{
	//�v���C���[�ƓG�̓����蔻��
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->GetPos(), CManager::GetScene()->GetPlayerX()->GetModelSizePrts(0) * fMagnification, pObject->GetModelSizePrtsEnemy(0)* fMagnification) == true)
	{
		return true;               //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}
	return false;
}

//=============================
//�e�N�X�`���̏����i�[
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
//X�t�@�C���̃T�C�Y�̎擾
//==============================
void CObjectX::Size()
{
	int nNumVertex; //���_���̊i�[
	DWORD dSIze; //���_�̃t�H�[�}�b�g�T�C�Y�擾����ۊǂ���
	BYTE* pVtxByte; //���_�t�H�[�}�b�g�̎擾

	//���_�����擾
	nNumVertex = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_���b�V���̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//�ʒu�������邽�߂̕ϐ�
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

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
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

	//�I�u�W�F�N�g�̃T�C�Y���v�Z����
	m_ModelSize = max - min;
}


//==================================
//�I�u�W�F�N�g�̔z�u
//==================================
void CObjectX::ObjectArrangement(CObjectX::TYPE type, CUI* pUI1)
{
	//O�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_O) == true)
	{
		if (pUI == nullptr)
		{
			pUI = CCreateInObject::Create(CObject3D::TYPE_UI::INUI);
			pUI->SetSize(50.0f, 0.0f, 50.0f);
		}

		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;
			CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++;

			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), m_pos);
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 180.0f, m_pos.z - 50.0f));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 170.0f, m_pos.z - 50.0f));

			//���[�U�[UI�̐����ƈʒu�𓯊�������
			pUI1 = CLaserCamare::Create(CObject3D::TYPE_UI::LASER);

			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //���������I�u�W�F�N�g�̈ʒu�ɓ���
		}

		//�n�ʗp�u���b�N�̎�
		else if (type == CObjectX::TYPE::FIELDBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK000, D3DXVECTOR3(m_pos.x + 600.0f, m_pos.y, m_pos.z));
		}
		//�オ��p�u���b�N�̎�
		else if (type == CObjectX::TYPE::GOUPBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK001, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}
		//���p�u���b�N�̎�
		else if (type == CObjectX::TYPE::ROADBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK002, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}
		//�ǌ����p�u���b�N�̎�
		else if (type == CObjectX::TYPE::WALLROADBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//�ǌ����p001�u���b�N�̎�
		else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK003_001, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//�������p�u���b�N�̎�
		else if (type == CObjectX::TYPE::SMALLBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
		//�������p001�u���b�N�̎�
		else if (type == CObjectX::TYPE::SMALLBLOCK_001)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK004_001, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
		//��ɐݒu����p�u���b�N�̎�
		else if (type == CObjectX::TYPE::UPWALLBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK005, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
		//����u���b�N�̎�
		else if (type == CObjectX::TYPE::BREAKBLOCK)
		{
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::BLOCK006, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
	}

	//9�L�[�������ꂽ��
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

			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //���������I�u�W�F�N�g�̈ʒu�ɓ���
		}
	}

	//8�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_8) == true)
	{
		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			//�z��J�E���g���A�S�̐���������傫����
			if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() >= CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount())
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() = 0;
			}
			else
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() += 1;
			}
			pUI->GetPos() = CManager::GetInstance()->GetStageObj(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(); //���������I�u�W�F�N�g�̈ʒu�ɓ���
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

	//�n�ʗp�u���b�N�̎�
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

	//�オ��p�u���b�N�̎�
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

	//���p�u���b�N�̎�
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

	//�ǌ����p�u���b�N�̎�
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

	//�ǌ����p�u���b�N001�̎�
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

	//�������p�u���b�N�̎�
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

	//�������p�u���b�N�̎�
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

	//��Ǘp�u���b�N�̎�
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
//X�t�@�C���̓ǂݍ���
//==================================
HRESULT CObjectX::Lood()
{
	int nNumTexture = 0; //�e�N�X�`���̔z���i�߂�ׂ̕ϐ�
	CRenderer* pRenderer = CManager::GetRenderer(); //���ʂ��������������C���X�^���X���l��
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C�������邩�ǂ����m���߂�
	if (FAILED(D3DXLoadMeshFromX(m_aFileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_dwNumMat, &m_pMesh)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�}�e���A���f�[�^�ւ̃|�C���^������
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�}�e���A���i�e�N�X�`���j����
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pMat[nCntMat].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C�������݂���
			D3DXCreateTextureFromFile(pDevice, m_pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++;
		}
	}
	return S_OK; //������Ԃ�
}