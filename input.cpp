//=================================
//
//�L�[�{�[�h�̏���[input.cpp]
//Author:chiba haruki
//
//=================================

#include "input.h"

//static�ϐ��̏�����
 

//============================================���N���XInput�̏���============================================

//======================
//�R���X�g���N�^
//======================
CInput::CInput()
{
	m_Input = nullptr;
	m_Device = nullptr;
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
	if (m_Input == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
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
	if (m_Device != nullptr)
	{
		m_Device->Unacquire();
		m_Device->Release();
		m_Device = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_Input != nullptr)
	{
		m_Input->Release();
		m_Input = nullptr;
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
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &GetDevice(), NULL)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�Ɏ��s������
	if (FAILED(GetDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�������[�h��ݒ�Ɏ��s������
	if (FAILED(GetDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	GetDevice()->Acquire();

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
	if (SUCCEEDED(GetDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�	
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�	
		}
	}
	else
	{
		GetDevice()->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
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
		memset(&m_JyoPad.joykeyState, 0, sizeof(XINPUT_STATE));
		memset(&m_JyoPad.joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

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
			m_JyoPad.Button = m_JyoPad.joykeyState.Gamepad.wButtons;
			m_JyoPad.joykeyStateTrigger.Gamepad.wButtons = m_JyoPad.Button & ~m_JyoPad.OldButton; //�g���K�[�̏���ݒ�
			m_JyoPad.OldButton = m_JyoPad.joykeyState.Gamepad.wButtons;

			m_JyoPad.joykeyState = joykeystate; //�W���C�p�b�h�̃v���X����ۑ�
		}
	}

}

//==========================================
//�W���C�p�b�h�̃v���X�����擾
//==========================================
bool CInputJoyPad::GetJoypadPress(JOYKEY key)
{
	return (m_JyoPad.joykeyState.Gamepad.wButtons & (0x01 << (int)key));
}


//==========================================================================================
//�W���C�p�b�h�̃g���K�[�����擾
//==========================================================================================
bool CInputJoyPad::GetJoypadTrigger(JOYKEY key)
{
	return (m_JyoPad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << (int)key));
}
