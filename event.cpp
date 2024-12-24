//====================================================
//
//�X�e�[�W����event����������[enent.cpp]
//Auther:Haruki Chiba
//
//====================================================

//�C���N���[�h
#include "event.h"
#include "manager.h"
#include <time.h>


//============================
//�R���X�g���N�^
//============================
CEvent::CEvent()
{
	//�����ł���ő吔����
	for (int nCount = 0; nCount < CInstance::MAX_RUBBLE; nCount++)
	{
		m_fDropSpeed[nCount] = 0.0f;                //���Ƃ��X�s�[�h�̏�����
		m_fDropPosY[nCount] = (float)(nCount * 15); //���Ƃ��ʒu���ǂ�ǂ񍂂�����i�ς݂����点��ׁj
	}

	m_nCreateWoodenBoradsCounter = 0;       //�����������̏�����
	m_nRandomRotX = 0;                      //�����̌����̗����̏�����
	m_nRandomRotY = 0;                      //�����̌����̗����̏�����
	m_nPosY = 300.0f;                       //��������Y����pos�̏�����
	m_bOneflag = false;                     //��񂾂��ʂ��t���O�̏������i�g���ĂȂ��j
	m_bBossDirection = false;               //�{�X���o����񂾂�����t���O�̏������i�g���ĂȂ��j
	m_bOneCreate = false;

	mciSendStringA("open data\\BGM\\Bossbgm-Short.wav alias BGM", NULL, 0, NULL); //�ݒ肵���������J���i�Đ��͕ʁj
}


//============================
//�f�X�g���N�^
//============================
CEvent::~CEvent()
{
	mciSendStringA("close BGM", NULL, 0, NULL); //�ݒ肵�����������
}


//============================
//�X�V����
//============================
void CEvent::Update()
{
	//���݂̐��������ő吔��肷���Ȃ���
	if (m_nCreateWoodenBoradsCounter < CInstance::MAX_RUBBLE)
	{
		BossDirection();  //�{�X���̉��o�������Ă�
	}

	//�؂̔Q���������ꂽ��
	if (CManager::GetInstance()->GetWoodenBoardCount() > 0)
	{
		//�܂��S�ė����؂��ĂȂ���
		if (m_bOneflag == false)
		{
			DropObj();  //�؂̔Q�𗎂Ƃ��������Ă�
		}

		//�؂̔Q�𐶐�����������
		for (int a = 0; a < m_nCreateWoodenBoradsCounter; a++)
		{
			//�v���C���[�Ɩ؂̔̓����蔻��
			if (CManager::GetScene()->GetPlayerX()->CollisionPlayerSelect(CManager::GetInstance()->GetWoodenBoard(a)))
			{
				//A�L�[�������ꂽ��
				if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
				{
					CManager::GetScene()->GetPlayerX()->GetMove().x += MAX_MOVESPEED; //�v���C���[���t���։����o��
				}
			}
		}
	}
	//CreateEnemy();

}


//============================
//�v���C���[�̕K�E�Z
//============================
void CEvent::BossDirection()
{
	//�v���C���[����������Ă�����
	if (CManager::GetScene()->GetPlayerX() != nullptr)
	{
		//�v���C���[��pos������̏ꏊ�֍s������
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 3450)
		{
			//�{�X�̉��o���܂��̎�
			if (m_bBossDirection == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::BOSS, 0, D3DXVECTOR3(4500.0f, 0.0f, 0.0f)); //�{�X�𐶐�
				CManager::GetSound()->StopSound(CManager::GetSound()->SOUND_LABEL_BGM1);                                //�w��̉������~�߂�
				mciSendStringA("play BGM", NULL, 0, NULL);                                                              //�J���ꂽ�������Đ�����i�J����ĂȂ��Ɛ������Ȃ��j         
				m_bBossDirection = true;                                                                                //���o�t���O��true�ɂ��A�ʂ�Ȃ�����
			}

			//�J�����̈ʒu��ύX
			CManager::GetScene()->GetCamera()->GetAdjustmentPosZ() = 1400; //�J�����̂y���̒l��ݒ�
			CManager::GetScene()->GetCamera()->GetSaveF() = 400.0f;        //�J�����̂x���̒l��ݒ�

			m_nPosY += 10.0f;             //���Ƃ��ʒu�𑝂₷
			m_nRandomRotY = rand() % 31;  //�x���̌����𗐐��Œ���
			m_nRandomRotX = rand() % 15;  //�w���̌����𗐐��Œ���

			CManager::GetInstance()->CreateRubble(CObjectX::STRATEGYTYPE::WODDENBORAD, D3DXVECTOR3(3250.0f, m_nPosY, 0.0f));   //�؂̔Q���o��
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().y = (float)m_nRandomRotY * 0.1f;               //�x���̌�����ݒ�
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().x = (float)m_nRandomRotX * 0.1f;               //�w���̌�����ݒ�
			m_nCreateWoodenBoradsCounter++; //�z��J�E���g��i�߂�
		}
	}
}


//============================
//���Ƃ�����
//============================
void CEvent::DropObj()
{
	//�؂̔Q���������ꂽ������
	for (int nCount = 0; nCount < m_nCreateWoodenBoradsCounter; nCount++)
	{
		//���������؂̔Q�̈ʒu���ݒ肵���ʒu���傫���i�����j��
		if (CManager::GetInstance()->GetWoodenBoard(nCount)->GetPos().y >= m_fDropPosY[nCount])
		{
			m_fDropSpeed[nCount] += 0.07f;                                                         //���Ƃ����x�𑝂₷
			CManager::GetInstance()->GetWoodenBoard(nCount)->GetMove().y -= m_fDropSpeed[nCount];  //�؂̔Q�𗎂Ƃ�
		}

		//���������؂̔Q�̈ʒu���ݒ肵���ʒu��菬������
		else
		{
			//for���̃J�E���g���ő吔���s������
			if (nCount == CInstance::MAX_RUBBLE - 1)
			{
				m_bOneflag = true; //�t���O��ON�ɂ���
			}
		}
	}
}


//============================
//覐΂𗎂Ƃ�����
//============================
void CEvent::DropMeteorite()
{

}


//
//
//
void CEvent::CreateEnemy()
{
	if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 9500.0f)
	{
		if (m_bOneCreate == false)
		{
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMYINMOTION001, 0, D3DXVECTOR3(9500.0f, 5000.0f, 0.0f));    //���[�V�����t���̓G�̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMYINMOTION001, 0, D3DXVECTOR3(10000.0f, 5000.0f, 0.0f));    //���[�V�����t���̓G�̐���
			m_bOneCreate = true;
		}
	}
}