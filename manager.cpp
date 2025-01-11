//===========================================
//
//�S�̂��Ǘ����鏈��[manager.cpp]
//Auther:Chiba Haruki
//
//===========================================


#include "manager.h"
#include "rendererh.h"

CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyBoard* CManager::m_pKeyBoard = nullptr;
CInputJoyPad* CManager::m_pJyoPad = nullptr;
CSound* CManager::m_pSound = nullptr;
CScene* CManager::m_pScene = nullptr;
CInstance* CManager::m_pInstance = nullptr;
CObjectSet* CManager::m_pObjectSet = nullptr;
CEvent* CManager::m_pEvent = nullptr;
CMain* CManager::m_pMain = nullptr;


//===================
//�R���X�g���N�^
//===================
CManager::CManager()
{

}

//===================
//�f�X�g���N�^
//===================
CManager::~CManager()
{

}

//==================
//����������
//==================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̏�񂪂Ȃ���
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer(); //�����_���[�̓��I�m�ۂ�����
	}

	//�L�[�{�[�h�̏�񂪂Ȃ���
	if (m_pKeyBoard == nullptr)
	{
		m_pKeyBoard = new CInputKeyBoard(); //�L�[�{�[�h�̓��I�m��
	}

	//�W���C�p�b�g�̏�񂪂Ȃ���
	if (m_pJyoPad == nullptr)
	{
		m_pJyoPad = new CInputJoyPad(); //�W���C�p�b�g�̓��I�m��
	}

	//�����̏�񂪂Ȃ���
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound(); //�T�E���h�̓��I�m��
	}

	if (m_pMain == nullptr)
	{
		m_pMain = new CMain();
	}

	m_pRenderer->Init(hInstance,hWnd, bWindow); //�����_���[��Window�̏������Ăяo��

	//CBlockManager::DataLood();


	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyBoard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�g�̏���������
	if (FAILED(m_pJyoPad->Init()))
	{
		return E_FAIL;
	}


	m_pSound->InitSound(hWnd); //�����̏�����

	return S_OK;
}

//==================
//�I������
//==================
void CManager::Uninit()
{
	//�����_���[�̏�񂪂��鎞
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit(); //���_�o�b�t�@�̔j��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�L�[�{�[�h�̏�񂪂��鎞
	if (m_pKeyBoard != nullptr)
	{
		m_pKeyBoard->Uninit(); //�L�[�{�[�h�̏I������
		delete m_pKeyBoard;
		m_pKeyBoard = nullptr;
	}


	//�W���C�p�b�g�̏�񂪂��鎞
	if (m_pJyoPad != nullptr)
	{
		m_pJyoPad->Uninit(); //�W���C�p�b�g�̏I������
		delete m_pJyoPad;
		m_pJyoPad = nullptr;
	}

	//�����̏�񂪂��鎞
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound(); //�T�E���h�̏I������
		delete m_pSound;
		m_pSound = nullptr;
	}


	//��ʑJ�ڂ̏�񂪂���Ƃ�
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit(); //�I���������Ă�
		delete m_pScene; //�������̉��
		m_pScene = nullptr; //�����Ȃ���
	}

	//�C���X�^���X��񂪂���Ƃ�
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	//text�t�@�C���̏�񂪂��鎞
	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;
		m_pObjectSet = nullptr;
	}

	if (m_pEvent != nullptr)
	{
		delete m_pEvent;
		m_pEvent = nullptr;
	}

	if (m_pMain != nullptr)
	{
		delete m_pMain;
		m_pMain = nullptr;
	}
}

//==================
//�X�V����
//==================
void CManager::Update()
{
	m_pKeyBoard->Update(); //�L�[�{�[�h�̍X�V����
	m_pJyoPad->Update();   //�W���C�p�b�g�̍X�V����
	m_pRenderer->Update(); //�����_���[�̍X�V����
	m_pScene->Update();    //�X�V�������Ă�
	m_pScene->AnyUpdate();    //�X�V�������Ă�
}


//==================
//�`�揈��
//==================
void CManager::Draw()
{
	m_pRenderer->Draw(); //�����_���[�̕`�揈��
	m_pScene->Draw(); //�`�揈�����Ă�
}


//===============================
//��ʑJ�ڂ̃��[�h�̕ύX
//===============================
void CManager::SetMode(CScene::MODE mode)
{
	//scene�̏�񂪂��鎞
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();  //�j���������Ă�
		delete m_pScene;     //��������
		m_pScene = nullptr;  //���𖳂���
	}

	//�C���X�^���X��񂪂���Ƃ�
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();  //�j���������Ă�
		delete m_pInstance;     //��������
		m_pInstance = nullptr;  //���𖳂���
	}

	//event�̏�񂪂��鎞
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;     //��������
		m_pEvent = nullptr;  //���𖳂���
	}

	m_pSound->StopSound();           //�������~�߂�
	m_pInstance = new CInstance();   //�C���X�^���X�̐���
	m_pScene = CScene::Create(mode); //scene�̐���

	//�^�C�g���ƃ��U���g���ȊO�̎�text�t�@�C���̏���ǂݍ���
	if (mode != CScene::MODE_TITLE)
	{
		m_pObjectSet = CObjectSet::Create(); //text����ǂݎ�����I�u�W�F�N�g��z�u����
		m_pEvent = new CEvent();             //���I�m�ۂ���
	}

	//�V�[�������U���g�̎�
	if (mode == CScene::MODE_RESULT)
	{
		//��񂪂��鎞
		if (m_pObjectSet != nullptr)
		{
			delete m_pObjectSet;     //��������
			m_pObjectSet = nullptr;  //���𖳂���
		}
	}
}


//===============================
//�����_���[�̏����擾����
//===============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}


//===============================
//�L�[�{�[�h�̏����擾����
//===============================
CInputKeyBoard* CManager::GetKeyBorad()
{
	return m_pKeyBoard;
}


//================================
//�W���C�p�b�g�̏����擾
//================================
CInputJoyPad* CManager::GetJyoPad()
{
	return m_pJyoPad;
}


//================================
//�T�E���h�̏����擾
//================================
CSound* CManager::GetSound()
{
	return m_pSound;
}
