//===================================
//
//���f���̐ݒ�����鏈��[player.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//�C���N���[�h
#include "main.h"
#include "player.x.h"
#include "rendererh.h"
#include "manager.h"
#include "collision.h"
#include "bullet.h"
#include "pos_object.h"
#include "enemy.h"
#include <time.h>
#include "DxLib.h"


//===================
//�R���X�g���N�^
//===================
CPlayerX::CPlayerX(int nPriority) : CCharacter(nPriority)
{
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0);

	m_GravityFlag = true;  //�d��ON
	m_JumpFlag = false;  //���ł��Ȃ��ɐݒ�
	m_Gravity = 0.0f;    //�d�͉����x�̏�����

	//�e�L�X�g�t�@�C���ɓo�^���鎞�̗t�z��ԍ��̏�����
	m_nFiledCount = -1;
	m_nTelephonCount = -1;

	//�e�L�X�g�t�@�C���ɓo�^���邵���S�Ă̔z��ԍ��̏�����
	m_nAllTelephonPoleCount = -1;
	m_nAllFiledCount = -1;

	m_ObjectNumber = 0;
	m_pMenyu = nullptr;
	m_pLaserUI = nullptr;

	m_nFrame = 0;
	m_nPraticlesCount = 0;
	m_nRandom = 0;
	m_nRandomCol = 0;            //������ۊǂ���ׂ̕ϐ�
	m_nDieFrame = 0;

	m_pTalkText = nullptr;
	m_pBuyText = nullptr;
	m_nSelectShopCount = 0;     //SHOP�őI��ł��镨
	m_nBuyOrSendCount = 0;
	m_pSelectGage = nullptr;
	m_pSelectGage001 = nullptr;
	SpecialAttack = false;
	m_PlayerState = NORMAI_MODE;
	m_FlagSate = NORMAI_MODE;
	m_nAlpha = 255;

	m_nMotionFrame = 0;
	m_nMotionFrame001 = 0;
	m_bNextStage = false;

	//������ԏ����̏�����
	m_nFlayFrame = 0;
	m_bFly = false;

	m_nDieRandom = 0;
	m_nMuki = 0;
	m_nSpecialAttackCount = 0;
	m_bOneCreate = false;

	//pSound = CManager::GetSound();
	//mciSendStringA("open tankBgm.wav alias BGM", NULL, 0, NULL);
}


//===================
//�f�X�g���N�^
//===================
CPlayerX::~CPlayerX()
{
	//mciSendStringA("close BGM", NULL, 0, NULL);
}


//====================
//����������
//====================
HRESULT CPlayerX::Init()
{
	CCharacter::Init();                        //�������������Ă�
	CCharacter::Lood();                        //�e�L�X�g�t�@�C����ǂݍ��ޏ���
	CCharacter::SetMotion(WALK);               //���[�V�����̐ݒ�
	m_rot.y = D3DX_PI*-0.5f;                   //�����̒����i�E�����j
	m_pModelPrts[18]->m_bCreateGun = false;    //�p�[�c�̏e�������\���ɐݒ�
	m_pos.x = 000.0f;                          //�ʒu�̒���
	CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_BGM1); //BDM�𗬂�
	m_nLife = 1;                               //���g�̃��C�t
	return S_OK; //������Ԃ�
}

//==================
//�I������
//=================
void CPlayerX::Uninit()
{
	/*m_nDieRandom.clear();
	m_nDieRandom.shrink_to_fit();*/
	//instance��������
	InstanceMakeNull();

	CCharacter::Uninit();
}

//===============================================================================================================================================================================
//instance��nullptr�ɂ���
//===============================================================================================================================================================================
void CPlayerX::InstanceMakeNull()
{

	//
	if (m_pTalkText != nullptr)
	{
		m_pTalkText = nullptr;
	}

	//
	if (m_pMenyu != nullptr)
	{
		m_pMenyu = nullptr;
	}


	//
	if (m_pBuyText != nullptr)
	{
		m_pBuyText = nullptr;
	}

	//
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage = nullptr;
	}

	//
	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001 = nullptr;
	}
}

