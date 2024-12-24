//=================================
//
//キーボードの処理[input.cpp]
//Author:chiba haruki
//
//=================================

#include "input.h"

Joypad g_aJoypad; //ジョイパッドの構造体

//static変数の初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr; //DirectInputオブジェクトへのポインタ

//============================================基底クラスInputの処理============================================

//======================
//コンストラクタ
//======================
CInput::CInput()
{
	m_pDevice = nullptr;
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
	if (m_pInput == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
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
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
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
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL; //失敗を返す
	}

	//データフォーマットを設定に失敗した時
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //失敗を返す
	}

	//協調モードを設定に失敗した時
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //失敗を返す
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

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
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存	
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存	
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードへのアクセス権を獲得
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
		memset(&g_aJoypad.joykeyState, 0, sizeof(XINPUT_STATE));
		memset(&g_aJoypad.joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

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
			g_aJoypad.Button = g_aJoypad.joykeyState.Gamepad.wButtons;
			g_aJoypad.joykeyStateTrigger.Gamepad.wButtons = g_aJoypad.Button & ~g_aJoypad.OldButton; //トリガーの情報を設定
			g_aJoypad.OldButton = g_aJoypad.joykeyState.Gamepad.wButtons;

			g_aJoypad.joykeyState = joykeystate; //ジョイパッドのプレス情報を保存
		}
	}

}

//==========================================
//ジョイパッドのプレス情報を取得
//==========================================
bool CInputJoyPad::GetJoypadPress(JOYKEY key)
{
	return (g_aJoypad.joykeyState.Gamepad.wButtons & (0x01 << key));
}


//==========================================================================================
//ジョイパッドのトリガー情報を取得
//==========================================================================================
bool CInputJoyPad::GetJoypadTrigger(JOYKEY key)
{
	return (g_aJoypad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << key));
}
