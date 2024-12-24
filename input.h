
//=============================================
//
//キーボードのプロトタイプ宣言[input.h]
//Author:chiba haruki
//
//=============================================

#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================
//インクルード
#include "main.h"


#define MAX_KEY (256)
#define MAX_PAD (10)

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,
	JOYKEY_DOWN,
	JOYKEY_LEFT,
	JOYKEY_RIGHT,
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_LB,
	JOYKEY_RB,
	JOYKEY_LT,
	JOYKEY_RT,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
}JOYKEY;

//コントローラーの構造体
typedef struct {
	int KeyPressCount;					//キーを押してる時間のカウント
	int JoyKeyPressCount;				//キーを押してる時間のカウント
	XINPUT_STATE joykeyState;			//ジョイパッドのプレス情報
	XINPUT_STATE joykeyStateTrigger;	//ジョイパッドのトリガー情報
	int Time;							//時間を計る
	D3DXVECTOR3 joykeyStickPos;			// スティックの傾き
	XINPUT_STATE XInput;				// 入力情報
	XINPUT_STATE joykeyStateRelease;	// コントローラーのリリース情報
	XINPUT_STATE joykeyCurrentTime;		// コントローラーの現在の時間
	XINPUT_STATE joykeyExecLastTime;	// コントローラーの最後に真を返した時間
	XINPUT_STATE joykeyInput;			// コントローラーの入力情報
	XINPUT_VIBRATION joykeyMoter;		// コントローラーのモーター
	WORD Button;						//ボタンの判定
	WORD OldButton;						//古いボタンの判定

}Joypad;

//共通項目のクラス
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update();

protected:
	//全入力処理で共有
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};


//キーボードのクラス
class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;
	void Uninit()override;
	void Update()override;

	bool  GetKeyboardPress(int nKey); //プレスの情報を取得
	bool GetKeyboardTrigger(int nKey); //トリガーの情報を取得

private:
	BYTE m_aKeyState[MAX_KEY]; //キーボードの情報を格納
	BYTE m_aKeyStateTrigger[MAX_KEY];
};

//ジョイパットのクラス
class CInputJoyPad
{
public:
	CInputJoyPad();
	~CInputJoyPad();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	bool GetJoypadPress(JOYKEY key);
	bool GetJoypadTrigger(JOYKEY key);
};

#endif