//
//
//
void CPlayerX::ShopInstanceMakeNullptr()
{
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage->Release();
		m_pSelectGage = nullptr;
	}

	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001->Release();
		m_pSelectGage001 = nullptr;
	}

	if (m_pBuyText != nullptr)
	{
		m_pBuyText->Release();
		m_pBuyText = nullptr;
	}

	if (m_pMenyu != nullptr)
	{
		m_pMenyu->Release();
		m_pMenyu = nullptr;
	}

	if (CManager::GetInstance()->GetShopScreen() != nullptr)
	{
		CManager::GetInstance()->GetShopScreen()->Release();
		CManager::GetInstance()->DesignationUninit2D(CObject2D::SCREEN);
	}
}


//===============================================================================================================================================================================
//�X�V����
//===============================================================================================================================================================================
void CPlayerX::Update()
{
	//�����Ă��鎞
	if (m_nLife == 1)
	{
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= 9000.0f)
		{
			if (m_bOneCreate == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMYINMOTION001, 0, D3DXVECTOR3(9500.0f, 4500.0f, 0.0f));    //���[�V�����t���̓G�̐���
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::ENEMYINMOTION001, 0, D3DXVECTOR3(12000.0f, 1500.0f, 0.0f));    //���[�V�����t���̓G�̐���
				m_bOneCreate = true;
			}
		}

		CCharacter::UpdatePlayer();  //���[�V�����̍X�V
		HitAttack();                 //����̍U�����󂯂����̏����֐����Ă�

		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			m_nSpecialAttackCount++;
		}

		//����scene�ɍs���t���O��On�̎�
		if (m_bNextStage == true)
		{
			SceneMode(1); //scene�̐؂�ւ�
			return;		  //�����𔲂���
		}

		//�Q�[�W��manager����������Ă�����
		if (CManager::GetInstance()->GetPlayerHPGage() != nullptr)
		{
			//HP�Q�[�W���O�ȉ��̎�
			if (CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() <= 0)
			{
				CManager::GetInstance()->GetPlayerHPGage()->GetSaveSizeX() = 0.0f;
				m_nLife = 0; //���C�t���O�ɐݒ�Ŏ��S����ɂ���
			}
		}

		//�������Ă��Ȃ���
		if (m_PlayerState == NORMAI_MODE)
		{
			NormalStateSummarizeFunction(); //��p�̏������Ă�
		}
		//SHOP�Ŕ����������Ă��鎞
		else if (m_PlayerState == SHOP_MODE || m_PlayerState == BUY_MODE)
		{
			ShopStateSummarizeFunction();   //��p�̏������Ă�
		}

		CObjectX::Update(); //���N���X�̊��N���X�̍X�V�������Ă�
	}

	//���񂾎�
	else if (m_nLife == 0)
	{
		m_nDieFrame++;                //���S�t���[���𑝂₷
		m_pos.y = -50.0f;             //�ʒu��Ⴍ����
		srand((unsigned)time(NULL));  //�����n���������

		//�����������ĂȂ���
		if (m_nDieRandom == 0)
		{
			m_nDieRandom = -1 + rand() % 3; //����������
		}
		m_pModelPrts[0]->m_pos += D3DXVECTOR3(m_nDieFrame * 0.1f * m_nDieRandom, 0.0f, m_nDieFrame * 0.1f * m_nDieRandom);

		CCharacter::Update();  //���N���X�̍X�V�������Ă�
		SetMotion(DIE);        //���[�V���������S�ɐݒ肷��

		//�P�b*�w��b
		if (m_nDieFrame >= 60 * 3)
		{
			SceneMode(3); //�V�[���̐ݒ�
			return;       //�����𔲂���
		}
	}
	SceneMode(2);         //�V�[����I��
}


