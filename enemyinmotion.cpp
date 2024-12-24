//=========================================================================
//
//���[�V�����t���̓G�̏���[enemyinmotion.cpp]
//Auther;Haruki Chiba
//
//=========================================================================

//==============================
//�C���N���[�h
#include "enemyinmotion.h"
#include "manager.h"
#include <time.h>

//=============================
//�R���X�g���N�^
//=============================
CManagerEnemyInMotion::CManagerEnemyInMotion(int nPriority) : CEnemyCharacter(nPriority)
{
	m_nJumpFrame = 0;
	m_aFileName = nullptr;
	JumpNumber = 0;
	JumpRecastTime = 0;
}

//=============================
//�f�X�g���N�^
//=============================
CManagerEnemyInMotion::~CManagerEnemyInMotion()
{

}

//=============================
//����������
//=============================
HRESULT CManagerEnemyInMotion::Init()
{
	//���_�o�b�t�@����
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}
	CEnemyCharacter::LoodEnemy(m_aFileName);
	CEnemyCharacter::SetMotionEnemy(ENEMYWALK);

	return S_OK;
}

//==============================
//�j������
//==============================
void CManagerEnemyInMotion::Uninit()
{
	CEnemyCharacter::Uninit();
}

//==============================
//�X�V����
//==============================
void CManagerEnemyInMotion::Update()
{
	
}

//==============================
//�`�揈��
//==============================
void CManagerEnemyInMotion::Draw()
{
	CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //�`�揈��
}

//==============================
//��������
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

	//��񂪂��鎞
	if (pEnemyInMotion != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pEnemyInMotion->Init()))
		{
			pEnemyInMotion->m_pos = pos; //�ʒu�̓���
			return pEnemyInMotion;       //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//====================================================================================================================================
//�G�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion::CEnemyInMotion(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	m_rot.y = D3DX_PI*-0.5f;
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion::~CEnemyInMotion()
{

}

//==============================
//�X�V����
//==============================
void CEnemyInMotion::Update()
{
	CEnemyCharacter::UpdateEnemy001();                                                       //���[�V�����̏����X�V����

	if (CObjectX::CollisionPlayerInEnemy(this,2.0f)==true)
	{
		CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //���[�V�����̎�ނ�ݒ�

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
			CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�
			TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //�v���C���[�Ɍ������悤�ɐݒ�
		}
	}

	Junp(TYPE::ENEMYINMOTION, 15.0f);                          //�W�����v�Əd�͏����֐����Ă�

	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//�n�ʗp�u���b�N�̏�񂪂��鎞
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (JumpNumber == -1)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, m_move) == true)
				{
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++;
						if (m_nJumpFrame >= 20)
						{
							m_JumpFlag = true; //��ԃt���O��ON�ɂ���

							m_nJumpFrame = 0;
							JumpNumber++;
							return;            //�����𔲂���
						}
					}
					else if (JumpRecastTime >= 0)
					{
						JumpRecastTime--;
					}

				}
				else
				{
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y���̈ʒu��ݒ�
					}
				}
			}

			else if (JumpNumber == 0)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, m_move) == true)
				{
					JumpRecastTime = 5;
					JumpNumber = -1;
					return;            //�����𔲂���
				}
				else
				{
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y���̈ʒu��ݒ�
					}
				}
			}

		}
	}

	CObjectX::Update(); //�ʒu�̍X�V
}


//====================================================================================================================================
//�G001�̏���
//====================================================================================================================================

//=============================
//�R���X�g���N�^
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	m_rot.y = D3DX_PI * -0.5f; //������ݒ�i�E�����j
	m_nHitFrame = 0;
	m_bHit = false;
	m_nLife = 5;
}

//=============================
//�f�X�g���N�^
//=============================
CEnemyInMotion001::~CEnemyInMotion001()
{

}


