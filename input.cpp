//=================================
//
//キーボードの処理[input.cpp]
//Author:chiba haruki
//
//=================================

#include "input.h"

//static変数の初期化
 

//============================================基底クラスInputの処理============================================

//======================
//コンストラクタ
//======================
CInput::CInput()
{
	m_Input = nullptr;
	m_Device = nullptr;
}

//======================
//デストラクタ
//======================
CInput::~CInput()
{

}


//=============================
//初期化処理
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//======================
//終了処理
//======================
void CInput::Uninit()
{
	//入力デバイス（キーボード）の破棄
	if (m_Device != nullptr)
	{
		m_Device->Unacquire();
		m_Device->Release();
		m_Device = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_Input != nullptr)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}


//======================
//更新処理
//======================
void CInput::Update()
{

}


//============================================キーボードの処理============================================

//======================
//コンストラクタ
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
//デストラクタ
//======================
CInputKeyBoard::~CInputKeyBoard()
{

}

//===========================
//キーボードの初期化処理
//===========================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//初期化に失敗した時
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL; //失敗を返す
	}

	//入力デバイス（キーボード）の生成に失敗した時
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &GetDevice(), NULL)))
	{
		return E_FAIL; //失敗を返す
	}

	//データフォーマットを設定に失敗した時
	if (FAILED(GetDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //失敗を返す
	}

	//協調モードを設定に失敗した時
	if (FAILED(GetDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //失敗を返す
	}

	//キーボードへのアクセス権を獲得
	GetDevice()->Acquire();

	return S_OK; //成功を返す
}

//========================
//キーボードの終了処理
//========================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit(); //終了処理を呼ぶ
}



//==========================
//キーボードの更新処理
//==========================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY]; //キーボードの入力情報
	
	//入力デバイスからデータを取得に成功した時
	if (SUCCEEDED(GetDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存	
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存	
		}
	}
	else
	{
		GetDevice()->Acquire(); //キーボードへのアクセス権を獲得
	}
}


//=======================
//キーボードプレス
//=======================
bool CInputKeyBoard ::GetKeyboardPress (int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false; //キーボードの情報を返す
}


//=======================
//キーボードトリガー
//=======================
bool CInputKeyBoard::GetKeyboardTrigger(int nKey)
{
	return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false; //キーボードトリガーの情報を返す
}


//============================================ジョイパットの処理============================================


//================================
//コンストラクタ
// //================================
CInputJoyPad::CInputJoyPad()
{

}


//================================
//デストラクタ
//================================
CInputJoyPad::~CInputJoyPad()
{

}


//==========================================
//ジョイパッドの初期化処理
//==========================================
HRESULT CInputJoyPad::Init(void)
{
	//for (int JoyCount = 0; JoyCount < MAX_PAD; JoyCount++)
	{
		//メモリのクリア
		memset(&m_JyoPad.joykeyState, 0, sizeof(XINPUT_STATE));
		memset(&m_JyoPad.joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

		//XInputのステート設定(有効にする)
		XInputEnable(true);
	}
	return S_OK;
}

//==========================================
//ジョイパッドの終了処理
//==========================================
void CInputJoyPad::Uninit(void)
{
	//XInputのステートを設定
	XInputEnable(false);
}


//==========================================
//ジョイパッドの更新処理
//==========================================
void CInputJoyPad::Update(void)
{

	//for (int JoyCount = 0; JoyCount < MAX_PAD; JoyCount++)
	{
		XINPUT_STATE joykeystate; //ジョイパッドの入力情報

		//ジョイパッドの情報を取得
		if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
		{
			m_JyoPad.Button = m_JyoPad.joykeyState.Gamepad.wButtons;
			m_JyoPad.joykeyStateTrigger.Gamepad.wButtons = m_JyoPad.Button & ~m_JyoPad.OldButton; //トリガーの情報を設定
			m_JyoPad.OldButton = m_JyoPad.joykeyState.Gamepad.wButtons;

			m_JyoPad.joykeyState = joykeystate; //ジョイパッドのプレス情報を保存
		}
	}

}

//==========================================
//ジョイパッドのプレス情報を取得
//==========================================
bool CInputJoyPad::GetJoypadPress(JOYKEY key)
{
	return (m_JyoPad.joykeyState.Gamepad.wButtons & (0x01 << (int)key));
}


//==========================================================================================
//ジョイパッドのトリガー情報を取得
//==========================================================================================
bool CInputJoyPad::GetJoypadTrigger(JOYKEY key)
{
	return (m_JyoPad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << (int)key));
}