//==================================================================================================================================================
//������я���
//==================================================================================================================================================
void CPlayerX::BlowAway()
{
	m_nFlayFrame++;
	CCharacter::SetMotion(BLOWAWAY);

	if (m_nFlayFrame <= 40)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += 20.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().y += 30.0f;
	}
	else if (m_nFlayFrame <= 90)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().y += 10.0f;
		CManager::GetScene()->GetPlayerX()->GetPos().x += 20.0f;
	}
	else
	{
		
		m_bFly = false;
		m_nFlayFrame = 0;
	}
}


//==================================================================================================================================================
//����̍U�����󂯂����̏���
//==================================================================================================================================================
void CPlayerX::HitAttack()
{
	//�Ռ��j�G�t�F�N�g�̃C���X�^���X��񂪂��鎞
	if (CManager::GetInstance()->GetImpact() != nullptr)
	{
		//���������t���O��ON�̎�
		if (CManager::GetInstance()->GetImpact()->GetFly() == true)
		{
			m_bFly = true; //���
		}
	}

	//��ԃt���O��ON�̎�
	if (m_bFly == true)
	{
		BlowAway();  //������я������Ă�
	}
}


//==================================================================================================================================================
//����scene����
//==================================================================================================================================================
void CPlayerX::SceneMode(int nType)
{
	//���̃X�e�[�W�ɍs���p�i�Q�[�����[�v�j
	if (nType == 1)
	{
		m_bNextStage = false;
		switch (CManager::GetScene()->GetMode())
		{
		case CScene::MODE_GAME01:
			CManager::SetMode(CScene::MODE_GAME02); //��ʑJ��
			return; //�����𔲂���

		case CScene::MODE_GAME02:
			CManager::SetMode(CScene::MODE_RESULT); //��ʑJ��
			return; //�����𔲂���
		}
	}

	//�f�o�b�N�p
	else if (nType == 2)
	{
		//Enter�L�[�������ꂽ���i�f�o�b�N�p�j
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true)
		{
			m_bNextStage = false;
			switch (CManager::GetScene()->GetMode())
			{
			case CScene::MODE_GAME01:
				CManager::SetMode(CScene::MODE_GAME02); //��ʑJ��
				return; //�����𔲂���

			case CScene::MODE_GAME02:
				CManager::SetMode(CScene::MODE_RESULT); //��ʑJ��
				return; //�����𔲂���
			}
		}
	}

	//���S�������p
	else if (nType == 3)
	{
		m_bNextStage = false;
		CManager::SetMode(CScene::MODE_GAMEOVER); //��ʑJ��
		return; //�����𔲂���
	}
}


//===============================================================================================================================================================================
//�ʏ��Ԏ��̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::NormalStateSummarizeFunction()
{
	if (m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
	{
		Praticles();        //�p�[�e�B�N���̐��������֐����Ă�

		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_CHAGE); //BDM�𗬂�
		}
	}
	BlockJudgement();   //�I�u�W�F�N�g�Ƃ̓����蔻�菈���֐����Ă�

	if (SpecialAttack == false)
	{
		KeySet();           //�L�[���Ƃ̏����֐����Ă�
	}
	else
	{
		if (m_nMotionFrame >= 0)
		{
			m_nMotionFrame--;
		}

		if (m_nMotionFrame001 >= 0)
		{
			m_nMotionFrame001--;
		}

		else if(m_nMotionFrame<=0&& m_nMotionFrame001<=0)
		{
			SpecialAttack = false;
		}
	}
	Junp(TYPE::PLAYER, 10.0f);             //�W�����v�Əd�͏����֐����Ă�
}


//===============================================================================================================================================================================
//���������̊֐����܂Ƃ߂�֐�����
//===============================================================================================================================================================================
void CPlayerX::ShopStateSummarizeFunction()
{
	BlockJudgement();
	ShopKeySet();            //�L�[���Ƃ̏���
}


