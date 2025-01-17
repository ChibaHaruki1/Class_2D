//=====================================
//
//�{�X�̏���[boss.cpp]
//Auther:Haruki Chiba
//
//=====================================


//=====================================
//�C���N���[�h
#include "boss.h"
#include "manager.h"
#include <time.h>
#include <iostream>


//========================
//�R���X�g���N�^
//========================
CBoss::CBoss(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::BOSSHP, 0); //�{�X��HP�Q�[�W�̐���
	
	m_nCoolTime = 0;                              //�N�[���^�C���̏�����
	SetRandom(-1);                                //�����̏�����
	m_nSize = 0;                                  //�z�񐔂̏�����
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;  //�ǂ���ɂ��邩�̏�����

	m_nSaveData.clear();                          //�ۊǗp�x�N�^�[�̏�����
	m_nDataX.clear();                             //�����̈ʒu�̏�����
	m_nDataY.clear();                             //�����̈ʒu�̏�����
							                      
	m_bOneCreateFlag = false;                     //�����t���O�̏�����
}

//========================
//�f�X�g���N�^
//========================
CBoss::~CBoss()
{
	//�ۊǗp�x�N�^�[�̔j��
	m_nSaveData.clear();         //��������
	m_nSaveData.shrink_to_fit(); //���𖳂���

	//X���p�̃x�N�^�[�̔j��
	m_nDataX.clear();            //��������
	m_nDataX.shrink_to_fit();    //���𖳂���

	//Y���p�̃x�N�^�[�̔j��
	m_nDataY.clear();            //��������
	m_nDataY.shrink_to_fit();    //���𖳂���
}


//========================
//����������
//========================
HRESULT CBoss::Init()
{
	//�x�N�^�[�̍ő吔����
	for (int nCount = 0; nCount < MAX_VECTOR_SIZE; nCount++)
	{
		m_nSaveData.push_back((float)nCount); //nCount��float�^��cast���đ������
	}

	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //X���p�̕ϐ��ɑ��
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //Y���p�̕ϐ��ɑ��

	CCharacter::Init();                       //������
	CCharacter::LoodBoss();                   //���t�@�C���̓ǂݍ���
	CCharacter::SetMotionBoss(BOSSJUMP);      //���[�V�����̏����ݒ�
	return S_OK;                              //������Ԃ�
}


//========================
//�j������
//========================
void CBoss::Uninit()
{
	CCharacter::Uninit();  //�j������
}


//========================
//�X�V����
//========================
void CBoss::Update()
{
	CCharacter::UpdateBoss();    //���[�V�����̏����X�V����

	//�{�X�������Ă��鎞
	if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() > 0)
	{
		Collision();             //���E�ǂ���ɂ��邩�������Ă���֐����Ă�
		AttackPatternSelect();   //�U���̎�ނ�I������֐����Ă�
	}

	//�{�X�����񂾎�
	else if (CManager::GetInstance()->GetBossHPGage()->GetSaveSizeX() <= 0)
	{
		SetAddjustDieFrame()++;                                                     //���S�J�E���g�𑝂₷
		SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSDIE);                        //���[�V�����̎�ނ�ݒ�
		CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::BOSS, 0);  //�{�X�́i���g�j�C���X�^���X�̏��𖳂���

		//frame���K��l�ȏ�̎�
		if (GetDieFrame() >= DIE_FRAME)
		{
			CManager::SetMode(CScene::MODE::MODE_RESULT); //���U���g�ֈڍs
		}
	}

	CObjectX::Update();      //���N���X�̊��N���X��m_move���X�V
}


//====================================================================
//�����蔻��ō��E�̂ǂ���ɂ��邩���肷��֐�
//====================================================================
void CBoss::Collision()
{
	//�E���ɂ��鎞
	if (CollisionRightSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_RIGHT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�����ɂ��鎞
	else if (CollisionLeftSelectPlayer(CManager::GetInstance()->GetFinalBlock()) == true)
	{
		//���E�i���o�[���[�P�̎�
		if (m_nWhichSideNumber == INIT_WICHI_SIDE_NUMBER)
		{
			m_nWhichSideNumber = WICHI_SIDE_LEFT_NUMBER; //�ԍ���ݒ�
		}
	}

	//�{�X�ɓ���������
	if (CollisionBossPrts() == true)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += 100.0f;
	}
}


