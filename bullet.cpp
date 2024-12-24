//==================================
//
//�e�̏���[bullet.h]
//Auther:Chiba Haruki
//
//==================================

//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "bullet.h"


//==============================================================================================================
//==================================================3D�e�̏���==================================================
//==============================================================================================================

//=====================
//�R���X�g���N�^
//=====================
CManagerBullet::CManagerBullet(int nPriority) :CObject3D(nPriority)
{
	//�|�C���^�[������
	//m_aFileName = "data\\TEXTURE\\bullet001.png";
}

//=====================
//�f�X�g���N�^
//=====================
CManagerBullet::~CManagerBullet()
{

}


//=====================
//����������
//=====================
HRESULT CManagerBullet::Init()
{
	//���_�o�b�t�@�����Ɏ��s�����Ƃ�
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	m_pos.z = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_fSizeX = 40.0f;
	m_nAlpha = 255;
	SetSize(m_fSizeX, 40.0f, 0.0f);//�T�C�Y�̒���
	return S_OK;
}


//=====================
//�I������
//=====================
void CManagerBullet::Uninit()
{
	CObject3D::Uninit();  //���N���X�̔j������
}


//=====================
//�X�V����
//=====================
void CManagerBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EFFECT, 0, m_pos); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetCol(255, 160, 0, m_nAlpha); //�F�̐ݒ�

	if (m_nAlpha >= 1)
	{
		m_nAlpha -= 5;
	}

	m_nLife--; //�����J�E���g

	//�������s����
	if (m_nLife <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//=====================
//�`�揈��
//=====================
void CManagerBullet::Draw()
{
	//CObject3D::Draw();
}


//=====================
//�`�揈��(�r���{�[�h)
//=====================
void CManagerBullet::DrawNoml()
{
	CObject3D::DrawNoml();
}



//====================
//�e�̈ʒu�̐ݒ菈��
//====================
void CManagerBullet::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	m_pos = pos; //�e�̈ʒu�������Ɠ�������
	m_move = move; //�e�̈ړ��ʂ������Ɠ�������
	m_nLife = nLife; //������ݒ肷��
}


//=========================
//�e�̂̐���
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
		pBullet3D->m_aFileName = "data\\TEXTURE\\bullet001.png";
		pBullet3D->SetPos(pos, move, nLife);
		pBullet3D->Lood();
		return pBullet3D;
	}
	return nullptr;
}