//===============================================================================================================================================================================
//�����_������
//===============================================================================================================================================================================
void CPlayerX::Random()
{
	//�ŏ��l�{rand()%�ŏ��l���牽�����₷���@�i�T�������灓�U��������@�T�A�U�A�V�A�W�A�X�A�P�O�̍��v�U�ɂȂ�j
	m_nRandom = -50 + rand() % 100; //�S�`�U�̐��l���o���i�͈͎w��j
	m_nRandomCol = rand() % 255; //�S�`�U�̐��l���o���i�͈͎w��j
}


//===============================================================================================================================================================================
//�p�[�e�B�N�����o������
//===============================================================================================================================================================================
void CPlayerX::Praticles()
{
	Random();            //�����_���������Ă�
	m_nFrame++;       //�t���[�������Z�����Ă���

	//�t���[��������̐��l�܂ōs������
	if (m_nFrame >= 4)
	{
		m_nFrame = 0; //�t���[��������������

		//�z��̍ő吔���ő吔��艺����
		if (m_nPraticlesCount >= 0 && m_nPraticlesCount <= CInstance::MAX_OBJECT_DATA - 1)
		{
			CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)m_pos.x + m_nRandom, m_pos.y+50.0f, 0.0f)); //�p�[�e�B�N���̐�������
			CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, 0, 0, m_nAlpha);
			m_nPraticlesCount++; //�z���i�߂�
		}

		//�ő吔�ɓ˓�
		else
		{
			CManager::GetInstance()->DesignationUninit(8);
			m_nPraticlesCount = 0; //�z��J�E���g������������
		}
	}
}


//===============================================================================================================================================================================
//�d���̔z�u����
//===============================================================================================================================================================================
void CPlayerX::ObjectArrangementTelephonPole()
{
	ObjectArrangement(CObjectX::TYPE::TELEPHONPOLE,m_pLaserUI);
}



