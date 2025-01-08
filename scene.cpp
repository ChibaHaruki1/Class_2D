//====================================
//
//��ʑJ�ڏ���[scene.cpp]
//Auther:Haruki Chiba
//
//====================================

#include "scene.h"
#include "manager.h"
#include "rendererh.h"
#include "bg.h"
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


//static�ϐ��̏�����
//CCamera* CScene::m_pCamera = nullptr;
//CLight* CScene::m_pLight = nullptr;
//CPlayerX* CScene::m_pPlayerX = nullptr;
//CTarget* CScene::m_pTragetUi = nullptr;
//CMPTargetReTime* CScene::pMPTargetReTime = nullptr;


//=======================
//�R���X�g���N�^
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_Mode = MODE_RESULT;
	m_pObjectSet = nullptr;
	m_pPlayerX = nullptr;
	m_bOneSound = false;
	//pMPTargetReTime = nullptr;
	//m_pOverhead_Processing = nullptr;
	//m_pPlayerX = nullptr;
	//m_pTragetUi = nullptr;

	//CObjectX::GetTragetNumberCount() = -1;
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
	CObject::ReleaseAll(); //�S�Ă�Uninit()���ĂсAdelete����
	CObjectManagerX::ReleaseAll(); //�S�Ă�unit���ĂсAdelete����

	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;
		m_pObjectSet = nullptr;
	}

	if (m_pPlayerX != nullptr)
	{
		m_pPlayerX = nullptr;
	}

	//�J�����̏�񂪂��鎞
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //�J�����̏I������
		delete m_pCamera; //�������̉��
		m_pCamera = nullptr; //���𖳂���
	}

	//�����̏�񂪂��鎞
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //�����̏I������
		delete m_pLight; //�������̉��
		m_pLight = nullptr; //���𖳂���
	}
}


//=======================
//�X�V����
//=======================
void CScene::Update()
{
	
}

//=======================
//���̕���Update���Ă�
//=======================
void CScene::AnyUpdate()
{
	if (m_Mode == MODE_GAME02)
	{
		CManager::GetEvent()->Update();
	}
}


//=======================
//�`�揈��
//=======================
void CScene::Draw()
{

}