//==============================
//�U���̎�ނ�I�����鏈��
//==============================
void CBoss::AttackPatternSelect()
{
	//�U���̃N�[���^�C�����߂�����
	if (m_nCoolTime >= 120)
	{
		if (GetRandom() == 0)
		{
			AttackPattern();
		}
		else if (GetRandom() == 1)
		{
			AttackPattern001();
		}
		else if (GetRandom() == 2)
		{
			SpecialAttack();
		}
	}
	//�N�[���^�C����
	else
	{
		//�����̐���
		if (GetRandom() == -1)
		{
			//srand((unsigned)time(NULL));  // �����n���������
			//SetRandom(rand() % 3);
			SetRandom(1);
		}
		m_nCoolTime++;
	}
}

//==============================
//�s���ɂ܂�镨�̏�����
//==============================
void CBoss::StatusInit()
{
	CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSNEUTRAL); //���[�V�����̎�ނ�ݒ�

	//vector�̏�����
	m_nDataX.clear();          //���g�̑S�폜
	m_nDataX.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	m_nDataY.clear();          //���g�̑S�폜
	m_nDataY.shrink_to_fit();  //�L���p�V�e�B�̍폜�i�������j

	//vector�̒l�擾�i�R�s�[�j
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX)); //�����p�̈ʒu�̏�����
	std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY)); //�����p�̈ʒu�̏�����

	//�����o�ϐ��̏�����
	SetFrame(0);                                   //�t���[���̏�����
	m_nCoolTime = 0;                               //�N�[���^�C���̏�����
	SetRandom(-1);                                 //�����_�����̏�����
	m_nSize = 0;                                   //vector�̔z�񐔂�������
	m_nWhichSideNumber = INIT_WICHI_SIDE_NUMBER;   //���E�̂ǂ���ɋ��邩�̏�����
	m_bOneCreateFlag = false;                      //�Ռ��g���o���t���O�̏�����
}


//==============================
//�~���U��
//==============================
void CBoss::AttackPattern()
{
	GetFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= 30)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK); //���[�V�����̎�ނ�ݒ�
		
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 12.0f);  //�v���C���[�Ɍ������悤�ɐݒ�
	}

	else if (GetFrame()<=140)
	{
		GetRot().y = 0.0f;                                                     //�����̏�����
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSIMPACT); //���[�V�����̎�ނ�ݒ�
		GetPos().y += PopY() * MAX_MOVE_SPEED;                                 //��Ɉړ�
	}

	else if (GetFrame() <= 141)
	{
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));//Y���p�̈ʒu�̏�����
	}

	else if (GetFrame()<=170)
	{
		GetPos().y -= PopY() * MAX_MOVE_SPEED * 1.2f;                                      //���Ɉړ�
	}

	//�Ռ��g
	else  if (GetFrame() <=180)
	{
		//�t���O��off�̎�
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::IMPACT, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //�Ռ��g�𐶐�
			CManager::GetInstance()->GetImpact()->SetEffect(GetPos());                                                //�Ռ��g�G�t�F�N�g���Ă�

			m_bOneCreateFlag = true; //�t���O��On�ɂ��Ēʂ�Ȃ�����
		}
	}

	//�������C��
	else if (GetFrame() <= 300)
	{
		GetRot().y = -1.57f; //������߂�
	}

	//�I��
	else
	{
		GetRot().y = 0.0f; //�ʒu��������
		GetPos().y = 0.0f; //�ʒu��������
		StatusInit();   //������
	}
}