//===============================================================================================================================================================================
//�L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::KeySet()
{
	//�K�E�Z�̔���
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_K) == true|| CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_RB)==true)
	{
		//���킪����ꂽ��
		if (m_pModelPrts[18]->m_bCreateGun == true&& m_nSpecialAttackCount>= MAX_SPECIALATTACKCOUNT)
		{
			SpecialAttack = true;      
			m_nSpecialAttackCount = 0;
			//�E�����̎�
			if (m_rot.y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�K�E�Z�̃G�t�F�N�g�̐���
				m_nMotionFrame = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                       //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 1;                                               //�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(m_posPrts[17].x + 220.0f,                   //�G�t�F�N�g�̏o���ʒu��ݒ�
					m_posPrts[17].y, m_posPrts[17].z));
			}

			//�������̎�
			else if (m_rot.y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2)
			{
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::SPECIALATTACK, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�K�E�Z�̃G�t�F�N�g�̐���
				m_nMotionFrame001 = CManager::GetInstance()->GetSpecialAttack()->GetLife();                                    //���[�V�����̃��C�t�𓯊�������
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = 2;											   //�T�C�Y�̐ݒ�p�̔ԍ���n��
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(m_posPrts[17].x - 50.0f, 				   //�G�t�F�N�g�̏o���ʒu��ݒ�
					m_posPrts[17].y, m_posPrts[17].z));
			}
		}
	}

	//A�L�[�������ꂽ���i�����ꑱ�������j
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true || CManager::GetJyoPad()->GetJoypadPress(JOYKEY_LEFT) == true)
	{
		m_rot.y = CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2; //�J�����̌����ɍ��킹�Č���
		m_move.x -= sinf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_move.z -= cosf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_nMuki = 1;
		//�����ĂȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//D�L�[�������ꂽ���i�����ꑱ�������j
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true || CManager::GetJyoPad()->GetJoypadPress(JOYKEY_RIGHT) == true)
	{
		m_rot.y = CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2; //�J�����̌����ɍ��킹�Č���
		m_move.x += sinf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_move.z += cosf(D3DX_PI / 2 + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED;
		m_nMuki = 2;
		//�����ĂȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //�������[�V����
		}
	}

	//���̑�
	else
	{
		//�����ĂȂ����Ɛ������łȂ���
		if (m_nMotionFrame <= 0 && m_nMotionFrame001 <= 0 && m_bFly == false)
		{
			SpecialAttack = false;
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::NEUTRAL); //�ҋ@���[�V����
		}
	}

	//space�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_SPACE) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_B) == true)
	{
		CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_SHOT); //BDM�𗬂�
		if (m_rot.y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI / 2)
		{
			m_nMotionFrame = 60;
			CManagerBullet::Create(D3DXVECTOR3(m_posPrts[17].x + 240.0f, m_posPrts[17].y, m_posPrts[17].z), D3DXVECTOR3(-sinf(m_rot.y) * MAX_BUULET_SPEED, 0.0f, 0.0f), SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}

		else if (m_rot.y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI / 2)
		{
			m_nMotionFrame001 = 60;
			CManagerBullet::Create(D3DXVECTOR3(m_posPrts[17].x - 50.0f, m_posPrts[17].y, m_posPrts[17].z), D3DXVECTOR3(-sinf(m_rot.y) * MAX_BUULET_SPEED, 0.0f, -cosf(m_rot.y) * MAX_BUULET_SPEED), SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //����
		}
	}

	//X�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_X) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true)
	{
		m_JumpFlag = true;
		CFuelGage::m_bUse = true;
	}
	else if (m_JumpFlag == true)
	{
		if (CManager::GetInstance()->GetFuelGage() != nullptr)
		{
			if (CManager::GetInstance()->GetFuelGage()->GetSizeY() > 0.0f && CFuelGage::m_bUse == true)
			{
				//X�L�[�������ꂽ��
				if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_X) == true || CManager::GetJyoPad()->GetJoypadPress(JOYKEY_A) == true)
				{
					m_move.y += 1.0f;
					m_GravityFlag = false;

					if (m_Gravity > 1.0f)
					{
						m_Gravity = 1.0f;
					}
				}
				else
				{
					CFuelGage::m_bUse = false;
					m_GravityFlag = true;
				}
			}
			else if (CManager::GetInstance()->GetFuelGage()->GetSizeY() <= 0.0f)
			{
				m_GravityFlag = true;
				CFuelGage::m_bUse = false;
				return;
			}
		}
	}


	//�E���̏e�Ɋւ���t���[���̏���
	if (m_nMotionFrame >= 0)
	{
		m_nMotionFrame--;
		SetMotion(CCharacter::MOTIONSTATE::ACTION);
	}
	//�����̏e�Ɋւ���t���[������
	if (m_nMotionFrame001 >= 0)
	{
		m_nMotionFrame001--;
		SetMotion(CCharacter::MOTIONSTATE::ACTION);
	}
}


