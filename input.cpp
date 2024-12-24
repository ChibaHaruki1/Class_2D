//=================================
//
//�L�[�{�[�h�̏���[input.cpp]
//Author:chiba haruki
//
//=================================

#include "input.h"

Joypad g_aJoypad; //�W���C�p�b�h�̍\����

//static�ϐ��̏�����
LPDIRECTINPUT8 CInput::m_pInput = nullptr; //DirectInput�I�u�W�F�N�g�ւ̃|�C���^

//============================================���N���XInput�̏���============================================

//======================
//�R���X�g���N�^
//======================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//======================
//�f�X�g���N�^
//======================
CInput::~CInput()
{

}


//=============================
//����������
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//======================
//�I������
//======================
void CInput::Uninit()
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}


//======================
//�X�V����
//======================
void CInput::Update()
{

}


//============================================�L�[�{�[�h�̏���============================================

//======================
//�R���X�g���N�^
//======================
CInputKeyBoard::CInputKeyBoard()
{
	for (int a = 0; a < MAX_KEY;a++)
	{
		m_aKeyState[a] = {};
		m_aKeyStateTrigger[a] = {};
	}
}

//======================
//�f�X�g���N�^
//======================
CInputKeyBoard::~CInputKeyBoard()
{

}

//===========================
//�L�[�{�[�h�̏���������
//===========================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�������Ɏ��s������
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐����Ɏ��s������
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�Ɏ��s������
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�������[�h��ݒ�Ɏ��s������
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK; //������Ԃ�
}

//========================
//�L�[�{�[�h�̏I������
//========================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit(); //�I���������Ă�
}



//==========================
//�L�[�{�[�h�̍X�V����
//==========================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY]; //�L�[�{�[�h�̓��͏��
	
	//���̓f�o�C�X����f�[�^���擾�ɐ���������
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�	
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�	
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}


//=======================
//�L�[�{�[�h�v���X
//=======================
bool CInputKeyBoard ::GetKeyboardPress (int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false; //�L�[�{�[�h�̏���Ԃ�
}


//=======================
//�L�[�{�[�h�g���K�[
//=======================
bool CInputKeyBoard::GetKeyboardTrigger(int nKey)
{
	return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false; //�L�[�{�[�h�g���K�[�̏���Ԃ�
}


//============================================�W���C�p�b�g�̏���============================================


//================================
//�R���X�g���N�^
// //================================
CInputJoyPad::CInputJoyPad()
{

}


//================================
//�f�X�g���N�^
//================================
CInputJoyPad::~CInputJoyPad()
{

}


//==========================================
//�W���C�p�b�h�̏���������
//==========================================
HRESULT CInputJoyPad::Init(void)
{
	//for (int JoyCount = 0; JoyCount < MAX_PAD; JoyCount++)
	{
		//�������̃N���A
		memset(&g_aJoypad.joykeyState, 0, sizeof(XINPUT_STATE));
		memset(&g_aJoypad.joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

		//XInput�̃X�e�[�g�ݒ�(�L���ɂ���)
		XInputEnable(true);
	}
	return S_OK;
}

//==========================================
//�W���C�p�b�h�̏I������
//==========================================
void CInputJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(false);
}


//==========================================
//�W���C�p�b�h�̍X�V����
//==========================================
void CInputJoyPad::Update(void)
{

	//for (int JoyCount = 0; JoyCount < MAX_PAD; JoyCount++)
	{
		XINPUT_STATE joykeystate; //�W���C�p�b�h�̓��͏��

		//�W���C�p�b�h�̏����擾
		if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
		{
			g_aJoypad.Button = g_aJoypad.joykeyState.Gamepad.wButtons;
			g_aJoypad.joykeyStateTrigger.Gamepad.wButtons = g_aJoypad.Button & ~g_aJoypad.OldButton; //�g���K�[�̏���ݒ�
			g_aJoypad.OldButton = g_aJoypad.joykeyState.Gamepad.wButtons;

			g_aJoypad.joykeyState = joykeystate; //�W���C�p�b�h�̃v���X����ۑ�
		}
	}

}

//==========================================
//�W���C�p�b�h�̃v���X�����擾
//==========================================
bool CInputJoyPad::GetJoypadPress(JOYKEY key)
{
	return (g_aJoypad.joykeyState.Gamepad.wButtons & (0x01 << key));
}


//==========================================================================================
//�W���C�p�b�h�̃g���K�[�����擾
//==========================================================================================
bool CInputJoyPad::GetJoypadTrigger(JOYKEY key)
{
	return (g_aJoypad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << key));
}