//==============================
//�X�V����
//==============================
void CEnemyInMotion001::Update()
{
	//�v���C���[������͈͓̔��ɗ�����X�V���������s����
	if (CObjectX::CollisionPlayerInEnemy(this, 10.0f) == true)
	{
		if (m_nLife > 0)
		{
			CEnemyCharacter::UpdateEnemy001();                                                    //���[�V�����̏����X�V����

			//�v���C���[�Ɠ������Ă��鎞
			if (CObjectX::CollisionPlayerInEnemy(this, 4.0f) == true)
			{
				CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //���[�V�����̎�ނ�ݒ�

				m_nFrame++;     //�e�����ۂ̃t���[���𑝂₷

				//�t���[�����K�萔�ɒB������
				if (m_nFrame >= 60)
				{
					CManagerBullet::Create(D3DXVECTOR3(this->m_posPrtsEnemy[4].x + 100.0f, this->m_posPrtsEnemy[4].y + 30.0f, this->m_posPrtsEnemy[4].z), D3DXVECTOR3(-sinf(m_rot.y) * MAX_BUULET_SPEED, 0.0f, -cosf(m_rot.y) * MAX_BUULET_SPEED),
						SET_BULLET_LIFE, CObject3D::ENEMYBULLET);
					m_nFrame = 0; //�t���[���̏�����
				}

				//�v���C���[���G�ɐڐG������
				if (CObjectX::CollisionPlayerInEnemy(this, 1.5f) == true)
				{
					m_bHit = true; //�������������On�ɂ���
				}

				//AdjustmentBulletAndRot(); //�v���C���[�ɑ΂���@�̂ƒe�̒����������Ă�
			}

			//�v���C���[�Ɠ������ĂȂ���
			else
			{
				//�����̏�����
				m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;
				CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion;

				//���ł��Ȃ��Ƃ�
				if (m_JumpFlag == false)
				{
					CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //���[�V�����̎�ނ�ݒ�

					//�W�����v�̃��L���X�g�^�C�����؂ꂽ��
					if (m_nJumpFrame == 0)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);        //�v���C���[�Ɍ������悤�ɐݒ�
					}
				}
			}

			//�v���C���[���G�ɓ���������
			if (m_bHit == true)
			{
				PlayerBloWwaway();               //�v���C���[�̐�����я������Ă�
			}

			Junp(TYPE::ENEMYINMOTION001, 15.0f); //�W�����v�Əd�͏����֐����Ă�
			WhenCollisionBlock();                //�n�ʗp�̃u���b�N�ɐG��Ă��鎞�̏���
			CObjectX::Update();                  //move�l�̍X�V
		}

		else if (m_nLife <= 0)
		{
			m_nDieFrame++;
			srand((unsigned)time(NULL));  //�����n���������
			if (m_nDieFrame <= 1)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //�����G�t�F�N�g�̈ʒu��ݒ�

				CManager::GetInstance()->GetExplosion()->SetEffect(m_pos);                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetEffect(m_pos);
			}
			else if (m_nDieFrame <= 20)
			{

			}

			else if (m_nDieFrame <= 21)
			{
				m_nRandom = -100 + rand() % 200;

				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //�����G�t�F�N�g�̈ʒu��ݒ�

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else if (m_nDieFrame <= 40)
			{

			}
			else if (m_nDieFrame <= 41)
			{

				m_nRandom = -100 + rand() % 200;
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj

				CManager::GetInstance()->GetExplosion()->SetSize(200.0f, 200.0f, 0.0f);                                           //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetSize(200.0f, 200.0f, 0.0);                                         //�����G�t�F�N�g�̈ʒu��ݒ�

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else if (m_nDieFrame <= 60)
			{

			}
			else if (m_nDieFrame <= 61)
			{

				m_nRandom = -100 + rand() % 200;
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //�����G�t�F�N�g���Ăԁi1�ځj
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�����G�t�F�N�g���Ăԁi2�ځj

				CManager::GetInstance()->GetExplosion()->SetSize(250.0f, 250.0f, 0.0f);                                           //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetSize(250.0f, 250.0f, 0.0);                                         //�����G�t�F�N�g�̈ʒu��ݒ�

				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));                                                        //�����G�t�F�N�g�̈ʒu��ݒ�
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(m_pos.x + m_nRandom, m_pos.y + m_nRandom, m_pos.z));
			}

			else
			{
				CManager::GetInstance()->GetGameScore()->AddScore(2000);                                                          //�X�R�A�����Z
				CObjectX::Release();
				return;
			}
		}
	}
}