//===============================================================================================================================================================================
//�V���b�v���̃L�[���Ƃ̏������܂Ƃ߂�֐�
//===============================================================================================================================================================================
void CPlayerX::ShopKeySet()
{
	//=======================================================================================================================================================
	//�ʏ��Ԃ̎�
	//=======================================================================================================================================================
	if (m_PlayerState == NORMAI_MODE)
	{
		//
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_Y) == true)
		{
			//�I���Q�[�W�P�ڂ𐶐�����
			if (m_pSelectGage == nullptr)
			{
				m_pSelectGage = CSelectGage::Create();
			}

			//�I���Q�[�W��ڂ𐶐�����
			if (m_pSelectGage001 == nullptr)
			{
				m_pSelectGage001 = CSelectGage001::Create();
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //��ڂ̃Q�[�W�̑傫���ɍ��킹��
			}

			//�w�iUI�𐶐�����
			if (CManager::GetInstance()->GetShopScreen() == nullptr)
			{
				CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCREEN, 0);
			}

			//���������邩��UI�𐶐�����
			if (m_pBuyText == nullptr)
			{
				m_pBuyText = CBuyText::Create();
			}

			m_PlayerState = SHOP_MODE; //���[�h��ύX����
		}
	}

	//=======================================================================================================================================================
	//SHOP��Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == SHOP_MODE)
	{
		//�t���O��Ԃ��ʏ펞�̎�
		if (m_FlagSate == NORMAI_MODE)
		{
			SelectGageUISize(50.0f, 270.0f); //�I���Q�[�W1�ڂ̑傫����ݒ肷��
			m_FlagSate = SHOP_MODE;          //�t���O��Ԃ�X�̏�Ԃ֕ω�������
		}

		//������I�������Ƃ��i�O����X�^�[�g�������͂O�ɖ߂�j
		if (m_nBuyOrSendCount == 0)
		{
			//Enter�L�[���������Ƃ�
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_B) == true)
			{
				SelectGageUISize(50.0,150.0f);
				m_PlayerState = BUY_MODE;
			}
		}

		//�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_DOWN) == true)
		{
			SelectGageUISizeCalculation("Plus", 400.0f, 400.0f); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount += 1; //�J�E���g��i�߂�

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount == 2 )
			{
				SelectGageUISize(50.0, 270.0f);
				m_nBuyOrSendCount = 0; //�J�E���g������������

			}
		}
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_UP) == true)
		{
			SelectGageUISizeCalculation("Minus", 400.0f, 400.0f); //�T�C�Y�𒲐�����
			m_nBuyOrSendCount -= 1; //�J�E���g��i�߂�

			//�I���O�̐��l�ɂȂ�����
			if (m_nBuyOrSendCount ==-1)
			{
				SelectGageUISize(450.0, 670.0f);
				m_nBuyOrSendCount = 1; //�J�E���g������������

			}
		}
	}

	//=======================================================================================================================================================
	//������Ԃ̎�
	//=======================================================================================================================================================
	else if (m_PlayerState == BUY_MODE)
	{
		//���������邩��UI��j������
		if (m_pBuyText != nullptr)
		{
			m_pBuyText->Release();
			m_pBuyText = nullptr;
			return;
		}

		//���j���[�𐶐�����
		if (m_pMenyu == nullptr)
		{
			m_pMenyu = CShopMenu::Create();
		}


		//�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = NORMAI_MODE;
		}

		//S�L�[���������Ƃ�
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_DOWN) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				m_pSelectGage->GetSizeY() += 160.0f;
				m_pSelectGage->GetSize1Y() += 160.0f;
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount += 1;

				if (m_nSelectShopCount == 4 || m_nSelectShopCount == 5)
				{
					m_pSelectGage->GetSizeY() = 50.0f;
					m_pSelectGage->GetSize1Y() = 150.0f;
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 0;

				}
			}
		}

		//W�L�[���������Ƃ�
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_UP) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				m_pSelectGage->GetSizeY() -= 160.0f;
				m_pSelectGage->GetSize1Y() -= 160.0f;
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount -= 1;

				if (m_nSelectShopCount == -1)
				{
					m_pSelectGage->GetSizeY() = 530.0f;
					m_pSelectGage->GetSize1Y() = 630.0f;
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = 3;

				}
			}
		}

		//Enter�L�[���������Ƃ�
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_B) == true)
		{
			CreateGun();
		}
	}
}


//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISize(float fSIzeX,float fSIze1X)
{
	m_pSelectGage->GetSizeY() = fSIzeX;
	m_pSelectGage->GetSize1Y() = fSIze1X;

	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //�I���Q�[�W�Q�ڂ̑傫���𓯊�������
}

//===============================================================================================================================================================================
//�I���Q�[�W��UI�̃T�C�Y��ݒ肷�鏈��
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISizeCalculation(const char* aSelect,float fSIzeX, float fSIze1X)
{
	if (aSelect == "Plus")
	{
		m_pSelectGage->GetSizeY() += fSIzeX;
		m_pSelectGage->GetSize1Y() += fSIze1X;
	}
	else if (aSelect == "Minus")
	{
		m_pSelectGage->GetSizeY() -= fSIzeX;
		m_pSelectGage->GetSize1Y() -= fSIze1X;
	}

	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //�I���Q�[�W�Q�ڂ̑傫���𓯊�������
}