//=======================
//����
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //���N���X�̓��I�m��

	//�Q�[�����[�h���P�̎�
	if (mode == MODE_GAME01)
	{
		pScene = new CGame01();
		pScene->m_Mode = MODE_GAME01;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�Q�[�����[�h���Q�̎�
	else if (mode == MODE_GAME02)
	{
		pScene = new CGame02();
		pScene->m_Mode = MODE_GAME02;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�^�C�g���̎�
	else if (mode == MODE_TITLE)
	{
		pScene = new CTitle();
		pScene->m_Mode = MODE_TITLE;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//���U���g�̎�
	else if (mode == MODE_RESULT)
	{
		pScene = new CResult();
		pScene->m_Mode = MODE_RESULT;

		if (SUCCEEDED(pScene->Init()))
		{
			if (pScene != nullptr)
			{
				return pScene;
			}
		}
	}

	//�Q�[�����[�h�̎�
	else if (mode == MODE_GAMEOVER)
	{
		pScene = new CGameOver();
		pScene->m_Mode = MODE_GAMEOVER;

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

//CMP* CScene::GetMP()
//{
//	return m_pMP;
//}



//=======================
//�J�����̏���Ԃ�
//=======================
CCamera* CScene::GetCamera()
{
	return m_pCamera;
}


//=======================
//�����̏���Ԃ�
//=======================
CLight* CScene::GetLight()
{
	return m_pLight;
}


//============================
//�v���C���[�̏���Ԃ�
//============================
CPlayerX* CScene::GetPlayerX()
{
	return m_pPlayerX;
}


//
//
//
CObjectSet* CScene::GetObjectSet()
{
	return m_pObjectSet;
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
	m_Mode = MODE_GAME01;
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

	CScene::Init();

	m_pCamera->GetAdjustmentPosZ() = 700;

	CompileLood(); //Lood�����������֐������ČĂ�

	CompileCreate(); //create���������̂��֐������ČĂ�

	return S_OK;
}


//=======================
//�I������
//=======================
void CGame01::Uninit()
{
	CScene::Uninit();

	//�e�N�X�`���̔j��
	CompileUnlood();
}


//=======================
//�X�V����
//=======================
void CGame01::Update()
{
	m_pCamera->Update(); //�J�����̍X�V����
	m_pLight->Update(); //�����̍X�V����

	//m_pOverhead_Processing->PlayerMPNumber();
}


//=======================
//�`�揈��
//=======================
void CGame01::Draw()
{

}


//=======================
//Lood�֐����Ă�
//=======================
void CGame01::CompileLood()
{
	
}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame01::CompileCreate()
{
	//X�t�@�C����create

	m_pPlayerX = CPlayerX::Create(); //�v���C���[�̐���

	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(12700.0f, 1900.0f, 0.0f));  //���̃X�e�[�W�֍s��obj�̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 1);                                                                    //��̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(1000.0f, 100.0f, 0.0f));     //���[�V�����t���̓G�̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(2900.0f, 2000.0f, 0.0f));    //���[�V�����t���̓G�̐���
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001,0, D3DXVECTOR3(7000.0f, 2000.0f, 0.0f));    //���[�V�����t���̓G�̐���

	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE,0);                                            //�X�R�A�̐���
}


//=======================
//Unlood�֐����Ă�
//=======================
void CGame01::CompileUnlood()
{
	
}


//================================================================================================================================
//                                                    �X�e�[�W2
//================================================================================================================================


//=======================
//�R���X�g���N�^
//=======================
CGame02::CGame02()
{
	
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

	//�e�N�X�`���̔j��
	CompileUnlood();
}


//=======================
//�X�V����
//=======================
void CGame02::Update()
{
	m_pCamera->Update(); //�J�����̍X�V����
	m_pLight->Update(); //�����̍X�V����
}


//=======================
//�`�揈��
//=======================
void CGame02::Draw()
{

}


//=======================
//Lood�֐����Ă�
//=======================
void CGame02::CompileLood()
{

}


//=======================
//Cretae�֐����Ă�
//=======================
void CGame02::CompileCreate()
{
	//X�t�@�C����create
	m_pPlayerX = CPlayerX::Create(); //�v���C���[�̐���

	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));         //�X�̐���
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                          //��̐���
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(4335.0f, -200.0f, 0.0f));   //�{�X��̑���
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());                                            //�X�R�A�̐���
}


//=======================
//Unlood�֐����Ă�
//=======================
void CGame02::CompileUnlood()
{
	
}


//================================================================================================================================
//                                                    �^�C�g�����[�h�̏���
//================================================================================================================================

//======================
//�R���X�g���N�^
//======================
CTitle::CTitle()
{
	Count = false;
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
	CManagerBg::Create(MODE_TITLE);
	////CBgText::Create();
	pFade = CFade::Create();
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
	if (Count == true)
	{
		pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

		//�t�F�[�h�̏������I�������i���S�ɈÂ��Ȃ�����j
		if (pFade->GetCountAlpha() >= 255)
		{
			CManager::SetMode(CScene::MODE_GAME01);
			//CManager::UninitKey();
			return; //�����𔲂���
		}

		//CManager::SetMode(CScene::MODE_GAME01);
	}

	//Enter�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true && pFade->GetCountAlpha() <= 245)
	{
		Count = true;
	}

	if (m_bOneSound == false)
	{
		CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_WING); //BDM�𗬂�
		m_bOneSound = true;
	}
}


//=======================
//�`�揈��
//=======================
void CTitle::Draw()
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
	Count = false;
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
	CManagerBg::Create(MODE_RESULT);
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
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A) == true)
	{
		Count = true;
	}

	else if (Count == true)
	{
		CManager::SetMode(CScene::MODE_TITLE);
		//CManager::UninitKey();
		return; //�����𔲂���
	}
}


//=======================
//�`�揈��
//=======================
void CResult::Draw()
{

}


//================================================================================================================================
//                                                   �Q�[���I�[�o�[���[�h�̏���
//================================================================================================================================


//======================
//�R���X�g���N�^
//======================
CGameOver::CGameOver()
{
	Count = false;
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
	CManagerBg::Create(MODE_GAMEOVER);
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
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(JOYKEY_A)==true)
	{
		Count = true;
	}

	if (Count == true)
	{
		CManager::SetMode(CScene::MODE_RESULT);
		//CManager::UninitKey();
		return; //�����𔲂���
	}
}


//=======================
//�`�揈��
//=======================
void CGameOver::Draw()
{

}