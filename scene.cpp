//====================================
//
//��ʑJ�ڏ���[scene.cpp]
//Auther:Haruki Chiba
//
//====================================


//====================================
//�C���N���[�h
#include "scene.h"
#include "manager.h"
#include "rendererh.h"
#include "bullet.h"
#include "enemy.h"
#include "efect.h"
#include "collision.h"
#include "score.h"
#include "objectX.h"
#include "stage_obj.h"
#include "block.h"
#include "gage.h"
#include "enemyinmotion.h"
#include "bg.h"


//static�ϐ��̏�����
//CCamera* CScene::m_pCamera = nullptr;
//CLight* CScene::m_pLight = nullptr;
//CPlayerX* CScene::m_pPlayerX = nullptr;
//CTarget* CScene::m_pTragetUi = nullptr;
//CMPTargetReTime* CScene::pMPTargetReTime = nullptr;

CManagerBg* g_pBG; //�w�i��BG�̃O���[�o���ϐ�


//=======================
//�R���X�g���N�^
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_Mode = MODE::MODE_RESULT;
	m_pPlayerX = nullptr;
	m_bOneSound = false;
	m_bOneScene = false;
}


//=======================
//�f�X�g���N�^
//=======================
CScene::~CScene()
{

}


//=======================
//����������
//=======================
HRESULT CScene::Init()
{
	m_pCamera = new CCamera(); //�J�����̓��I�m��
	m_pLight = new CLight(); //�����̓��I�m��

	m_pCamera->Init(); //�J�����̏�����
	m_pLight->Init(); //�����̏�����

	CManager::GetRenderer()->GetDrawShader() = false;
	return S_OK;
}


//=======================
//�I������
//=======================
void CScene::Uninit()
{
	CObject::ReleaseAll();         //�S�Ă�Uninit()���ĂсAdelete����
	CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����


	m_pPlayerX = nullptr;          //���𖳂���

	//�J�����̏�񂪂��鎞
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //�J�����̏I������
		delete m_pCamera;    //�������̉��
		m_pCamera = nullptr; //���𖳂���
	}

	//�����̏�񂪂��鎞
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //�����̏I������
		delete m_pLight;    //�������̉��
		m_pLight = nullptr; //���𖳂���
	}
}


//=======================
//�X�V����
//=======================
void CScene::Update()
{
	m_pCamera->Update(); //�J�����̍X�V����
	m_pLight->Update();  //�����̍X�V����
}

//=======================
//���̕���Update���Ă�
//=======================
void CScene::AnyUpdate()
{
	if (m_Mode == MODE::MODE_GAME02)
	{
		CManager::GetEvent()->Update();
	}
}