//===============================================================================================================================================================================
//���퐶������
//===============================================================================================================================================================================
void CPlayerX::CreateGun()
{
	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 0)
	{
		if (m_pModelPrts[18]->m_bCreateGun == false)
		{
			m_pModelPrts[18]->m_bCreateGun = true;
		}
	}

	//��Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 1)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::DEBRIS, 0, m_pos);
	}

	//�O�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 2)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::DEBRIS, 0, m_pos);
	}

	//�l�Ԗڂ̕��킪�I�΂ꂽ��
	if (m_nSelectShopCount == 3)
	{
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::DEBRIS, 0, m_pos);
	}

}

//===============================================================================================================================================================================
//�`�揈��
//===============================================================================================================================================================================
void CPlayerX::Draw()
{
	CCharacter::DrawPlayer(MAX_PRTS);
}

//===============================================================================================================================================================================
//�l�X�ȕ��̓����蔻��
//===============================================================================================================================================================================
void CPlayerX::BlockJudgement()
{
	//�n�ʗp�̃u���b�N�̐���������
	for (int nCount = 0; nCount <CManager::GetInstance()->GetFieldBlockCount()+1; nCount++)
	{
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.05f, m_move) == true)
			{

			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), m_ModelSize, CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), m_move) == true)
				{
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y + CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
			}
		}
	}

	//�オ��p�̃u���b�N�̐���������
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetGoUpBlockCount() + 1; nCount1++)
	{
		if (CManager::GetInstance()->GetGoUpBlock(nCount1) != nullptr)
		{
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), m_ModelSize, CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize() * 1.1f, m_move) == true)
			{

			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), m_ModelSize, CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize(), m_move) == true)
				{
					CFuelGage::m_bUse = false;
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize().y + CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
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
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), m_ModelSize, CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.1f, m_move) == true)
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
			if (m_pCollision->ColiisionBoxRoadBlock001(m_pos, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), m_ModelSize, CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * 1.04f, m_move) == true)
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
					CFuelGage::m_bUse = false;
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
				else if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), m_ModelSize, CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), m_move) == true)
				{
					CFuelGage::m_bUse = false;
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

	//��ǃu���b�N����
	for (int nCount6 = 0; nCount6 < CManager::GetInstance()->GetUpWallBlockCount() + 1; nCount6++)
	{
		if (CManager::GetInstance()->GetUpBlock(nCount6) != nullptr)
		{
			if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), m_ModelSize, CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize() * 1.05f, m_move) == true)
			{
				//m_pos.x = 100.0f;
			}
			else
			{
				if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), m_ModelSize, CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), m_move) == true)
				{
					GravityTogether();
					m_pos.y = CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize().y + CManager::GetInstance()->GetUpBlock(nCount6)->GetPos().y;//y���̈ʒu��ݒ�
					if (m_JumpFlag == true)
					{
						m_JumpFlag = false; //�t���O��flase�ɂ���
					}
				}
				else if (m_pCollision->ColiisionBoxOutside(m_pos, CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), m_ModelSize, CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), m_move) == true)
				{
					m_JumpFlag = false; //�t���O��flase�ɂ���
				}
			}
		}
	}

	//�������u���b�N001����
	for (int nCount7 = 0; nCount7 < CManager::GetInstance()->GetSmallBlock001Count() + 1; nCount7++)
	{
		if (CManager::GetInstance()->GetSmallBlock001(nCount7) != nullptr)
		{
			if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), m_ModelSize, CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), m_move) == true)
			{
				CFuelGage::m_bUse = false;
				GravityTogether();
				m_pos.y = CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos().y;//y���̈ʒu��ݒ�
				if (m_JumpFlag == true)
				{
					m_JumpFlag = false; //�t���O��flase�ɂ���
				}
			}
			else if (m_pCollision->ColiisionBoxOutside(m_pos, CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), m_ModelSize, CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), m_move) == true)
			{
				m_JumpFlag = false; //�t���O��flase�ɂ���
			}
		}
	}
	
	//�{�X��̑���
	if (CManager::GetInstance()->GetFinalBlock() != nullptr)
	{
		if (m_pCollision->ColiisionBoxInside(m_pos, CManager::GetInstance()->GetFinalBlock()->GetPos(), m_ModelSize, CManager::GetInstance()->GetFinalBlock()->GetModelSize(), m_move) == true)
		{
			GravityTogether();
			m_pos.y = CManager::GetInstance()->GetFinalBlock()->GetModelSize().y + CManager::GetInstance()->GetFinalBlock()->GetPos().y;//y���̈ʒu��ݒ�
			if (m_JumpFlag == true)
			{
				m_JumpFlag = false; //�t���O��flase�ɂ���
			}
		}
	}
	//�{�X��̓V��
	if (CManager::GetInstance()->GetFinalCeiling() != nullptr)
	{
		if (m_pCollision->ColiisionBoxOutside(m_pos, CManager::GetInstance()->GetFinalCeiling()->GetPos(), m_ModelSize, CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), m_move) == true)
		{
			//m_JumpFlag = false; //�t���O��flase�ɂ���
			m_GravityFlag = true;
		}
		//���̑�
		else
		{
			m_GravityFlag = true;
		}
	}



	//�o�g���V�b�v�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetSpeceBattleShip() != nullptr)
	{
		if (m_pCollision->CircleCollision(m_pos, CManager::GetInstance()->GetSpeceBattleShip()->GetPos(), m_ModelSize, CManager::GetInstance()->GetSpeceBattleShip()->GetModelSize() * 1.1f) == true)
		{
			m_bNextStage = true; //����scene�֍s���t���t��ON�ɂ���
		}
	}

	//SHOP�Ƃ̓����蔻��
	if (CManager::GetInstance()->GetShop() != nullptr)
	{
		if (m_pCollision->ColiisionBox(m_pos, CManager::GetInstance()->GetShop()->GetPos(), m_ModelSize, CManager::GetInstance()->GetShop()->GetModelSize(), m_move) == true)
		{

		}

		if (m_pCollision->CircleCollision(m_pos, CManager::GetInstance()->GetShop()->GetPos(), m_ModelSize, CManager::GetInstance()->GetShop()->GetModelSize() * 1.5f) == true)
		{
			//�b��text�̏�񂪂Ȃ���
			if (m_pTalkText == nullptr)
			{
				m_pTalkText = CUI::Create(CObject3D::TYPE_UI::TALKTEXTR);
				m_pTalkText->GetPos() = D3DXVECTOR3(CManager::GetInstance()->GetShop()->GetPos().x, CManager::GetInstance()->GetShop()->GetPos().y + 150.0f, CManager::GetInstance()->GetShop()->GetPos().z); //�ʒu�̏�����
				m_pTalkText->GetDraw() = true;
			}

			if (m_PlayerState == NORMAI_MODE)
			{
				ShopKeySet();
			}
		}
		else
		{
			//�b��text�̏�񂪂��鎞
			if (m_pTalkText != nullptr)
			{
				m_pTalkText->Release();
				m_pTalkText = nullptr;
			}
		}
	}
}

//===============================================================================================================================================================================
//���f���̎擾
//===============================================================================================================================================================================
CPlayerX* CPlayerX::Create()
{
	CPlayerX* pPlayerX = new CPlayerX(3); //���I�m��

	if (SUCCEEDED(pPlayerX->Init()))
	{
		if (pPlayerX != nullptr)
		{
			//pPlayerX->Size(); //Player�̃T�C�Y�̌v�Z������
			pPlayerX->SetType(PLAYER); //�^�C�v��PLAYER�ɐݒ�
			return pPlayerX; //�v���C���[�̏���Ԃ�
		}
	}

	return nullptr; //���Ȃ�
}