//==============================
//���U��
//==============================
void CBoss::AttackPattern001()
{
	GetFrame()++; //�t���[�����Z

	//���s��
	if (GetFrame() <= 40)
	{
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSWALK); //���[�V�����̎�ނ�ݒ�
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 8.0f);  //�v���C���[�Ɍ������悤�ɐݒ�
	}

	//���s��
	else if (GetFrame() <= 120)
	{
		if (GetRot().y >= 0.0f)
		{
			GetRot().y -= 0.1f;
		}
	}

	//��O�s��
	else if (GetFrame() <= 200)
	{
		GetRot().y = 0.0f;
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSATTACK); //���[�V�����̎�ނ�ݒ�
		GetPos().y += PopY() * 0.25f;
	}

	else if (GetFrame() <= 201)
	{
		CManagerBullet::Create(D3DXVECTOR3(GetPosPrtsBoss(17).x+100.0f, GetPosPrtsBoss(17).y-150.0f, GetPosPrtsBoss(17).z), D3DXVECTOR3(-sinf(GetRot().y) * 0, 0.0f, -cosf(GetRot().y) * 0), CManagerBullet::SET_BULLET_LIFE,CObject3D::TYPE::BOSSBULLET); //����
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataY));      //�����p�̈ʒu�̏�����
		std::copy(m_nSaveData.begin(), m_nSaveData.end(), std::back_inserter(m_nDataX));      //�����p�̈ʒu�̏�����
	}

	//��l�s��
	else if (GetFrame() <= 240)
	{
		GetPos().y -= PopY() * 0.25f;

		if (m_nWhichSideNumber == WICHI_SIDE_LEFT_NUMBER)
		{
			GetRot().y = 1.57f;
			GetMove().x -= PopX() *0.1f;
		}
		else if (m_nWhichSideNumber == WICHI_SIDE_RIGHT_NUMBER)
		{
			GetRot().y = -1.57f;
			GetMove().x += PopX() * 0.1f;
		}
	}

    //�I��
	else
	{
		GetRot().y = 0.0f;
		GetPos().y = 0.0f;
		StatusInit(); //������
	}
}


//=======================================================================================================================================================
//�K�E�Z�̏���
//=======================================================================================================================================================
void CBoss::SpecialAttack()
{
	GetFrame()++; //�t���[�����Z

	if (GetFrame() <= 10)
	{
		TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), 10.0f);  //�v���C���[�Ɍ������悤�ɐݒ�
		CCharacter::SetMotionBoss(CCharacter::BOSSMOTIONSTATE::BOSSACTION); //���[�V�����̎�ނ�ݒ�
	}

	else if (GetFrame() <= 60)
	{

	}

	else if (GetFrame() <= 61)
	{
		if (m_bOneCreateFlag == false)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::BOSSSPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�K�E�Z�̃G�t�F�N�g�̐���

			if (GetRot().y >= D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(2);                                           //�T�C�Y�̐ݒ�p�̔ԍ���n��
				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));

			}
			else if (GetRot().y <= -D3DX_PI_ORI)
			{
				CManager::GetInstance()->GetBossSpecialAttack()->SetRotNumber(1);                                           //�T�C�Y�̐ݒ�p�̔ԍ���n��

				//�ʒu���e�ɐݒ�
				CManager::GetInstance()->GetBossSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosPrtsBoss(17).x +300.0f ,
					GetPosPrtsBoss(17).y,
					GetPosPrtsBoss(17).z));
			}
			m_bOneCreateFlag = true;
		}
	}
	else if (GetFrame() <= 220)
	{

	}
	//�I��
	else
	{
		GetRot().y = 0.0f;
		GetPos().y = 0.0f;
		StatusInit(); //������
	}
}


//=======================================================================================================================================================
//  �X�^�b�N�\���̏���
//=======================================================================================================================================================

//============================
//�X�^�b�N��X�l���폜
//============================
float CBoss::PopX()
{
	if (m_nSize == 0)
	{
		m_nSize = m_nDataX.size() - 1;
	}

	else if (m_nSize > 0)
	{
		m_nSize--;
		m_nDataX.erase(m_nDataX.end() - 1); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataX[m_nSize];
	}
	return 0;
}


//============================
//�X�^�b�N��Y�l���폜
//============================
float CBoss::PopY()
{
	int Number = m_nDataY.size() - 1;

	if (Number > 0)
	{
		Number--;
		m_nDataY.erase(m_nDataY.end() - 1); //���ꂼ��̔z���X���̒l��Ԃ�
		return m_nDataY[Number];
	}
	return 0;
}


//========================
//�`�揈��
//========================
void CBoss::Draw()
{
	CCharacter::DrawBoss(MAX_BOSSPARTS);
}


//========================
//��������
//========================
CBoss* CBoss::Create(D3DXVECTOR3 pos )
{
	CBoss* pBoss = new CBoss(3); //���I�m��
	//pBoss->m_bUse = bUse;
	if (SUCCEEDED(pBoss->Init()))
	{
		if (pBoss != nullptr)
		{
			pBoss->GetPos() = pos;
			//pBoss->SetType(BOSS); //�^�C�v��PLAYER�ɐݒ�
			return pBoss; //�v���C���[�̏���Ԃ�
		}
	}

	return nullptr; //���Ȃ�
}