//=======================
//����
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //���N���X�̓��I�m��

	//�Q�[�����[�h���P�̎�
	if (mode == MODE::MODE_GAME01)
	{
		pScene = new CGame01();
		pScene->m_Mode = MODE::MODE_GAME01;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�Q�[�����[�h���Q�̎�
	else if (mode == MODE::MODE_GAME02)
	{
		pScene = new CGame02();
		pScene->m_Mode = MODE::MODE_GAME02;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�^�C�g���̎�
	else if (mode == MODE::MODE_TITLE)
	{
		pScene = new CTitle();
		pScene->m_Mode = MODE::MODE_TITLE;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//���U���g�̎�
	else if (mode == MODE::MODE_RESULT)
	{
		pScene = new CResult();
		pScene->m_Mode = MODE::MODE_RESULT;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�Q�[�����[�h�̎�
	else if (mode == MODE::MODE_GAMEOVER)
	{
		pScene = new CGameOver();
		pScene->m_Mode = MODE::MODE_GAMEOVER;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	return nullptr; //
}


//================================================================================================================================
//                                                    �Q�[�����[�h�̏���
//================================================================================================================================


//================================================================================================================================
//                                                    �X�e�[�W�P
//================================================================================================================================


//=======================
//�R���X�g���N�^
//=======================
CGame01::CGame01()
{
	m_pFade = nullptr;
}


//=======================
//�f�X�g���N�^
//=======================
CGame01::~CGame01()
{

}


//=======================
//����������
//=======================
HRESULT CGame01::Init()
{
	g_pBG = CManagerBg::Create(MODE::MODE_TITLE);             //�w�i��UI����
	m_pFade = CFade::Create();                                //�t�F�[�h�̐���
												              
	CScene::Init();                                           //����������
													          
	GetCamera()->GetAdjustmentPosZ() = 500;                   //�J������Z���̒���
	GetCamera()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));        //�J�����̌����̐ݒ�
													          
	InitCreate();                                             //�^�C�g���ɕK�v�Ȑ���
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING); //�v���C���[�̃��[�V������T���ɐݒ�
	GetPlayerX()->SetRot(D3DXVECTOR3(0.0f,0.57f,0.0f));       //�v���C���[�̌�����ݒ�
	
	GetPlayerX()->GetPos().y = 2050.0f;                //�v���C���[��Y���̈ʒu��ݒ�
										               
	return S_OK;                                       //������Ԃ�
}


//=======================
//�I������
//=======================
void CGame01::Uninit()
{
	CScene::Uninit(); //�j������
}


//=======================
//�X�V����
//=======================
void CGame01::Update()
{
	if (GetOneScene() == true)
	{
		if (m_pFade != nullptr)
		{
			m_pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

			//�t�F�[�h�̏������I�������i���S�ɈÂ��Ȃ�����j
			if (m_pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
			{
				m_pFade->Release();
				g_pBG->Release();
				m_pFade = nullptr;
				g_pBG = nullptr;
				SetPlay(true);
				GetPlayerX()->SetGravityFlag(true);                                           //�d��ON
				GetCamera()->GetAdjustmentPosZ() = 700;                                       //�J������Z���̒���
				GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);
				CompileCreate();                        //create���������̂��֐������ČĂ�
				return;
			}
		}
	}

	if (GetOneScene() == false)
	{
		GetPlayerX()->SetGravityFlag(false); //�d��Off

		//Enter�L�[�������ꂽ����A�L�[�������ꂽ��
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
		{
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING);    //�w��̉������~�߂�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);  //BDM�𗬂�
			SetOneScene(true);
		}
	}

	//����������Ă��Ȃ���
	if (GetOneSound() == false)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDM�𗬂�
		SetOneSound(true);                                                         //��x��������
	}

	CScene::Update(); //�X�V����
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame01::InitCreate()
{
	GetPlayerX() = CPlayerX::Create();                                                                                     //�v���C���[�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(0.0f, 2000.0f, 100.0f));  //���̃X�e�[�W�֍s��obj�̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 1);                                                                  //��̐���
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame01::CompileCreate()
{
	//X�t�@�C����create
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //�X�̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(12700.0f, 1900.0f, 0.0f));        //���̃X�e�[�W�֍s��obj�̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(1000.0f, 100.0f, 0.0f));     //���[�V�����t���̓G�̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(2900.0f, 2000.0f, 0.0f));    //���[�V�����t���̓G�̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(7000.0f, 2000.0f, 0.0f));    //���[�V�����t���̓G�̐���

	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE,0);                                                   //�X�R�A�̐���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0); //�v���C���[��HP�Q�[�W�̐���
}


//================================================================================================================================
//                                                    �X�e�[�W2
//================================================================================================================================


//=======================
//�R���X�g���N�^
//=======================
CGame02::CGame02()
{
	SetPlay(true);
}


//=======================
//�f�X�g���N�^
//=======================
CGame02::~CGame02()
{

}


//=======================
//����������
//=======================
HRESULT CGame02::Init()
{
	CScene::Init();

	//CompileLood(); //Lood�����������֐������ČĂ�

	CompileCreate(); //create���������̂��֐������ČĂ�


	return S_OK;
}


//=======================
//�I������
//=======================
void CGame02::Uninit()
{
	CScene::Uninit();
}


//=======================
//�X�V����
//=======================
void CGame02::Update()
{
	CScene::Update();
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame02::CompileCreate()
{
	//X�t�@�C����create
	GetPlayerX() = CPlayerX::Create(); //�v���C���[�̐���

	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //�X�̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                          //��̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(4335.0f, -200.0f, 0.0f));   //�{�X��̑���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());          //�X�R�A�̐���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0); //�v���C���[��HP�Q�[�W�̐���
}


//================================================================================================================================
//                                                    �^�C�g�����[�h�̏���
//================================================================================================================================

//======================
//�R���X�g���N�^
//======================
CTitle::CTitle()
{
	pFade = nullptr;
}


//======================
//�f�X�g���N�^
//======================
CTitle::~CTitle()
{

}


//======================
//������
//======================
HRESULT CTitle::Init()
{
	//CManagerBg::Create(MODE::MODE_TITLE);
	//////CBgText::Create();
	//pFade = CFade::Create();

	CScene::Init();

	GetCamera()->GetAdjustmentPosZ() = 700;

	return S_OK;
}


//======================
//�I������
//======================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
	//CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����
}


//=======================
//�X�V����
//=======================
void CTitle::Update()
{
	////Enter�L�[�������ꂽ�Ƃ�
	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true && pFade->GetAlph() <= 245)
	//{
	//	SetOneScene(true);
	//}

	//else if (GetOneScene() == true)
	//{
	//	pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

	//	//�t�F�[�h�̏������I�������i���S�ɈÂ��Ȃ�����j
	//	if (pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
	//	{
	//		CManager::SetMode(CScene::MODE::MODE_GAME01);
	//		return; //�����𔲂���
	//	}

	//	//CManager::SetMode(CScene::MODE_GAME01);
	//}

	//if (GetOneSound() == false)
	//{
	//	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDM�𗬂�
	//	SetOneSound(true);
	//}

	CScene::Update();
}


//=============================
//�^�C�g���Q�[����ʏ���
//=============================
void CTitle::Game()
{

}


//================================================================================================================================
//                                                   ���U���g���[�h�̏���
//================================================================================================================================


//======================
//�R���X�g���N�^
//======================
CResult::CResult()
{
	
}


//======================
//�f�X�g���N�^
//======================
CResult::~CResult()
{

}


//======================
//������
//======================
HRESULT CResult::Init()
{
	//m_pResultScore = CResultScore::Create();
	CManagerBg::Create(MODE::MODE_RESULT);
	return S_OK;
}


//======================
//�I������
//======================
void CResult::Uninit()
{
	CScene::Uninit();
}


//=======================
//�X�V����
//=======================
void CResult::Update()
{
	//Enter�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetOneScene(true);
	}

	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_GAME01);
		//CManager::UninitKey();
		return; //�����𔲂���
	}
}


//================================================================================================================================
//                                                   �Q�[���I�[�o�[���[�h�̏���
//================================================================================================================================


//======================
//�R���X�g���N�^
//======================
CGameOver::CGameOver()
{
	
}


//======================
//�f�X�g���N�^
//======================
CGameOver::~CGameOver()
{

}


//======================
//������
//======================
HRESULT CGameOver::Init()
{
	CManagerBg::Create(MODE::MODE_GAMEOVER);
	return S_OK;
}


//======================
//�I������
//======================
void CGameOver::Uninit()
{
	CScene::Uninit();
	//CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����
}


//=======================
//�X�V����
//=======================
void CGameOver::Update()
{
	//Enter�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A)==true)
	{
		SetOneScene(true);
	}

	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
		//CManager::UninitKey();
		return; //�����𔲂���
	}
}