//===============================================
//�v���C���[���G�ɓ���������
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //��������

	//Hitframe������l�ւ�������
	if (m_nHitFrame <= 20)
	{
		//�������̎�
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += 10.0f;  //�E�Ɉړ�
		}

		//�E�����̎�
		else if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= 10.0f;  //���Ɉړ�
		}
	}
	else
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= 
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * 0.001f; //HP�Q�[�W�����炷
		m_nHitFrame = 0; //hitframe��������
		m_bHit = false;  //�������������off�ɂ���
	}
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//�������̎�
	if (m_rot.y >= D3DX_PI_ORI)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetMuki()==1)
		{
			m_pModelPrtsEnemy[0]->m_rot.x += 0.01f;
			CEnemyBullet::m_fAdditionPosY -= 0.3f;
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			m_pModelPrtsEnemy[0]->m_rot.x -= 0.01f;
			CEnemyBullet::m_fAdditionPosY += 0.3f;
		}
	}

	//�E�����̎�
	else if (m_rot.y <= -D3DX_PI_ORI)
	{
		//�v���C���[�̌������������̎�
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 1)
		{
			m_pModelPrtsEnemy[0]->m_rot.x -= 0.01f; //
			CEnemyBullet::m_fAdditionPosY += 0.3f;
		}

		//�v���C���[�̌������E�����̎�
		if (CManager::GetScene()->GetPlayerX()->GetMuki() == 2)
		{
			m_pModelPrtsEnemy[0]->m_rot.x += 0.01f;
			CEnemyBullet::m_fAdditionPosY -= 0.3f;
		}
	}

	Correctionrot(); //�������C������֐����Ă�
}

//===============================================
//�v���C���[�ɑ΂���@�̂ƒe�̒�������
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//�n�ʗp�u���b�N�̏�񂪂��鎞
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (JumpNumber == -1)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, m_move) == true)
				{
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++;
						SetMotionEnemy(ENEMYJUMP);
						if (m_nJumpFrame >= 40)
						{
							m_JumpFlag = true; //��ԃt���O��ON�ɂ���
							m_nJumpFrame = 0;
							JumpNumber++;

							return;            //�����𔲂���
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
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y���̈ʒu��ݒ�
					}
				}
			}

			else if (JumpNumber == 0)
			{
				//���@�ƒn�ʗp�u���b�N������������
				if (m_pCollision->ColiisionBox1(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, m_move) == true)
				{
					JumpRecastTime = 5;
					JumpNumber = -1;
					return;            //�����𔲂���
				}
				else
				{
					//�n�ʗp�u���b�N�̏�ɏ���Ă��鎞
					if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
					{
						GravityTogether(); //�d�͂𓯊�������

						m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y���̈ʒu��ݒ�
					}
				}
			}
		}
	}

	//���p�u���b�N����
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
					m_pos.y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
			}
		}
	}

	//�ǌ����p�u���b�N����
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
					m_pos.y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
			}
		}
	}
	
	//�ǌ���001�p�u���b�N����
	for (int nCount4 = 0; nCount4 < CManager::GetInstance()->GetWallRoadBlock001Count() + 1; nCount4++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), m_ModelSize, CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), m_move) == true)
			{
				GravityTogether();
				m_pos.y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;//y���̈ʒu��ݒ�
				if (m_JumpFlag == true)
				{
					m_JumpFlag = false; //�t���O��flase�ɂ���
				}
			}
		}
	}

	//�������u���b�N����
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
					m_pos.y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
			}
		}
	}

}

//===============================================
//�������C��
//===============================================
void CEnemyInMotion001::Correctionrot()
{
	//�����Z���Ă����ϐ��̒l������̈ʒu�͈͓̔��̎�
	if (CEnemyBullet::m_fAdditionPosY <= -CEnemyBullet::InitAddItion && CEnemyBullet::m_fAdditionPosY >= -8.0f)
	{
		m_rot.y = -D3DX_PI_ORI;                                         //�������t�ɐݒ�
		m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;                           //�����̏�����
		CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion * 4.0f;  //�e�̏o������𒲐�
	}
	else if (CEnemyBullet::m_fAdditionPosY >= CEnemyBullet::InitAddItion * 3.0f && CEnemyBullet::m_fAdditionPosY <= 21.3f)
	{
		m_rot.y = D3DX_PI_ORI;                                         //�������t�ɐݒ�
		m_pModelPrtsEnemy[0]->m_rot.x = 0.0f;                           //�����̏�����
		CEnemyBullet::m_fAdditionPosY = CEnemyBullet::InitAddItion * 4.0f;  //�e�̏o������𒲐�
	}
}