//================================================================================================================================================
//�v���C���[�̒ʏ�e����
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CBullet3D::CBullet3D(int nPriority) : CManagerBullet(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CBullet3D::~CBullet3D()
{

}




//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBullet3D::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //���G�t�F�N�g���Ă�
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //�j�ЃG�t�F�N�g���Ă�


	CManager::GetInstance()->GetExplosion()->SetEffect(m_pos);                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
	CManager::GetInstance()->GetExplosion001()->SetEffect(m_pos);                                                     //�����G�t�F�N�g�̈ʒu��ݒ�
	CManager::GetInstance()->GetThander()->SetEffect(m_pos);                                                          //���G�t�F�N�g�̈ʒu��ݒ�
	CManager::GetInstance()->GetDebris()->SetEffect(m_pos);                                                           //�j�ЃG�t�F�N�g�̈ʒu��ݒ�
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBullet3D::CollisionOnObject()
{
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//�u���b�N�Ƃ̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize()) == true)
		{
			CallEffect(true);         //�G�t�F�N�g�������Ă�

			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
		}
	}

	//�G�̏�񂪂��鎞
	if (CManager::GetInstance()->GetEnemy000() != nullptr)
	{
		//�G�Ƃ̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetEnemy000()->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy000()->GetModelSize()*0.4f, m_fSizeX, 10) == true)
		{
			//CallEffect(true);         //�G�t�F�N�g�������Ă�
			CManager::GetInstance()->GetEnemy000()->GetLife() -= 1;   //�G�̃��C�t�����炷

			//�G�̃��C�t���O�ȉ��̎�
			if (CManager::GetInstance()->GetEnemy000()->GetLife() <= 0)
			{
				CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY, 0); //�|�C���^�[��nullptr�ɂ���
			}

			CObject3D::Release(); //���g�̉��
			return;               //�����𔲂���
		}
	}

	//�G001�̏�񂪂��鎞
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetEnemyCount() + 1; nCount1++)
	{
		if (CManager::GetInstance()->GetEnemy001(nCount1) != nullptr)
		{
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetInstance()->GetEnemy001(nCount1)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy001(nCount1)->GetModelSize() * 0.5f, m_fSizeX, 10) == true)
			{
				CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() -= 1; //�G�̃��C�t�����炷

				//�G�̃��C�t���O�ȉ��̎�
				if (CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY001, nCount1);  //�|�C���^�[��nullptr�ɂ���
				}

				CObject3D::Release(); //���g�̉��
				return;               //�����𔲂���
			}
		}
	}

	//�J�����̏㕔���̏�񂪂��鎞
	if (CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
	{
		//�J�����Ƃ̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos(),
			m_fSizeX, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
			CManager::GetInstance()->GetSurveillanceCameraUp(0)->GetModelSize()))
		{
			CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->Release(); //�J�����̏㕔���̍폜
			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SURVEILLANCECAMERAUP, 0);                                    //�|�C���^�[��nullptr�ɂ���
			CObject3D::Release(); //���g�̉��
			return;               //�����𔲂���
		}
	}

	//���[�V�����t���̓G001�̏�񂪂��鎞
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count()+1; nMotionInEnemy001++)
	{
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			for (int i = 0; i < CObjectX::MAX_ENEMYPARTS; i++)
			{
				//���[�V�����t���̓G001�̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(i),
					m_fSizeX, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePrtsEnemy(i) * 0.5f))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() -= 1;

					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{                                     
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //�|�C���^�[��nullptr�ɂ���
					}
					CObject3D::Release();     //���g�̉��
					return;                   //�����𔲂���
				}
			}
		}
	}

	//�{�X�̏�񂪂��鎞
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 2; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			if (CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->m_bCreateGun == true)
			{
				//�{�X�Ƃ̓����蔻��
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(m_pos, CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
					MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), m_fSizeX, nCount2))
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.01f; //�{�X��HP�Q�[�W�����炷

					//�w���parts��`�悵�Ȃ��{��������O�������ɂ���
					if (nCount2 == 6 || nCount2 == 7 || nCount2 == 8 || nCount2 == 9 || nCount2 == 11 || nCount2 == 12 || nCount2 == 13 || nCount2 == 15)
					{
						CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->m_bCreateGun = false;
					}

					CallEffect(true);         //�G�t�F�N�g�������Ă�
					CObject3D::Release();     //���g�̉��
					return;                   //�����𔲂���
				}
			}
		}
	}
}

//================================================================================================================================================
//�v���C���[�̕K�E�e����
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CSpecialBullet::CSpecialBullet(int nPriority) : CManagerBullet(nPriority)
{

}


//======================
//�R���X�g���N�^
//======================
CSpecialBullet::~CSpecialBullet()
{

}


//===========================
//�X�V����
//===========================
void CSpecialBullet::Update()
{
	if (CManager::GetScene()->GetPlayerX()->m_pModelPrts[18]->m_bCreateGun == true)
	{
		if (m_fSizeX <= 1000.0f)
		{
			m_fSizeX += 10.0f;
		}
		SetSize(m_fSizeX, 40.0f, 0.0f);//�T�C�Y�̒���
	}
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CSpecialBullet::CallEffect(bool bUse)
{
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //���G�t�F�N�g���Ă�
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //�j�ЃG�t�F�N�g���Ă�
	////CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //�j�ЃG�t�F�N�g���Ă�


	//CManager::GetInstance()->GetExplosion()->SetEffect(m_pos);                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetExplosion001()->SetEffect(m_pos);                                                     //�����G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetThander()->SetEffect(m_pos);                                                          //���G�t�F�N�g�̈ʒu��ݒ�
	//CManager::GetInstance()->GetDebris()->SetEffect(m_pos);                                                           //�j�ЃG�t�F�N�g�̈ʒu��ݒ�
	////CManager::GetInstance()->GetPillarOfFire()->SetEffect(m_pos);                                                           //�j�ЃG�t�F�N�g�̈ʒu��ݒ�
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CSpecialBullet::CollisionOnObject()
{
	//�{�X�̓����蔻��
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		for (int nCount2 = 0; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//�G�Ƃ̓����蔻��
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(m_pos, CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(nCount2),
				40, 40.0f, MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePrtsBoss(nCount2), m_fSizeX,nCount2))
			{
				if (CManager::GetScene()->GetPlayerX()->m_pModelPrts[18]->m_bCreateGun == false)
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.01f; //�{�X��HP�Q�[�W�����炷
					CallEffect(true);         //�G�t�F�N�g�������Ă�
					CObject3D::Release();     //���g�̉��
					return;                   //�����𔲂���
				}
				else
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= SCREEN_WIDTH * 0.0001f; //�{�X��HP�Q�[�W�����炷
				}
			}
		}
	}
}

