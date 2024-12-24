
//=============================================
//
//�L�[�{�[�h�̃v���g�^�C�v�錾[input.h]
//Author:chiba haruki
//
//=============================================

#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================
//�C���N���[�h
#include "main.h"


#define MAX_KEY (256)
#define MAX_PAD (10)

//�L�[�̎��
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

//�R���g���[���[�̍\����
typedef struct {
	int KeyPressCount;					//�L�[�������Ă鎞�Ԃ̃J�E���g
	int JoyKeyPressCount;				//�L�[�������Ă鎞�Ԃ̃J�E���g
	XINPUT_STATE joykeyState;			//�W���C�p�b�h�̃v���X���
	XINPUT_STATE joykeyStateTrigger;	//�W���C�p�b�h�̃g���K�[���
	int Time;							//���Ԃ��v��
	D3DXVECTOR3 joykeyStickPos;			// �X�e�B�b�N�̌X��
	XINPUT_STATE XInput;				// ���͏��
	XINPUT_STATE joykeyStateRelease;	// �R���g���[���[�̃����[�X���
	XINPUT_STATE joykeyCurrentTime;		// �R���g���[���[�̌��݂̎���
	XINPUT_STATE joykeyExecLastTime;	// �R���g���[���[�̍Ō�ɐ^��Ԃ�������
	XINPUT_STATE joykeyInput;			// �R���g���[���[�̓��͏��
	XINPUT_VIBRATION joykeyMoter;		// �R���g���[���[�̃��[�^�[
	WORD Button;						//�{�^���̔���
	WORD OldButton;						//�Â��{�^���̔���

}Joypad;

//���ʍ��ڂ̃N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update();

protected:
	//�S���͏����ŋ��L
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};


//�L�[�{�[�h�̃N���X
class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;
	void Uninit()override;
	void Update()override;

	bool  GetKeyboardPress(int nKey); //�v���X�̏����擾
	bool GetKeyboardTrigger(int nKey); //�g���K�[�̏����擾

private:
	BYTE m_aKeyState[MAX_KEY]; //�L�[�{�[�h�̏����i�[
	BYTE m_aKeyStateTrigger[MAX_KEY];
};

//�W���C�p�b�g�̃N���X
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