//======================================================================================================================================================================
//�G�̒e�̏���
//======================================================================================================================================================================

//static�ϐ��̏�����
float CEnemyBullet::m_fAdditionPosY = InitAddItion;

//=====================
//�R���X�g���N�^
//=====================
CEnemyBullet::CEnemyBullet(int nPriority) :CManagerBullet(nPriority)
{
	m_nFrame = 0;
	m_nLife = 0;
	m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
}

//=====================
//�f�X�g���N�^
//=====================
CEnemyBullet::~CEnemyBullet()
{
	CObject3D::Uninit();
}


//=====================
//�X�V����
//=====================
void CEnemyBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EFFECT, 0, m_pos); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, m_nAlpha); //�F�̐ݒ�
	m_pos.y -= m_fAdditionPosY;

	//�A���t�@�l��0���傫����
	if (m_nAlpha > 0)
	{
		m_nAlpha -= 5;
	}

	m_nLife--; //�����J�E���g

	//�������s����
	if (m_nLife <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CEnemyBullet::CallEffect(bool bUse)
{
	
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CEnemyBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f, nCount2))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.05f; //HP�Q�[�W�����炷

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}


//======================================================================================================================================================================
//�{�X�̒e�̏���
//======================================================================================================================================================================

//static�ϐ��̏�����

//=====================
//�R���X�g���N�^
//=====================
CBossBullet::CBossBullet(int nPriority) :CManagerBullet(nPriority)
{
	m_nFrame = 0;
	m_nLife = 0;
	m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
}

//=====================
//�f�X�g���N�^
//=====================
CBossBullet::~CBossBullet()
{
	CObject3D::Uninit();
}


//=====================
//�X�V����
//=====================
void CBossBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EFFECT, 0, m_pos); //�G�t�F�N�g�i�O�Ձj�𐶐�����
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, m_nAlpha); //�F�̐ݒ�

	//�A���t�@�l��0���傫����
	if (m_nAlpha >0)
	{
		m_nAlpha -= 5;
	}

	m_nLife--; //�����J�E���g

	//�������s����
	if (m_nLife <= 0)
	{
		CallEffect(false);         //�G�t�F�N�g�������Ă�

		CObject3D::Release();      //���g�̉��
		return;                    //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}

	CObject3D::Update();           //���N���X�̍X�V�������Ă�
	CollisionOnObject();           //�����蔻�菈�����Ăԁ@�i�����𔲂���������Ō�ɌĂԁj
}


//===========================
//�G�t�F�N�g�̏������Ă�
//===========================
void CBossBullet::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //����̉��G�t�F�N�g���Ă�
	CManager::GetInstance()->GetPillarOfFire()->SetEffect(D3DXVECTOR3(m_pos.x, m_pos.y + 200.0f, m_pos.z));                 //����̉��G�t�F�N�g�̈ʒu��ݒ�
}


//===============================
//�I�u�W�F�N�g�Ƃ̓����蔻��
//===============================
void CBossBullet::CollisionOnObject()
{
	//�v���C���[�̃p�[�c������
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//�v���C���[�̓����蔻��
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(m_pos, CManager::GetScene()->GetPlayerX()->GetPosPrts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizePrts(nCount2), 0.0f, nCount2))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.05f; //HP�Q�[�W�����炷

			CallEffect(true);         //�G�t�F�N�g�������Ă�
			CObject3D::Release();     //���g�̉��
			return;                   //�����𔲂���
		}
	}
}